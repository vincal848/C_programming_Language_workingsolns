/* K&R exercise 1-13: print a horizontal histogram of the lengths of
 * the words read from standard input. Words are separated by blanks,
 * tabs, or newlines; anything longer than MAXLEN is folded into the
 * last bin so one very long word can't blow up the table width.
 *
 * Approach: count lengths into an array first, then print the
 * histogram in a second pass, rather than trying to print and count in
 * the same loop.
 *
 * Original bugs: `if word[i] >= res){` was missing its opening paren;
 * the histogram-printing loops were nested and braced incorrectly
 * (closing braces missing/misplaced put them inside the word-reading
 * while loop and put a newline inside the bar-drawing loop instead of
 * after it); and the two-pass count/print split didn't exist, so there
 * was no point in the program where the counts were ever correct and
 * also visible.
 */
#include <stdio.h>

#define MAXLEN 10

int main(void)
{
    int lengths[MAXLEN + 1] = {0};
    int c, len, i, bar;

    len = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (len > 0) {
                if (len > MAXLEN)
                    len = MAXLEN;
                lengths[len]++;
            }
            len = 0;
        } else {
            len++;
        }
    }
    if (len > 0) {
        if (len > MAXLEN)
            len = MAXLEN;
        lengths[len]++;
    }

    for (i = 1; i <= MAXLEN; i++) {
        printf("%2d (%2d):", i, lengths[i]);
        if (lengths[i] > 0) {
            putchar(' ');
            for (bar = 0; bar < lengths[i]; bar++)
                putchar('*');
        }
        putchar('\n');
    }

    return 0;
}
