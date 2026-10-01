/* SUPERSEDED. Kept for reference only -- this file is not part of the
 * build and is known to be incorrect.
 *
 * 1. `sign = (c == '+' || c == '-') { ... }` is not valid C: an
 *    assignment followed directly by a brace block is neither a valid
 *    ternary nor a valid if-statement (the `if` keyword and the `?:`
 *    were both dropped). Exercise 5-1 specifically asks to use `?:`
 *    for the sign test, and this is where that logic lives, so the
 *    file does not compile and the exercise is unattempted.
 * 2. There is no `getch`/`ungetch` pushback-buffer implementation and
 *    no `main`, so even if the syntax error were fixed there would be
 *    nothing to link or run.
 *
 * Replaced by chapter5/ex5_01.c, which adds getch/ungetch and a main
 * that reads integers until EOF; pinned by the test_getint() cases in
 * tests/unit_tests.c.
 */

#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getint(int *pn) {
  int c, d, sign;

  while (isspace(c = getch()));
  if(!isdigit(c) && c!=EOF && c!='+' && c!='-') {
    ungetch(c);
    return 0;
  }
  sign = (c == '+' || c == '-') {
    d = c;
    if(!isdigit(c = getch())) {
      if(c != EOF){
        ungetch(c);
      }
      ungetch(d);
      return d;
    }
  }
  for (*pn = 0; isdigit(c); c = getch()) {
    *pn = 10 * *pn + (c-'0');
  }
  *pn *= sign;
  if(c != EOF){
    ungetch(c);
  }
  return c;
}
