/* SUPERSEDED. Kept for reference only -- this file is not part of the
 * build and is known to be incorrect.
 *
 * 1. The printf call is missing a closing parenthesis, and the
 *    expression `(ch = getchar() != EOF, ch)` binds `!=` tighter than
 *    `=`, so `ch` ends up holding the 0/1 result of the comparison
 *    instead of the character read -- not what exercise 1-6 ("verify
 *    that the expression getchar() != EOF is 0 or 1") needs to print
 *    both the flag and the original character. File does not compile
 *    as written. Pinned by tests/ex1_06.out.
 *
 * Replaced by chapter1/ex1_06.c.
 */

# include <stdio.h>

int main(void) {
  char ch;

  printf("Press a key to check : ");

  printf("The value of the expression is: %d for the input %c.\n", (ch = getchar() != EOF, ch);

  return 0;
}
