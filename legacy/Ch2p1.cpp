/* SUPERSEDED. Kept for reference only -- this file is not part of the
 * build, though it was actually fine as written.
 *
 * No defects found by the survey: it compiles and prints the limits.h
 * constants correctly. Moved as-is to chapter2/ex2_01.c (reformatted to
 * house style, main() wrapped with the usual exercise-statement
 * comment), pinned by tests/ex2_01.out.
 */

#include <stdio.h>
#include <limits.h>

int main(void) {
  printf("signed char max = %d\n", SCHAR_MAX);
  printf("signed char min = %d\n", SCHAR_MIN);
  printf("signed short max = %d\n", SHRT_MAX);
  printf("signed short min = %d\n", SHRT_MIN);
  printf("signed int max = %d\n", INT_MAX);
  printf("signed int min = %d\n", INT_MIN);
  printf("signed long max = %ld\n", LONG_MAX);
  printf("signed long min = %ld\n", LONG_MIN);
  printf("unsigned char max = %u\n", UCHAR_MAX);
  printf("unsigned short max = %u\n", USHRT_MAX);
  printf("unsigned int max = %u\n", UINT_MAX);
  printf("unsigned long max = %lu\n", ULONG_MAX);
  return 0;
}
