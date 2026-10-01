/* K&R exercise 3-2: write a function escape(s, t) that converts
 * characters like newline and tab into visible escape sequences such
 * as \n and \t as it copies the string t to s. Use a switch. Write a
 * function for the other direction as well, converting the escape
 * sequences back into the real characters.
 *
 * Approach: kept the original's switch-per-special-character shape for
 * escape(), and wrote unescape() as the mirror image: on seeing a
 * backslash, look at the next character to decide what real character
 * to emit.
 *
 * Original bugs: `int void escape(...)` declared two types on one
 * function; `s[j] = '\0'` was missing its semicolon; and the for
 * loop's closing brace was missing, so the terminator statement and
 * the function's closing brace did not balance. There was also no
 * main and no unescape(), so only half the exercise was attempted.
 */
#include <stdio.h>
#include <string.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

void escape(char s[], char t[])
{
    int i, j;

    for (i = j = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        case '\\':
            s[j++] = '\\';
            s[j++] = '\\';
            break;
        default:
            s[j++] = t[i];
            break;
        }
    }
    s[j] = '\0';
}

void unescape(char s[], char t[])
{
    int i, j;

    for (i = j = 0; t[i] != '\0'; i++) {
        if (t[i] == '\\') {
            switch (t[i + 1]) {
            case 'n':
                s[j++] = '\n';
                i++;
                break;
            case 't':
                s[j++] = '\t';
                i++;
                break;
            case '\\':
                s[j++] = '\\';
                i++;
                break;
            default:
                s[j++] = t[i];
                break;
            }
        } else {
            s[j++] = t[i];
        }
    }
    s[j] = '\0';
}

#ifndef UNIT_TEST
int main(void)
{
    char input[100], escaped[200], restored[100];

    printf("Enter a line: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
        return 0;
    input[strcspn(input, "\n")] = '\0';

    escape(escaped, input);
    printf("escaped:  %s\n", escaped);

    unescape(restored, escaped);
    printf("restored: %s\n", restored);

    return 0;
}
#endif
