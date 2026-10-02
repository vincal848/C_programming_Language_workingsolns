# C_programming_Language_workingsolns

[![tests](https://github.com/vincal848/C_programming_Language_workingsolns/actions/workflows/tests.yml/badge.svg)](https://github.com/vincal848/C_programming_Language_workingsolns/actions/workflows/tests.yml)

This came out of working through Kernighan & Ritchie's *The C Programming
Language* as a learner. The original commits were written and pushed
straight from a tutorial-style pass through the exercises, with no way to
check later whether any of them actually ran.

I have since rebuilt it: every exercise lives in its own file under a
chapter directory, every function the book asks for is unit tested, every
program with deterministic output has a golden I/O test, and the originals
are kept in `legacy/` for reference.

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

| Exercise | File | Task |
|---|---|---|
| 1-2 | `chapter1/ex1_02.c` | Effect of an undefined escape sequence (`\c`) in a printf string |
| 1-4 | `chapter1/ex1_04.c` | Celsius-to-Fahrenheit table with a heading |
| 1-6 | `chapter1/ex1_06.c` | Verify that `getchar() != EOF` is 0 or 1 |
| 1-13 | `chapter1/ex1_13.c` | Horizontal histogram of word lengths |
| 1-24 | `chapter1/ex1_24.c` | Rudimentary syntax checker: brackets, quotes, escapes, comments |
| 2-1 | `chapter2/ex2_01.c` | Ranges of char, short, int and long, signed and unsigned |
| 2-2 | `chapter2/ex2_02.c` | Input loop without `&&` or `\|\|` |
| 2-3 | `chapter2/ex2_03.c` | `htoi`: hex string to integer, optional `0x`/`0X` prefix |
| 2-4 | `chapter2/ex2_04.c` | `squeeze(s1, s2)`: delete every character of s1 found in s2 |
| 2-10 | `chapter2/ex2_10.c` | `lower(c)` with a conditional expression |
| 3-1 | `chapter3/ex3_01.c` | Binary search with one test inside the loop, timed against the two-test version |
| 3-2 | `chapter3/ex3_02.c` | `escape`/`unescape`: newline and tab to visible escapes and back |
| 3-3 | `chapter3/ex3_03.c` | `expand`: shorthand like `a-z` to the full range |
| 5-1 | `chapter5/ex5_01.c` | `getint` with a conditional expression for the sign test |

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
| `legacy/` | The original versions of each exercise, kept for reference. |
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
