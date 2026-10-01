/* K&R exercise 3-3: write a function expand(s1, s2) that expands
 * shorthand notations like a-z in the string s1 into the equivalent
 * complete list abc...xyz in s2. Allow for a-z in either order, digit
 * ranges, and a leading or trailing - taken literally.
 *
 * Approach: walk s1 one character at a time; whenever the next two
 * characters are "-X" and X is a later letter or digit than the
 * current one, fill in the whole range and skip past it, otherwise
 * copy the current character literally. This naturally leaves a
 * leading or trailing '-' alone, since there's no valid range to find
 * around it.
 *
 * Original bugs: `int i = 0; j = 0;` left j undeclared; `char = c;`
 * was missing the variable name; `int main(0 {` was missing `void)`;
 * a printf call was missing its semicolon; expand()'s closing brace
 * was missing so it ran into main(); and `s2[j++] = '\0'` was inside
 * the while loop, re-terminating (and advancing j past) the string
 * after every character instead of exactly once at the end.
 */
#include <stdio.h>
#include <ctype.h>

void expand(char s1[], char s2[]);

void expand(char s1[], char s2[])
{
    int i, j;
    char c;

    i = j = 0;
    while ((c = s1[i]) != '\0') {
        if (s1[i + 1] == '-' && s1[i + 2] > c) {
            char start = c;
            char end = s1[i + 2];
            if ((isalpha(start) && isalpha(end)) ||
                (isdigit(start) && isdigit(end))) {
                char k;
                for (k = start; k <= end; k++)
                    s2[j++] = k;
                i += 3;
                continue;
            }
        }
        s2[j++] = c;
        i++;
    }
    s2[j] = '\0';
}

#ifndef UNIT_TEST
int main(void)
{
    char s1[100], s2[200];

    printf("Enter a string (ranges like a-z allowed): ");
    if (scanf("%99s", s1) != 1)
        return 0;

    expand(s1, s2);
    printf("Expanded string: %s\n", s2);

    return 0;
}
#endif
