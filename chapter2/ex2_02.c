/* K&R exercise 2-2: write a loop equivalent to
 *   for (i = 0; i < lim-1 && (c = getchar()) != '\n' && c != EOF; ++i)
 *       s[i] = c;
 * that does not use && or ||.
 *
 * Approach: replace each condition in the chained && with a separate
 * if-break, which is the standard way to drop short-circuit operators
 * without changing what gets tested.
 *
 * Original bugs: the store `text[i++] = c` was written after a break
 * (dead code, and not present anywhere reachable), and
 * `text[i] = '\0'; printf(...); return 0;` sat inside the loop body
 * instead of after it, so the loop only ever ran for (at most) one
 * character before returning.
 */
#include <stdio.h>

#define MAXLINE 81

int main(void)
{
    char text[MAXLINE];
    int i, c;

    printf("Enter text:\n");

    i = 0;
    while (i < MAXLINE - 1) {
        c = getchar();
        if (c == '\n')
            break;
        if (c == EOF)
            break;
        text[i] = c;
        i++;
    }
    text[i] = '\0';

    printf("The input text is: %s\n", text);

    return 0;
}
