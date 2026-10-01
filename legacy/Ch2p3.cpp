/* SUPERSEDED. Kept for reference only -- this file is not part of the
 * build and is known to be incorrect.
 *
 * 1. `line[i] == 'x' || line[i] == 'x'` checks the same thing twice;
 *    it should be 'x' or 'X' to accept an uppercase 0X prefix.
 * 2. `for(h==1; ++i){` -- `h==1` is a comparison used as the init
 *    clause (it does nothing useful, and is not even assignment), and
 *    there is no loop condition, so this is really an infinite `for`
 *    relying on `h` being set to 0 inside the body to end it via...
 *    nothing, since a `for` with an empty middle clause never checks
 *    `h` at all. Combined with the missing increment of `i` on the
 *    fall-through path this does not reliably terminate or scan past
 *    the first bad character correctly. Does not compile cleanly as a
 *    well-formed for-statement in the way intended either.
 * 3. The digit-accumulation loop is only reachable when the string
 *    starts with '0' (it's nested inside `if (line[i] == '0')`), so
 *    a bare hex string like "ff" (no leading 0) returns 0 instead of
 *    255.
 *
 * Replaced by chapter2/ex2_03.c, pinned by the test_htoi() cases in
 * tests/unit_tests.c.
 */

#include <stdio.h>

int htoi(char[]);

int main(void) {
  char text[10];
  int a;

  printf("Enter hexa decimal string: ");
  scanf("%s", text);
  a = htoi(text);

  printf("\nInteger value for given hexa is: %d \n", a);
  return 0;
}

int htoi(char line[]) {
  int digit, i = 0, h, x;
  if (line[i] == '0'){
    ++i;
    if(line[i] == 'x' || line[i] == 'x') {
      i++;
    }
    x = 0;
    h = 1;
    for(h==1; ++i){
      if(line[i] >= '0' && line[i] <= '9') {
        digit = line[i] - '0';
      } else if(line[i] >= 'a' && line[i] <= 'f') {
        digit = line[i] - 'a' + 10;
      } else if(line[i] >= 'A' && line[i] <= 'F') {
        digit = line[i] - 'A' + 10;
      } else {
        h = 0;
      }
      if(h == 1) {
        x = 16 * x + digit;
      }
    }
  }
  return x;
}
