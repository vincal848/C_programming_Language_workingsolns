/* SUPERSEDED. Kept for reference only -- this file is not part of the
 * build and is known to be incorrect (or, in this case, intentionally
 * ambiguous in a way the original author did not call out).
 *
 * 1. The `\c` escape sequence used on the second printf is not one of
 *    the escape sequences C defines. That is in fact the point of K&R
 *    exercise 1-2 ("find out what happens when printf's argument string
 *    contains \c"), but the original had no comment explaining this, so
 *    it reads like an accident rather than the experiment it is.
 *    Pinned by chapter1/ex1_24 -- no, see tests/ex1_02.out, which
 *    records the actual observed behavior of the local toolchain.
 * 2. No "note on approach" or exercise statement, so a reader has no
 *    way to tell this was deliberate.
 *
 * Replaced by chapter1/ex1_02.c.
 */



#include <stdio.h>

int main(void)
{
  printf("Experiment to test a non-escape sequence character.\n");

  printf("Using c as escape sequence character: \c");

  return 0;
}

