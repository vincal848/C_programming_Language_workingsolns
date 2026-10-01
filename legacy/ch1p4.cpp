/* SUPERSEDED. Kept for reference only -- this file is not part of the
 * build and is known to be incorrect.
 *
 * 1. `printf("-------\t-------\n")';` -- a stray `';` after the closing
 *    paren does not parse. This is a straight copy-paste typo; the file
 *    does not compile. Pinned by tests/ex1_04.out (the program now
 *    actually runs and produces the table).
 *
 * Replaced by chapter1/ex1_04.c.
 */

#include <stdio.h>

int main(void) {
  float ft, cel;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  printf("Celsius\tFahr\n");
  printf("-------\t-------\n")';
  cel = lower;
  while (cel <= upper)
    {
      ft = cel * (9.0 / 5.0) + 32.0;
      printf("%3.0f\t%6.1f\n", cel, ft);
      cel = cel + step;
    }
  getchar();
  return 0;
}
