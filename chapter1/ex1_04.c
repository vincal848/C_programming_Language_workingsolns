/* K&R exercise 1-4: write a program to print a Celsius-to-Fahrenheit
 * table (the mirror image of the Fahrenheit-to-Celsius table built
 * earlier in the chapter), with a heading above the columns.
 *
 * Approach: same shape as the book's Fahrenheit-to-Celsius loop, just
 * swapping which side is the independent variable.
 *
 * Original bug: a stray `';` left over after the header printf's
 * closing paren, which doesn't parse.
 */
#include <stdio.h>

int main(void)
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("Celsius\tFahr\n");
    printf("-------\t-------\n");

    celsius = lower;
    while (celsius <= upper) {
        fahr = celsius * (9.0 / 5.0) + 32.0;
        printf("%3.0f\t%6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }

    return 0;
}
