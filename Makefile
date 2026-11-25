# Force use GNU tools
.DEFAULT_GOAL := all
FIND := /usr/bin/find

ifeq ($(OS),Windows_NT)
	OS_ID := Windows
	PATH_SEP := \\
	COPY := copy
	DELETE := del
	DELETEFLAGS := /s /q
else
	OS_ID := $(shell uname 2>/dev/null || echo Unknown)
	PATH_SEP := /
	COPY := cp
	DELETE := rm
	DELETEFLAGS := -rf

	WINE := wine
endif

EEGCC = python3 tools/run_ee_compiler.py $(WINE) tools/cc/bin/ee-gcc.exe
CROSS = mipsel-linux-gnu
#CROSS = mips64r5900el-ps2-elf

-include userconfig.mk

PRODG_DIR = tools/cc

# The compiler driver selects SN ps2eeas with -snas.
SN_AS = $(PRODG_DIR)/lib/gcc-lib/ee/2.95.2/ps2eeas.exe

.PHONY: all setup-snas
all: novalis

setup-snas:
	python3 tools/install_sn_assembler.py --dest $(SN_AS)

$(SN_AS): tools/install_sn_assembler.py
	python3 tools/install_sn_assembler.py --dest $@

.SECONDEXPANSION:

# ---------------------------------------------------------------------------
# Novalis level overlay (assets/levels/1_novalis/overlay.elf)
#
#   make split-novalis   split the overlay with splat
#   make novalis         build build/novalis/overlay.bin and compare it to the original
#
# C++ is compiled with the one project flag set and assembled by SN ps2eeas
# 1.9.6.516 (make setup-snas). Generated .s files are assembled with GNU as.
# ---------------------------------------------------------------------------
NOVALIS_DIR = build/novalis
NOVALIS_LD = $(NOVALIS_DIR)/novalis.ld
NOVALIS_ELF = $(NOVALIS_DIR)/overlay.elf
NOVALIS_BIN = $(NOVALIS_DIR)/overlay.bin
NOVALIS_ORIGINAL = assets/levels/1_novalis/overlay.elf
NOVALIS_FLAGS = -G16 -O2 -fno-exceptions -snas
NOVALIS_OBJS = $(shell test -f $(NOVALIS_LD) && grep -oE '$(NOVALIS_DIR)/[^ ()]+\.o' $(NOVALIS_LD) | awk '!seen[$$0]++')

.PHONY: split-novalis novalis

split-novalis:
	python3 -m splat split config/novalis/novalis.yaml --disassemble-all

novalis: $(NOVALIS_BIN)
	cmp $(NOVALIS_BIN) $(NOVALIS_ORIGINAL) && echo "novalis: OK"

$(NOVALIS_BIN): $(NOVALIS_ELF)
	$(CROSS)-objcopy -O binary $< $@

$(NOVALIS_ELF): $(NOVALIS_OBJS) $(NOVALIS_LD) config/novalis/symbols.txt config/novalis/core_symbols.txt config/novalis/link_aliases.txt
	python3 tools/symbols_to_ld.py $(NOVALIS_DIR)/symbols.ld config/novalis/symbols.txt config/novalis/core_symbols.txt config/novalis/link_aliases.txt
	$(CROSS)-ld -EL --defsym _gp=0x166c00 -T $(NOVALIS_DIR)/symbols.ld -T $(NOVALIS_DIR)/undefined_funcs_auto.txt -T $(NOVALIS_DIR)/undefined_syms_auto.txt -T $(NOVALIS_LD) -Map $(NOVALIS_DIR)/novalis.map $(NOVALIS_OBJS) -o $@

$(NOVALIS_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(CROSS)-as -EL -march=r5900 -mabi=eabi -no-pad-sections -Icode/include $< -o $@

$(NOVALIS_DIR)/code/novalis/%.o: code/novalis/%.cpp $(SN_AS) $(wildcard code/include/*.h) $$(wildcard code/_generated/novalis/nonmatchings/$$*/*.s)
	@mkdir -p $(dir $@)
	$(EEGCC) -c -x c++ $(NOVALIS_FLAGS) -Icode/include -B$(PRODG_DIR)/lib/gcc-lib/ee/2.95.2/ $< -o $@

iso:
	$(WRENCHFOLDER)/wrenchbuild pack assets $(WRENCHFOLDER)/underlay -a rac -o build/build.iso -h release --flusher-thread-hack

clean:
	rm -rf build
	rm -rf code/_generated
