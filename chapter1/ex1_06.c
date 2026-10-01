/* K&R exercise 1-6: verify that the expression getchar() != EOF is 0
 * or 1.
 *
 * Approach: read one character and print both the character and the
 * value of the comparison, so a reader can see it's always 0 or 1
 * regardless of what was typed.
 *
 * Original bugs: a missing closing parenthesis on the printf call, and
 * `(ch = getchar() != EOF, ch)` -- `!=` binds tighter than `=`, so ch
 * ended up holding the 0/1 comparison result instead of the character
 * that was read, which defeats the point of printing both.
 */
#include <stdio.h>

int main(void)
{
    int c;

    printf("Press a key, then Enter: ");
    c = getchar();
    printf("The value of (c != EOF) is %d for the input character '%c'.\n",
           c != EOF, c);

    return 0;
}
