# Matching Functions: Agent Rules

These rules apply to every function you decompile in this project, in both the boot ELF and the level overlays (`code/novalis/`). They take priority over older notes in the repo that conflict with them. In particular, old notes that use `extern "C"` or give one file its own compiler flags are out of date. Do not copy those patterns.

The goal is C++ source that compiles to the original bytes and is also good code: readable, well named, using real structs and globals. A byte match on unreadable code is not finished work.

## Hard rules

1. **No `extern "C"`. Ever.** The game is C-style code in `.cpp` files, compiled as C++. Every function you write is a C++ function, and its symbol is the GCC 2.95 mangled name (see "Symbols and mangling"). Callers anywhere in the codebase reference it through a normal C++ prototype in a header.
2. **One set of compiler flags for all code.** Do not add flags for one file or one function (`-fno-schedule-insns`, `-mno-split-addresses`, `-O1`, …) to force a match. If a function only matches with different flags, it does not match. Leave it as `INCLUDE_ASM` and record what you tried.
3. **No source tricks that only exist to fool the compiler.** No `asm()` statements, register variables (`register int x asm("$2")`), dummy volatiles, `goto` spaghetti or meaningless temporaries added just to shift register allocation. The one exception is genuine VU0/COP2 macro code (`lqc2`, `vmul`, `qmtc2`, …). The original source used inline asm for that, so inline asm that reproduces the same VU0 instructions is legitimate.
   - **Last resort only:** a plain temporary that steers register allocation (for example one `zero` variable reused as an index and a loop start, as in `DrawLineList`) may be used, but only after natural rewrites have really been exhausted. Prefer leaving the function as `INCLUDE_ASM` with a note. Never use `asm()`, register variables or volatiles for this.
   - **Vector copies:** the original copied quadword vectors through a hand-written inline helper (`lq $2` then `sq $2`, always `$2`, address in its own register). Use `CopyVec4Inline` from `mathfunc_inline.h` wherever retail shows that pattern; a plain struct assignment compiles differently.
4. **Fake "functions" stay as `INCLUDE_ASM`.** Some splat functions are really trailing alignment padding, or a few stray words after a real function's `jr $ra`. The linker and compiler do not reproduce these as functions. Do not invent a body: write them with `TEXT_PADDING(words...)` (from `include_asm.h`), copying the words from the generated `.s`. It aligns to 8 and emits the words verbatim. Anything that has a real symbol in `config/symbols.txt` or `config/novalis/symbols.txt` (a named function, not `func_XXXXXXXX` padding) is fair game.
5. **Handwritten assembly files stay assembly.** Files marked `asm` in the yaml (`*proc` files such as `mobyproc`, `partproc`, `shadowproc`, `tfragproc`, `tieproc`, `shrubproc`, `skyproc`, plus `cmecpu`, `collproc`, `drawquad`, `fastfunc`, `miscproc`) were written in assembly by Insomniac. Do not decompile them to C++.
6. **The bytes decide.** Never declare a match by reading the code. It only counts when the object bytes for the function equal the original, and the full build still compares equal (see "Verifying").

## Toolchain

- Compiler: EE GCC 2.95.2 (`tools/cc/bin/ee-gcc.exe`, run through Wine), always with exactly:
  ```
  -G16 -O2 -fno-exceptions -snas
  ```
- Assembler for compiled C++: SN `ps2eeas` 1.9.6.516 (`make setup-snas` installs it into `tools/cc/lib/gcc-lib/ee/2.95.2/`). Other ps2eeas builds pad DIV instructions differently and do not reproduce the original.
- Generated `.s` files (data, handwritten asm files) are assembled with GNU as: `-EL -march=r5900 -mabi=eabi -no-pad-sections -Icode/include`.
- What these choices imply for your code:
  - ps2eeas commits to an addressing mode at the first reference. A small extern global is loaded with `lui`/`lw`; a global defined earlier in the same file (with an initializer) is loaded `$gp`-relative. Inside delay slots the compiler itself emits `$gp`-relative stores. So where retail uses `$gp` for a load, the global is probably defined in that file.
  - A core global (address below 0x15EF00) that retail treats as small data even though it is bigger than 8 bytes (macro addressing, `$gp` in delay slots) is declared with its true size and `__attribute__((section(".sdata")))` on the extern declaration. That is where it really lives, and GCC treats anything in `.sdata` as small data. Use this only for such core externs; never to move an overlay definition. This is a stopgap while the core has no build of its own: once it does, these variables get real definitions there and the attribute should be removed.
  - Whether an extern array is declared with or without a size matters: an unsized array (`extern T x[];`) is addressed through its base address, a sized small one (`extern int x[2];`) through `symbol+offset`. Match the declaration to how retail addresses it.
  - Globals shared with interrupt handlers are `volatile` (stores stay out of delay slots).
  - `-O2` reorders and schedules instructions, including delay slots. Statement order matters less than data flow, but it still matters.
  - `-fno-exceptions`: no try/catch, no destructors that need unwinding.
