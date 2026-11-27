#!/usr/bin/env python3
"""Write README.md with the Novalis overlay's decompilation progress.

Run it after `make split-novalis`. For every cpp file in the yaml, a function
counts as done once it is written in C++, and as left while it is still an
INCLUDE_ASM. Padding (func_XXXXXXXX) is not counted as a function. Code size
is the file's span in the overlay minus the bytes still in INCLUDE_ASM.
Files marked asm in the yaml are handwritten assembly and are left out.
"""
import os
import re

YAML = 'config/novalis/novalis.yaml'
SOURCE = 'code/novalis'
NONMATCHINGS = 'code/_generated/novalis/nonmatchings'


def count_cpp_functions(source):
    # Ignore examples in comments and braces/semicolons inside string literals.
    source = re.sub(
        r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
        lambda match: re.sub(r'[^\n]', ' ', match.group()), source)
    # Signatures can span lines. Stop at declarations and other opening scopes.
    return len(re.findall(r'^[A-Za-z][^;{}]*\)\s*\{', source, re.M))


def main():
    segments = []
    for line in open(YAML):
        match = re.match(r'\s*- \[(0x[0-9a-fA-F]+), ([.\w]+)(?:, ([\w/]+))?\]', line)
        if match:
            segments.append((int(match.group(1), 16), match.group(2), match.group(3)))

    groups = {'Engine files': [0] * 6, 'Update files': [0] * 6}
    for index, (start, kind, name) in enumerate(segments):
        if kind != 'cpp':
            continue

        end = segments[index + 1][0]
        source = open(os.path.join(SOURCE, name + '.cpp')).read()

        # A function guarded by ALLOW_NON_MATCHING is not done until it matches.
        source = re.sub(r'#ifdef ALLOW_NON_MATCHING\n.*?#else\n(.*?)#endif\n', r'\1', source, flags=re.S)

        left = re.findall(r'INCLUDE_ASM\("[^"]+", (\w+)\);', source)
        left_bytes = 0
        for function in left:
            header = open(os.path.join(NONMATCHINGS, name, function + '.s')).read()
            left_bytes += int(re.search(r'nonmatching \w+, (0x[0-9A-Fa-f]+)', header).group(1), 16)

        left = [function for function in left if not function.startswith('func_')]
        done = count_cpp_functions(source)

        group = groups['Update files' if name.startswith('game/update/') else 'Engine files']
        group[0] += not left
        group[1] += 1
        group[2] += done
        group[3] += done + len(left)
        group[4] += end - start - left_bytes
        group[5] += end - start

    lines = [
        '# Ratchet & Clank decompilation',
        '',
        'Progress on the Novalis level overlay (handwritten assembly files are not counted).',
        '',
        '| | Files | Functions | Code |',
        '|---|---|---|---|',
    ]
    for name, (files_done, files, functions_done, functions, bytes_done, total_bytes) in groups.items():
        lines.append('| %s | %d / %d | %d / %d | %d KB / %d KB |' % (
            name, files_done, files, functions_done, functions, bytes_done // 1024, total_bytes // 1024))

    open('README.md', 'w').write('\n'.join(lines) + '\n')
    print('\n'.join(lines))


if __name__ == '__main__':
    main()
