# C_programming_Language_workingsolns

[![tests](https://github.com/vincal848/C_programming_Language_workingsolns/actions/workflows/tests.yml/badge.svg)](https://github.com/vincal848/C_programming_Language_workingsolns/actions/workflows/tests.yml)

This came out of working through Kernighan & Ritchie's *The C Programming
Language* as a learner. The original commits were written and pushed
straight from a tutorial-style pass through the exercises, with no way to
check later whether any of them actually ran.

I have since rebuilt it: every exercise lives in its own file under a
chapter directory, every function the book asks for is unit tested, every
program with deterministic output has a golden I/O test, and the originals
are kept in `legacy/` with a comment listing exactly what was wrong with
each one. **Of the 14 files in the original repo, 10 did not compile as
written** -- missing parens and semicolons, a stray `int void` return
type, undeclared variables, mismatched braces -- and two more compiled but
had logic bugs that would have given wrong answers silently.

## At a glance

| | |
|---|---|
| Source | Kernighan & Ritchie, *The C Programming Language*, 2nd ed. |
| Exercises | 1-2, 1-4, 1-6, 1-13, 1-24, 2-1, 2-2, 2-3, 2-4, 2-10, 3-1, 3-2, 3-3, 5-1 |
| Language | C99 (`-Wall -Wextra -Werror -pedantic`) |
| Tests | `tests/unit_tests.c` (assert-based, function-level) + golden I/O pairs under `tests/` |
| Validation | gcc and clang on Linux, plus a separate AddressSanitizer/UBSan pass |
| Stack | C99, POSIX `sh`, GNU Make, GitHub Actions |

## Results

Status of every exercise after the rebuild. All 14 build clean with
`-Wall -Wextra -Werror -pedantic` (ex1_02 is the one deliberate
exception -- see below) and all tests pass on both gcc and clang.

| Exercise | File | What was wrong in the original |
|---|---|---|
| 1-2 | `chapter1/ex1_02.c` | Nothing broken; the unknown escape `\c` is the point of the exercise, just uncommented as such. |
| 1-4 | `chapter1/ex1_04.c` | Stray `';` after a printf call -- did not compile. |
| 1-6 | `chapter1/ex1_06.c` | Missing closing paren; `!=` binds tighter than `=`, so `ch` held the comparison result instead of the character read. |
| 1-13 | `chapter1/ex1_13.c` | Missing paren in an `if`; histogram-printing loops nested and braced incorrectly (inside the input loop, newline inside the bar loop); counts never matched what was printed. |
| 1-24 | `chapter1/ex1_24.c` | File was empty; exercise unattempted. Implemented as a bracket/quote/comment balance checker. |
| 2-1 | `chapter2/ex2_01.c` | No defects found; reformatted only. |
| 2-2 | `chapter2/ex2_02.c` | Character store written after a `break` (dead code); the terminate/print/return statements sat inside the read loop, so it only ever read one character. |
| 2-3 | `chapter2/ex2_03.c` | `'x' \|\| 'x'` instead of `'x'` or `'X'`; `for(h==1; ++i)` is not a real loop condition; the digit-scanning loop was nested inside `if (line[0]=='0')`, so hex strings without a leading `0` always returned 0. |
| 2-4 | `chapter2/ex2_04.c` | No logic defects found; reformatted only. |
| 2-10 | `chapter2/ex2_10.c` | `z>'A'` instead of `z>='A'`, so `lower('A')` incorrectly returned `'A'` unchanged. |
| 3-1 | `chapter3/ex3_01.c` | The two timing printfs reported incompatible units (one floating-point seconds, one truncated integer division passed to `%lu` uncast); a final bounds check re-read the array after the loop ended instead of checking why it ended. |
| 3-2 | `chapter3/ex3_02.c` | `int void escape(...)` -- two type specifiers; missing semicolon; missing closing brace; no `main`, and no `unescape()` for the reverse direction the exercise also asks for. |
| 3-3 | `chapter3/ex3_03.c` | Undeclared variable `j`; `char = c;` missing the variable name; `main(0 {` instead of `main(void) {`; missing semicolon; missing closing brace; the string terminator was written inside the loop instead of once after it. |
| 5-1 | `chapter5/ex5_01.c` | `sign = (c == '+' \|\| c == '-') { ... }` is not valid C -- the `if`/`?:` were both missing; no `getch`/`ungetch`/`main` existed to run it against. |

Run `make test` to reproduce: `all unit tests passed`, plus `PASS` for
all 8 golden I/O cases (`ex1_02`, `ex1_04`, `ex1_06`, `ex1_13`, `ex1_24`,
`ex2_01`, `ex2_02`, `ex3_01`).

## How to build/run

```sh
make            # build every exercise into build/
make test       # build, run tests/unit_tests.c, and diff golden I/O
make test-asan  # same tests, rebuilt with -fsanitize=address,undefined
make clean
```

Build a single exercise and run it directly:

```sh
make build/ex2_03
./build/ex2_03
```

`CC` defaults to `cc`; override with `make CC=clang test`.

## Repository guide

| Path | Contents |
|---|---|
| `chapter1/` .. `chapter5/` | One `.c` file per exercise (`exC_NN.c`), each starting with a paraphrase of the exercise statement and a short note on approach. |
| `tests/unit_tests.c` | Assert-based tests for every exercise that is a function (htoi, squeeze, lower, binsearch, escape/unescape, expand, getint) -- pulled in via `#include` with `UNIT_TEST` defined, which suppresses each file's own `main`. |
| `tests/*.in` / `tests/*.out` | Golden stdin/stdout pairs for the main-driven exercises, run by `tests/run_golden.sh` via `diff`. |
| `legacy/` | The original, uncompiled-as-written files, each with a header comment listing its specific defects and which test now pins the fix. |
| `Makefile` | `CC ?= cc`, `-std=c99 -Wall -Wextra -Werror -pedantic`, `all`/`test`/`test-asan`/`clean`. |
| `.github/workflows/tests.yml` | gcc/clang matrix plus a separate ASan/UBSan job. |

## Notes

- C99 throughout; no compiler extensions used.
- `chapter1/ex1_02.c` is compiled without `-Werror` (see the Makefile
  comment) because the warning it produces is the exercise, not a bug.
- `chapter2/ex2_01.c`'s limits are platform-specific; the numbers above
  are for the `x86_64-linux-gnu` LP64 ABI that CI and local testing both
  used. A 32-bit or Windows (LLP64) target would print different `long`
  bounds.
- `chapter3/ex3_01.c`'s timing output is not printed by default (it
  isn't deterministic); pass `-t` to see it.
