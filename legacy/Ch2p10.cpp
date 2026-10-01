/* SUPERSEDED. Kept for reference only -- this file is not part of the
 * build and is known to be incorrect.
 *
 * 1. `z>'A' && z<= 'Z'` excludes 'A' itself (strict `>` instead of
 *    `>=`), so lower('A') incorrectly returns 'A' unchanged instead of
 *    'a'. Pinned by the test_lower() case in tests/unit_tests.c.
 *
 * Replaced by chapter2/ex2_10.c.
 */

#include <stdio.h>

char lower(char);

int main(void) {
  char a[] = "WelCOMe MY name IS cal", ch;
  int r = 0;

  while(a[r] != '\0') {
    ch = lower(a[r]);
    printf("Lower case letter of  '%c' is '%c'.\n", a[r], ch);
    r++;
  }
  return 0;
}

char lower(char z) {
  return z>'A' && z<= 'Z' ? z + 'a' - 'A' :z;
}
