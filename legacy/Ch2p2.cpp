/* SUPERSEDED. Kept for reference only -- this file is not part of the
 * build and is known to be incorrect.
 *
 * 1. `break; text[i++] = c;` -- the store is written after the break,
 *    so it is dead code. There is no `text[i++] = c` anywhere else in
 *    the loop either, so ordinary characters are never written into
 *    the array at all.
 * 2. `text[i] = '\0'; printf(...); return 0;` sit inside the while
 *    loop body (not after it), so main reads one character, then
 *    unconditionally null-terminates at index 0, prints an empty
 *    string, and returns -- regardless of what that first character
 *    was. The loop never iterates more than once.
 *
 * Exercise 2-2 asks for a loop equivalent to
 *   for (i = 0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
 * that avoids && and ||; the intent survives in the comment but the
 * body never implements it.
 *
 * Replaced by chapter2/ex2_02.c, pinned by tests/ex2_02.out.
 */

/* Equivalent/Original Code: for(i = 0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i) */

#include <stdio.h>

int main(void) {
  int i, lim, c;
  i = 0;
  lim = 81;
  char text[81];
  printf("Enter Text:\n\n");
  while(i < (lim-1)){
    c = getchar();
    if (c == EOF){
      break;
    } else if (c=='\n') {
      break;
      text[i++] = c;
    }
    text[i] = '\0';
    printf("The input text is: %s.\n",text);
    return 0;
  }
}
