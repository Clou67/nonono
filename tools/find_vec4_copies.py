#!/usr/bin/env python3
"""Find R5900 quadword copies suitable for CopyVec4Inline.

Examples (run from the repository root):
    python3 tools/find_vec4_copies.py
    python3 tools/find_vec4_copies.py path/to/BOOT.elf --symbols config/symbols.txt
    python3 tools/find_vec4_copies.py --all-registers --json

Scans executable ELF sections for lq followed by sq of the same register,
optionally separated by nops. Use --exclude-stack to filter stack accesses. These are candidates, not proof of a Vec4
copy: inspect the surrounding code before replacing it with the helper.
"""
import argparse
import bisect
import json
import re
import struct
from pathlib import Path

from elftools.elf.elffile import ELFFile

ROOT = Path(__file__).resolve().parent.parent
REGISTERS = ('zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 '
             's0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra').split()


def functions(elf, symbol_paths):
    """Prefer the supplied address map over any ELF symbol names."""
    result = {}
    for section in elf.iter_sections():
        if section['sh_type'] not in ('SHT_SYMTAB', 'SHT_DYNSYM'):
            continue
        for symbol in section.iter_symbols():
            if symbol['st_info']['type'] == 'STT_FUNC' and symbol.name:
                result[symbol['st_value']] = (symbol.name, symbol['st_size'])
    for path in symbol_paths:
        for line in path.read_text().splitlines():
            match = re.match(r'\s*(\w+)\s*=\s*(0x[\da-fA-F]+)\s*;.*?type:func\b', line)
            if match:
                size = re.search(r'\bsize:(0x[\da-fA-F]+|\d+)', line)
                result[int(match[2], 16)] = (match[1], int(size[1], 0) if size else 0)
    return result


def memory_operand(word):
    displacement = word & 0xffff
    if displacement & 0x8000:
        displacement -= 0x10000
    return '%s0x%x($%s)' % ('-' if displacement < 0 else '', abs(displacement),
                            REGISTERS[(word >> 21) & 31])


def scan(elf, table, args):
    starts = sorted(table)
    endian = '<' if elf.little_endian else '>'
    for section in elf.iter_sections():
        if not section['sh_flags'] & 4 or section['sh_type'] == 'SHT_NOBITS':
            continue
        data = section.data()
        words = [word[0] for word in struct.iter_unpack(endian + 'I', data[:len(data) // 4 * 4])]
        for index, load in enumerate(words):
            register = (load >> 16) & 31
            if load >> 26 != 0x1e or register == 0:
                continue
            if not args.all_registers and register != 2:
                continue
            store_index = index + 1
            while (store_index < len(words) and words[store_index] == 0
                   and store_index - index - 1 < args.max_nops):
                store_index += 1
            if store_index >= len(words):
                continue
            store = words[store_index]
            if store >> 26 != 0x1f or (store >> 16) & 31 != register:
                continue
            if args.exclude_stack and (29 in ((load >> 21) & 31, (store >> 21) & 31)):
                continue
            # lq must not overwrite the register used to address the destination.
            if (store >> 21) & 31 == register:
                continue
            address = section['sh_addr'] + index * 4
            store_address = section['sh_addr'] + store_index * 4
            position = bisect.bisect_right(starts, address) - 1
            start = starts[position] if position >= 0 else None
            name, size = table[start] if start is not None else ('<unknown>', 0)
            limit = start + size if size else (starts[position + 1] if position + 1 < len(starts) else section['sh_addr'] + len(data))
            if start is not None and address >= limit:
                name, start = '<unknown>', None
            if start is not None and store_address >= limit:
                continue
            yield dict(function=name, function_address=start,
                       function_offset=address - start if start is not None else None,
                       load_address=address, store_address=store_address,
                       file_offset=section['sh_offset'] + index * 4,
                       register=REGISTERS[register], source=memory_operand(load),
                       destination=memory_operand(store))


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('binary', nargs='?', type=Path,
                        default=ROOT / 'assets/levels/1_novalis/overlay.elf')
    parser.add_argument('--symbols', action='append', type=Path,
                        help='function map in symbols.txt format; repeat for multiple maps')
    parser.add_argument('--all-registers', action='store_true', help='include copies through registers other than $v0')
    parser.add_argument('--exclude-stack', action='store_true', help='exclude copies to/from $sp')
    parser.add_argument('--max-nops', type=int, default=0, help='allow this many nops between lq and sq (default: 0)')
    parser.add_argument('--json', action='store_true', help='emit a JSON array instead of text')
    args = parser.parse_args()
    if args.max_nops < 0:
        parser.error('--max-nops must be nonnegative')
    paths = args.symbols
    if paths is None:
        paths = [ROOT / 'config/novalis/symbols.txt'] if args.binary.resolve() == (ROOT / 'assets/levels/1_novalis/overlay.elf').resolve() else []
    try:
        with args.binary.open('rb') as stream:
            elf = ELFFile(stream)
            if elf.elfclass != 32 or elf['e_machine'] != 'EM_MIPS':
                parser.error('expected a 32-bit MIPS ELF')
            matches = list(scan(elf, functions(elf, paths), args))
    except (OSError, ValueError) as error:
        parser.error(str(error))
    if args.json:
        print(json.dumps(matches, indent=2))
    else:
        for match in matches:
            offset = '+0x%x' % match['function_offset'] if match['function_offset'] is not None else ''
            print('0x%08X  %s%s  lq $%s,%s -> sq $%s,%s' % (
                match['load_address'], match['function'], offset, match['register'],
                match['source'], match['register'], match['destination']))
        print('%d candidate copies in %d functions' % (len(matches), len({m['function'] for m in matches})))


if __name__ == '__main__':
    main()
