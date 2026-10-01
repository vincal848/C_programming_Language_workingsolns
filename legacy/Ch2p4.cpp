/* SUPERSEDED. Kept for reference only -- this file is not part of the
 * build, though the squeeze() logic itself was already correct.
 *
 * No logic defects found by the survey. Reformatted to house style
 * (brace placement, naming) as chapter2/ex2_04.c, pinned by the
 * test_squeeze() cases in tests/unit_tests.c.
 */

#include <stdio.h>

void squeeze(char str1[], char str2[]);

int main(void) {
  char str1[40];
  char str2[20];

  printf("Enter string1  : ");

  scanf("%s", str1);

  printf("Enter string2  : ");

  scanf("%s", str2);

  squeeze(str1,str2);

  printf("Modifies String  : %s\n", str1);
  return 0;
}

void squeeze(char s1[], char s2[]) {
  int i, j, k;
  for(i=k=0; s1[i] != '\0'; i++) {
    for(j = 0; s2[j] != '\0' && s2[j] != s1[i]; j++);
      if(s2[j] == '\0') {
        s1[k++] = s1[i];
      }
  }

  s1[k] = '\0';
}
