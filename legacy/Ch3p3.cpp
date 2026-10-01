/* SUPERSEDED. Kept for reference only -- this file is not part of the
 * build and is known to be incorrect.
 *
 * 1. `int i = 0; j = 0;` declares `i` but not `j` -- `j` is undeclared.
 * 2. `char = c;` is missing the variable name between the type and
 *    the assignment; it should be `char c;`.
 * 3. `int main(0 {` has a stray `0` and a missing `)` -- should be
 *    `int main(void) {`.
 * 4. `printf("Enter the input strinf: ");` is missing its terminating
 *    semicolon.
 * 5. `expand`'s closing brace is missing, so it and `main` are not
 *    properly separated (the function body runs into the next
 *    declaration).
 * 6. `s2[j++] = '\0';` sits *inside* the while loop, so the string
 *    gets re-terminated (and j incorrectly advanced) after every
 *    character copied, instead of exactly once after the loop.
 *
 * Replaced by chapter3/ex3_03.c, pinned by the test_expand() cases in
 * tests/unit_tests.c.
 */

#include <stdio.h>
#include <ctype.h>

void expand(const char s1[], char s2[]) {
  int i = 0; j = 0;
  char = c;

  while ((c = s1[i++]) != '\0') {
    if (s1[i] == '-' && s1[i + 1] >= c) {
      char start = c;
      char end = s1[i + 1];
      if ((isalpha(start) && isalpha(end)) || (isdigit(start) && isdigit(end))) {
                i += 2;
                for (char k = start; k <= end; k++) {
                    s2[j++] = k;
                }
      } else {
        s2[j++] = c;
      }
    } else {
      s2[j++] = c;
    }

    s2[j++] = '\0';
}

int main(0 {
  char s1[100], s2[100];
  printf("Enter the input strinf: ");
  scanf("%99s", s1);

  expand(s1, s2);
  printf("Expanded string: %s\n", s2);

  return 0;
}
