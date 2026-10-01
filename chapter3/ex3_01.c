/* K&R exercise 3-1: our binary search makes two tests inside the loop
 * for every iteration, when one test would suffice (at the price of
 * more tests outside the loop). Rewrite binsearch to use only one
 * test inside the loop, and measure the difference in run time.
 *
 * Approach: keep both versions side by side -- binsearch1 is the
 * textbook three-way version (less/greater/equal, two comparisons per
 * iteration), binsearch2 moves the equality check into the loop
 * condition so the body only ever makes one comparison. By default the
 * program just reports where a handful of fixed values are found by
 * each function, which is deterministic and good for a golden test;
 * pass -t to also run both functions 60000 times and print timing.
 *
 * Original bugs: the two timing lines reported different, incompatible
 * units -- the first cast elapsed_time to double and divided by
 * CLOCKS_PER_SEC for a seconds figure, the second passed the truncated
 * integer division straight to %lu without even casting it, so it
 * almost always printed 0 or 1 "seconds" instead of a real duration.
 * Also, binsearch2's final check re-read arr[m] after the loop ended
 * instead of asking why the loop ended; it happened to stay in bounds
 * here, but that was incidental to how start/end converge, not
 * something the code demonstrated it could rely on.
 */
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 20000
#define TRIALS 60000

int binsearch1(int x, int arr[], int n);
int binsearch2(int x, int arr[], int n);

int binsearch1(int x, int arr[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < arr[mid])
            high = mid - 1;
        else if (x > arr[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int binsearch2(int x, int arr[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (low + high) / 2;
    while (low <= high && x != arr[mid]) {
        if (x < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
        mid = (low + high) / 2;
    }
    if (low <= high)
        return mid;
    return -1;
}

#ifndef UNIT_TEST
int main(int argc, char *argv[])
{
    static int test[MAX];
    int i, pos1, pos2;
    int targets[] = {0, 1, 100, MAX - 1, MAX, -5};
    int ntargets = (int)(sizeof(targets) / sizeof(targets[0]));
    int timing = argc > 1 && strcmp(argv[1], "-t") == 0;

    for (i = 0; i < MAX; i++)
        test[i] = i;

    for (i = 0; i < ntargets; i++) {
        pos1 = binsearch1(targets[i], test, MAX);
        pos2 = binsearch2(targets[i], test, MAX);
        printf("value %d: binsearch1 -> %d, binsearch2 -> %d\n",
               targets[i], pos1, pos2);
    }

    if (timing) {
        clock_t start, elapsed1, elapsed2;
        int x = 100;

        start = clock();
        for (i = 0; i < TRIALS; i++)
            pos1 = binsearch1(x, test, MAX);
        elapsed1 = clock() - start;

        start = clock();
        for (i = 0; i < TRIALS; i++)
            pos2 = binsearch2(x, test, MAX);
        elapsed2 = clock() - start;

        printf("binsearch1: %lu clocks (%.5f seconds) over %d trials\n",
               (unsigned long)elapsed1, (double)elapsed1 / CLOCKS_PER_SEC, TRIALS);
        printf("binsearch2: %lu clocks (%.5f seconds) over %d trials\n",
               (unsigned long)elapsed2, (double)elapsed2 / CLOCKS_PER_SEC, TRIALS);
    }

    return 0;
}
#endif
