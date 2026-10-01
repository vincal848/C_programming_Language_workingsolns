/* Pulls the exercise functions straight into this translation unit
 * (each exercise file guards its own main() with #ifndef UNIT_TEST so
 * that including it here doesn't give us two mains) and exercises
 * them with assert(). Run via `make test`.
 */
#define UNIT_TEST
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../chapter2/ex2_03.c"
#include "../chapter2/ex2_04.c"
#include "../chapter2/ex2_10.c"
#include "../chapter3/ex3_01.c"
#include "../chapter3/ex3_02.c"
#include "../chapter3/ex3_03.c"
#include "../chapter5/ex5_01.c"

static void test_htoi(void)
{
    assert(htoi("0") == 0);
    assert(htoi("1010") == 0x1010);
    assert(htoi("0x1F") == 0x1F);
    assert(htoi("0X1f") == 0x1f);
    assert(htoi("ff") == 0xff);
    assert(htoi("abc") == 0xabc);
}

static void test_squeeze(void)
{
    char s1[40];

    strcpy(s1, "hello world");
    squeeze(s1, "lo");
    assert(strcmp(s1, "he wrd") == 0);

    strcpy(s1, "mississippi");
    squeeze(s1, "si");
    assert(strcmp(s1, "mpp") == 0);

    strcpy(s1, "abc");
    squeeze(s1, "");
    assert(strcmp(s1, "abc") == 0);
}

static void test_lower(void)
{
    assert(lower('A') == 'a');
    assert(lower('Z') == 'z');
    assert(lower('a') == 'a');
    assert(lower('5') == '5');
    assert(lower(' ') == ' ');
}

static void test_binsearch(void)
{
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));

    assert(binsearch1(7, arr, n) == 3);
    assert(binsearch1(1, arr, n) == 0);
    assert(binsearch1(11, arr, n) == 5);
    assert(binsearch1(2, arr, n) == -1);

    assert(binsearch2(7, arr, n) == 3);
    assert(binsearch2(1, arr, n) == 0);
    assert(binsearch2(11, arr, n) == 5);
    assert(binsearch2(2, arr, n) == -1);
}

static void test_escape_unescape(void)
{
    char s[100], t[100];

    escape(s, "a\tb\nc");
    assert(strcmp(s, "a\\tb\\nc") == 0);

    unescape(t, s);
    assert(strcmp(t, "a\tb\nc") == 0);
}

static void test_expand(void)
{
    char s2[200];

    expand("a-z", s2);
    assert(strcmp(s2, "abcdefghijklmnopqrstuvwxyz") == 0);

    expand("0-9", s2);
    assert(strcmp(s2, "0123456789") == 0);

    expand("a-cx-z", s2);
    assert(strcmp(s2, "abcxyz") == 0);

    expand("az-", s2);
    assert(strcmp(s2, "az-") == 0);
}

static void test_getint(void)
{
    int n;

    /* push "123 " in reverse so getch() reads it back in order */
    ungetch(' ');
    ungetch('3');
    ungetch('2');
    ungetch('1');
    assert(getint(&n) == ' ');
    assert(n == 123);

    ungetch(' ');
    ungetch('5');
    ungetch('-');
    assert(getint(&n) == ' ');
    assert(n == -5);
}

int main(void)
{
    test_htoi();
    test_squeeze();
    test_lower();
    test_binsearch();
    test_escape_unescape();
    test_expand();
    test_getint();

    printf("all unit tests passed\n");
    return 0;
}
