/* K&R exercise 2-3: write the function htoi(s), which converts a
 * string of hexadecimal digits (optionally preceded by 0x or 0X) into
 * its equivalent integer value.
 *
 * Approach: keep the original's flag-controlled scan loop (a local
 * "still scanning hex digits" flag instead of a for-loop with a
 * condition clause), but fix it so the digit-accumulation loop always
 * runs over whatever is left of the string, regardless of whether a
 * "0" prefix was present.
 *
 * Original bugs: `line[i] == 'x' || line[i] == 'x'` checked the same
 * thing twice instead of checking for 'x' or 'X'; `for(h==1; ++i)` is
 * not a loop with a real condition (h==1 is a no-op comparison used as
 * the init clause); and the whole digit-scanning loop was nested
 * inside `if (line[i] == '0')`, so a hex string with no leading 0 (for
 * example "ff") never got scanned at all and returned 0.
 *
 * The result is unsigned long, not int: 8 or more hex digits overflowed
 * int (undefined behaviour). Unsigned arithmetic wraps by definition, so
 * input past the width of unsigned long is wrong but never UB.
 */
#include <stdio.h>

unsigned long htoi(const char line[]);

unsigned long htoi(const char line[])
{
    int i, digit, scanning;
    unsigned long x;

    i = 0;
    x = 0;

    if (line[i] == '0') {
        i++;
        if (line[i] == 'x' || line[i] == 'X')
            i++;
    }

    scanning = 1;
    while (scanning) {
        if (line[i] >= '0' && line[i] <= '9')
            digit = line[i] - '0';
        else if (line[i] >= 'a' && line[i] <= 'f')
            digit = line[i] - 'a' + 10;
        else if (line[i] >= 'A' && line[i] <= 'F')
            digit = line[i] - 'A' + 10;
        else
            scanning = 0;

        if (scanning) {
            x = 16 * x + (unsigned long)digit;
            i++;
        }
    }

    return x;
}

#ifndef UNIT_TEST
int main(void)
{
    char text[64];
    unsigned long a;

    printf("Enter a hexadecimal string: ");
    if (scanf("%63s", text) != 1)
        return 0;

    a = htoi(text);
    printf("Integer value: %lu\n", a);

    return 0;
}
#endif
