/* K&R exercise 2-10: write a function lower(c) that converts the
 * character c to lower case if it is upper case, using a conditional
 * expression instead of if-else.
 *
 * Approach: this was already using a conditional expression; the only
 * problem was the bound on the range check.
 *
 * Original bug: `z>'A' && z<='Z'` excludes 'A' itself (strict `>`
 * instead of `>=`), so lower('A') incorrectly returned 'A' unchanged.
 */
#include <stdio.h>

char lower(char c);

char lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

#ifndef UNIT_TEST
int main(void)
{
    char a[] = "WelCOMe MY name IS cal";
    int r = 0;

    while (a[r] != '\0') {
        printf("Lower case of '%c' is '%c'.\n", a[r], lower(a[r]));
        r++;
    }
    return 0;
}
#endif
