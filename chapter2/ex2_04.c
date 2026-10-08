/* K&R exercise 2-4: write an alternative version of squeeze(s1, s2)
 * that deletes each character in s1 that matches any character in the
 * string s2.
 *
 * Approach: this was already correct in the original -- for each
 * character of s1, scan s2 looking for a match; keep the character
 * only if s2 was scanned to its end without finding one. Reformatted
 * to house style only.
 */
#include <stdio.h>

void squeeze(char s1[], const char s2[]);

void squeeze(char s1[], const char s2[])
{
    int i, j, k;

    for (i = k = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0' && s2[j] != s1[i]; j++)
            ;
        if (s2[j] == '\0')
            s1[k++] = s1[i];
    }
    s1[k] = '\0';
}

#ifndef UNIT_TEST
int main(void)
{
    char s1[64];
    char s2[64];

    printf("Enter string 1: ");
    if (scanf("%63s", s1) != 1)
        return 0;

    printf("Enter string 2 (characters to remove from string 1): ");
    if (scanf("%63s", s2) != 1)
        return 0;

    squeeze(s1, s2);

    printf("Result: %s\n", s1);
    return 0;
}
#endif