- Sony SDK functions (libdma, libgraph, kernel) are C: declare them `extern "C"` in their SDK header (`sce.h`). SDK macros such as `ExitHandler()` live in their own headers (`eekernel.h`).

## Workflow for one function

1. **Pick a target.** It must be a named function in a `cpp` subsegment, still `INCLUDE_ASM`, and not padding (rule 4).
2. **Gather context before writing anything.**
   - Generated asm: `code/_generated/.../<file>/<function>.s`. This is the source of truth.
   - Ghidra project: decompile, callers, xrefs, struct types (`/DL` types are PS2 layouts).
   - PS3 decomp (`NPEA00385`): usually has the real variable names, struct field names and control flow. Field offsets differ from PS2, so use it for names and logic, not offsets.
   - Deadlocked (DL) symbols: real names, real prototypes (mangled names in `all_funcs.tsv`) and PS2 struct layouts.
3. **Write the prototype first.** It needs real parameter names and real types (struct pointers, not `int`). The prototype decides the mangled name, so it has to be right before the body matters.
4. **Write the body.** Write clean code (see "Code style"), then iterate on the source until the bytes match.
5. **Verify** (see below).
6. **Update shared state.** Put new structs and fields in headers and give globals their names. Fix prototypes and symbol names everywhere they are used.

## Symbols and mangling

EE GCC 2.95 uses the **old GNU v2 mangling scheme**, not the Itanium one modern tools produce. Examples:

```
void Camera_Exit(UpdateCam *cam)                 -> Camera_Exit__FP9UpdateCam
void MB_randVector(vec4 &v, float min, float max) -> MB_randVector__FR4vec4ff
int  memcard_Update(void)                        -> memcard_Update__Fv
```

The parts of a v2 name:
- **Prefix:** `name__F` for a free function.
- **Base types:** `v` (void, only for an empty list), `c` (char), `Uc`, `s`, `Us`, `i`, `Ui`, `l`, `Ul`, `x` (long long), `Ux`, `f`, `d`, `b` (bool).
- **Pointers and qualifiers:** `P` (pointer), `R` (reference), `C` (const).
- **Named types:** `<length><Name>`, e.g. `9UpdateCam`.
- **Repeats:** `T<n>` repeats parameter n (1-based), and `N<count><n>` repeats parameter n count times. Get these right, because they are where hand mangling usually goes wrong.

Rules:
- Every C++ function in `symbols.txt` gets its **mangled** name once it is decompiled, and every reference to it uses that name.
- While a function is still `INCLUDE_ASM`, its symbol is whatever splat uses. When you decompile it, change the symbol to the mangled name and update the `INCLUDE_ASM` lines and asm references that still use the old name.
- Confirm a mangled name with the real compiler: compile a file containing the prototype and `&Function`, then read the symbol from the `.s` or `.o`. DL's `all_funcs.tsv` mangled names are correct when the signature is the same.
- Do not demangle or remangle with modern `c++filt`. It no longer understands v2.

## Code style

- **Names:** real, descriptive names everywhere: functions, parameters, locals, struct fields, globals. No one- or two-character names (`i`, `p`, `v`, `fp`, `t1`). Loop counters too: use `moby_index`, `slot`, `channel`. Take names from PS3 or DL when they exist. Otherwise describe the role (`targetMoby`, `fadeTimer`).
- **Structs:** use real structs, never raw offsets. No `*(int *)(moby + 0x20)`; write `moby->state`. If a field is missing, add it to the struct with a name and a correct offset comment. Unknown fields get `unk_<offset>` names until their meaning is known. Never leave magic offsets in code.
- **Globals:** every global you touch gets a real name and a correct type in a header, plus its address in `symbols.txt`. No `D_0015F40C` left in finished code.
- **Constants:** use enums and `#define`s for oClasses, states, flags and button masks. Don't write `if (state == 7)`.
- **Spacing:** separate each logical step of a function with a blank line, e.g. setup, the loop, the result. Code should read top to bottom in short paragraphs:
  ```cpp
  void Camera_Exit(UpdateCam *camera)
  {
      CameraBlender *blender = &camera->blender;

      blender->activeCamera = NULL;
      blender->blendTime = 0.0f;

      if (camera->exitFunc != NULL)
          camera->exitFunc(camera);

      ResetCameraShake();
  }
  ```
- **Braces:** an `if`/`else` branch with a single statement has no braces, and each branch of an `if`/`else if`/`else` chain is separated by a blank line. Branches with more than one statement keep their braces.
- **Line wrapping:** do not wrap a statement across lines unless it is absolutely justified. A single statement that fits on one line (the project limit is 100 columns) stays on one line; do not let a formatter break an assignment or a call across 3-4 lines. Only wrap when the line would truly exceed the limit. An `else` with a single statement is `else` on its own line, then the statement indented under it, with the statement itself on one line if it fits.
  ```cpp
  if (slots == POINT_LIGHT_SLOTS_EMPTY)
      tie->point_lights = light | 0xFFF0;

  else if ((slots & 0xFFF0) == 0xFFF0)
      tie->point_lights = (slots & 0xFF0F) | (light << 4);

  else
      entry--;
  ```
