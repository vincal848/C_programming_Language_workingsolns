/* K&R exercise 5-1: rewrite the function getint, from the pushback-
 * buffer example earlier in the chapter, to use a conditional
 * expression instead of if-else for the sign test.
 *
 * Approach: getch/ungetch are the standard single-character pushback
 * pair (a small static buffer that getch drains before falling back
 * to getchar). getint uses sign = (c == '-') ? -1 : 1 as asked; the
 * rest of its structure follows the book's version, including pushing
 * the terminating character back so the caller can read it next, and
 * handling a lone '+'/'-' with no digits after it by pushing the
 * offending character back and reporting "not a number".
 *
 * Original bug: `sign = (c == '+' || c == '-') { ... }` is not valid
 * C -- it reads like an attempt at an if-statement with the `if` and
 * the `?:` both missing, so this didn't compile, and there was no
 * getch/ungetch or main to run it against anyway.
 */
#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

static char buf[BUFSIZE];
static int bufp = 0;

int getch(void);
void ungetch(int c);
int getint(int *pn);

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        fprintf(stderr, "ungetch: too many characters pushed back\n");
    else
        buf[bufp++] = (char)c;
}

int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()))
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
        c = getch();

    if (!isdigit(c)) {
        if (c != EOF)
            ungetch(c);
        return 0;
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}

#ifndef UNIT_TEST
int main(void)
{
    int n, c;

    while ((c = getint(&n)) != EOF) {
        if (c == 0)
            getch(); /* not a number; discard the offending character and move on */
        else
            printf("%d\n", n);
    }

    return 0;
}
#endif
