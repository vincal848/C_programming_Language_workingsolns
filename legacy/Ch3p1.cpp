/* SUPERSEDED. Kept for reference only -- this file is not part of the
 * build and is known to be incorrect.
 *
 * 1. The second timing printf passes `elapsed_time/CLOCKS_PER_SEC`
 *    (an integer `clock_t` division, truncated to whole clocks-per-
 *    second, i.e. almost always 0 or 1) to a `%lu` conversion without
 *    even casting it, while the matching first printf correctly casts
 *    and uses a floating-point division for the seconds figure. The
 *    two timing lines are not reporting comparable numbers, and the
 *    second one is not actually a seconds value at all.
 * 2. binsearch2's final check re-reads `arr[m]` after the loop exits
 *    instead of checking whether the loop exited because the element
 *    was found vs. because the range was exhausted; it happens to stay
 *    in-bounds here because of how start/end converge, but that is an
 *    accident of this particular loop shape, not something the code
 *    demonstrates it relies on.
 *
 * Replaced by chapter3/ex3_01.c, which prints matching, cast,
 * floating-point seconds for both functions and checks loop-exit
 * reason rather than re-indexing after the loop; pinned by the
 * test_binsearch() cases in tests/unit_tests.c and tests/ex3_01.out
 * for the non-timing part (timing output is only printed under -t).
 */

#include <stdio.h>
#include <time.h>

int binsearch1(int a, int arr[], int x);
int binsearch2(int a, int arr[], int x);

#define MAX 20000

int main(void) {
  int test[MAX];
  int l, i, x = 100;
  clock_t elapsed_time, curr_time;
  for(i = 0; i < MAX; i++) {
    test[i] = i;
  }
  curr_time = clock();
  for(i = 0; i < 60000; i++) {
    l = binsearch1(x, test, MAX);
  }
  elapsed_time = clock() - curr_time;
  if(l < 0) {
    printf("Element %d not found.\n", x);
  }
  else {
    printf("Element %d found at %d position.\n", x, l);
  }
  printf("First binary search take %lu clocks (%.5f seconds).\n",(unsigned long)elapsed_time, (double)elapsed_time/CLOCKS_PER_SEC);

  curr_time = clock();

  for(i = 0; i < 60000; i++) {
    l = binsearch2(x,test,MAX);
  }
    elapsed_time = clock() - curr_time;

    if(l < 0){
      printf("Element %d not found.\n",x);
    } else {
      printf("Element %d found at %d position.\n",x,l);
    }
    printf("Second binary search take %lu clocks (%lu seconds) \n", (unsigned long)elapsed_time,
      elapsed_time/CLOCKS_PER_SEC);
}

int binsearch1(int a, int arr[], int x) {
  int start, end, m;
  start = 0;
  end = x-1;
  while(start <= end){
    m = (start+end)/2;
    if(a < arr[m]){
      end = m - 1;
    } else if (a > arr[m]) {
      start = m + 1;
    } else {
      return m;
    }
  }
  return -1;
}

int binsearch2(int a, int arr[], int x) {
  int start, end, m;
  start = 0;
  end = x-1;
  m = (start + end) / 2;
  while (start <= end && a != arr[m]) {
    if (a < arr[m]){
      end = m-1;
    } else {
      start = m + 1;
    }
    m = (start + end) / 2;
  }
  if(a == arr[m]){
    return m;
  } else {
    return -1;
  }
}
