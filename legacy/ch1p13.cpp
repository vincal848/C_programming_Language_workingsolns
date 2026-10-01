/* SUPERSEDED. Kept for reference only -- this file is not part of the
 * build and is known to be incorrect.
 *
 * 1. `if word[i] >= res){` is missing its opening parenthesis around
 *    the condition -- does not compile.
 * 2. The two histogram-printing `for` loops and the bar-drawing loop are
 *    nested and braced incorrectly: closing braces are missing/misplaced
 *    so the printing loops end up inside the word-reading `while`, and
 *    a `putchar`/`printf("\n")` sits inside the bar loop instead of
 *    after it, which would print a newline after every single star.
 * 3. `res =++ word[lenofword-1];` and `res =++ word[MAX];` read as
 *    `res = (++word[...])`, which does increment the right bucket, but
 *    combined with bug 2 the counts it prints never match what was
 *    counted, and the whole program never reaches a working state to
 *    check.
 *
 * Replaced by chapter1/ex1_13.c, which counts word lengths into an
 * array first and only then prints the histogram, pinned by
 * tests/ex1_13.out.
 */

#include <stdio.h>

#define MAX 10

int main(void) {
  long word[MAX + 1];
  char letchar;
  int i, a, s1, lenofword, res, maxres, count;
  lenofword = res = maxres = count = 0;
  a = 0;

  for(i = 0; i <= MAX; i++)
    printf("Enter Text, Ctrl+Z exits \n\n");
  while (a==0) {
    letchar = getchar();
    if(letchar == ' ' || letchar == '\t' || letchar == '\n' || letchar == EOF) {
      if (count == 0) {
        s1 = 0;
        count = 1;
        if(lenofword <= MAX) {
          if(lenofword >0) {
            res =++ word[lenofword-1];
            if(res > maxres){
              maxres = res;
            }
        }
      }
      else {
        res =++ word[MAX];
        if(res > maxres){
          maxres = res;
        }
        if(letchar == EOF) {
          a = 1;
        }
      }
    }
    else {
      if(count ==1 || s1 == 1) {
        s1 = 0;
        lenofword = 0;
        count = 0;
      }
      ++lenofword;
    }
  }
for(res = maxres; res > 0; res--) {
  printf("%4d    |  ", res);
  for(i = 0; i <= MAX; i++) {
    if word[i] >= res){
      printf("*   ");
    }
    else {
      printf("    ");
    }
    printf("\n");
  }
  printf("     +");
  for(i = 0; i < MAX; i++){
    printf("---");
    printf("\n      ");
  }
  for(i = 0; i < MAX; i++){
    printf(" >%d\n", MAX);
  }
}
    return 0;
}
