/* K&R exercise 1-24: write a program to check a C program for
 * rudimentary syntax errors, such as unbalanced parentheses, brackets,
 * and braces. Don't forget quotes (single and double), escape
 * sequences within them, and comments.
 *
 * This one was never attempted in the original repo -- the file was
 * committed empty. Approach: read the source a character at a time,
 * push each opening ( [ { onto a stack with the line it was seen on,
 * and pop/compare on each closing one; skip the contents of slash-
 * slash and slash-star comments and of '...' and "..." literals
 * (honoring backslash escapes) so brackets that appear inside them
 * are not counted. Report unmatched closers immediately and any
 * still-open brackets once the input ends.
 */
#include <stdio.h>

#define STACKSIZE 256

static int errors = 0;

static void report(int line, const char *msg)
{
    fprintf(stderr, "line %d: %s\n", line, msg);
    errors++;
}

int check_syntax(FILE *fp)
{
    char stack[STACKSIZE];
    int stacklines[STACKSIZE];
    int top = 0;
    int line = 1;
    int c;

    errors = 0;

    while ((c = getc(fp)) != EOF) {
        if (c == '\n') {
            line++;
            continue;
        }

        if (c == '/') {
            int c2 = getc(fp);
            if (c2 == '*') {
                int prev = 0;
                int startline = line;
                int closed = 0;
                while ((c = getc(fp)) != EOF) {
                    if (c == '\n')
                        line++;
                    if (prev == '*' && c == '/') {
                        closed = 1;
                        break;
                    }
                    prev = c;
                }
                if (!closed)
                    report(startline, "unterminated /* comment");
                continue;
            } else if (c2 == '/') {
                while ((c = getc(fp)) != EOF && c != '\n')
                    ;
                if (c == '\n')
                    line++;
                continue;
            } else if (c2 != EOF) {
                ungetc(c2, fp);
            }
        }

        if (c == '\'' || c == '"') {
            int quote = c;
            int startline = line;
            int closed = 0;
            while ((c = getc(fp)) != EOF && c != '\n') {
                if (c == '\\') {
                    c = getc(fp);
                    if (c == EOF)
                        break;
                    continue;
                }
                if (c == quote) {
                    closed = 1;
                    break;
                }
            }
            if (!closed)
                report(startline, quote == '"' ?
                       "unterminated \" string" : "unterminated ' character literal");
            continue;
        }

        if (c == '(' || c == '[' || c == '{') {
            if (top < STACKSIZE) {
                stack[top] = (char)c;
                stacklines[top] = line;
                top++;
            }
            continue;
        }

        if (c == ')' || c == ']' || c == '}') {
            char want = (c == ')') ? '(' : (c == ']') ? '[' : '{';
            if (top == 0) {
                report(line, "unmatched closing bracket");
            } else if (stack[top - 1] != want) {
                report(line, "mismatched bracket");
                top--;
            } else {
                top--;
            }
            continue;
        }
    }

    while (top > 0) {
        report(stacklines[top - 1], "unclosed bracket at end of file");
        top--;
    }

    return errors;
}

#ifndef UNIT_TEST
int main(void)
{
    int n = check_syntax(stdin);

    if (n == 0)
        printf("no syntax errors found\n");
    else
        printf("%d syntax error(s) found\n", n);

    return n == 0 ? 0 : 1;
}
#endif