- **Control flow:** write it naturally, with early returns where the original logic has them, `for` loops with real bounds and `switch` for jump tables. No `goto` unless the original control flow really needs it.
- **Comments:** short, and say why rather than what. Note anything non-obvious, such as a field whose meaning is a guess.

## Verifying

1. **Compile only the file** and compare the function's object bytes to the original slice: same start offset inside `.text`, same size, same bytes.
2. **Full overlay build:** `make split-novalis && make novalis` must print `novalis: OK` (the rebuilt `overlay.elf` is byte-identical to `assets/levels/1_novalis/overlay.elf`). Run it after every function. This also checks string literals, data placement and every relocation.
3. **Data carve-outs:** when a matched file gains string literals (`.rodata`) or initialized small globals (`.sdata`), add a `.rodata`/`.sdata` subsegment for that file at its original address in `config/novalis/novalis.yaml` (see vuchain). The literals only line up once every function in the file that uses strings is decompiled.
4. If a change touches a shared header (a struct or a prototype), rebuild everything that includes it.

## When it doesn't match

- Typical small differences and what usually causes them:
  - Register swaps: expression order or which value lives in a variable.
  - An extra or missing `move`: a temporary that the original did not have, or the reverse.
  - Branch shape: `if`/`else` order, or `while` versus `for`.
  - `$gp` versus `lui`: a global declared with the wrong size.
  - Wrong callee prototypes. Check every called function against its DL prototype, because a wrong declaration changes the caller's code even when the call itself looks right:
    - Return type: a call declared `void` that really returns `int` leaves `$v0` free, so a nearby temporary lands in `v0` instead of `v1` (`FontPrintCenter` returns `int`).
    - Parameter order: EABI fills int and float argument registers separately, so a wrong order can still put every argument in the right register. But the scheduler breaks ties by argument order, so the argument moves around the `jal` come out in a different order (`Hud_DrawRotatedSprite16(float cx, float cy, float width, float height, float theta, int texW, int texH, unsigned long tex0)`).
- Try natural rewrites only: different but equally readable code. Rule 3 applies.
- If the function still does not match, leave it as `INCLUDE_ASM` with a short note under `../decomp_state/notes/<file>_<function>.md` (next to the repository) giving the closest attempt, the remaining diff and the ideas already tried. A clean note is better than a hacked match.

## Overlay specifics (Novalis and other levels)

- Each level overlay is loaded over the boot ELF's level region (from 0x15EF00), so overlay addresses overlap boot level-code addresses. Always check which binary a symbol belongs to. Resident core code (below 0x15EF00) is shared, and its names come from the boot project.
- Some overlay files are identical to boot files (for example `movie/*` and `shadowproc`). Reuse the boot source rather than decompiling twice.
- Moby update code is one file per class (`game/update/moby<oClass>.cpp`). Helpers before an `UpdateMoby_<N>` belong to that file and are named `M<oClass>_<Behavior>`, e.g. `M773_HandleStepping`.

## Known shortcomings

- **Small-data threshold is `-G16`.** String literals and initialized globals of up to 16 bytes go to `.sdata`; longer strings go to `.rodata`. So a file's short labels sit in the small-data zone next to its small variables, and its long messages sit in its `.rodata` carve. Write them as plain literals.
  - Retail code did not treat every 9–16-byte extern as small data. If a matched function's codegen changes because GCC now thinks an extern is small (it stops keeping the base address in a register, or moves a store into a delay slot), declare the extern the way retail evidently did. For arrays, leave the size out (`extern float TfragDists[];`, `extern char CollJointCacheKeys[];`, with a `#define` for any `sizeof`). For 16-byte core structs such as `Vec4` globals, add `__attribute__((section(".data")))` to the extern declaration (`LightDirection`, `HeroPosition`, `camPosOffset`, `MobyVu1HeaderData`). Core globals far from the overlay's `$gp` fail to link otherwise.
  - `freeze`: its strings are still extern data symbols carved as raw data, from before the flag change.

## Commits

- One commit per matched function, with the message `match FunctionName` (the plain, unmangled name). Nothing else in the message: no description, no trailers, no attribution.
- Supporting changes (new headers, struct fields, global names, symbol renames) go in the same commit as the function that needs them, or in their own short commit (`add framebuf header`, `rename currentLevelId to Level`).
- Never commit a symbol rename for a function that is still `INCLUDE_ASM`; the split depends on those names.
- Work on one branch per source file. Pull requests are opened by the maintainer, not by agents.
- At the end of every session, before the maintainer merges, run `python3 tools/progress.py` (after `make split-novalis`) and commit the updated `README.md` as `update progress`.
