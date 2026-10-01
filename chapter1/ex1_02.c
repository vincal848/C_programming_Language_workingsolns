/* K&R exercise 1-2: find out what happens when printf's argument string
 * contains \c, where c is a character not in the language's list of
 * defined escape sequences.
 *
 * Approach: just do it and look at the output. The language does not
 * define a meaning for \c, so what you see is whatever this particular
 * compiler/library does with an escape it doesn't recognize -- gcc and
 * clang both warn and then drop the backslash, keeping the letter, but
 * that is not a portability guarantee. tests/ex1_02.out records what
 * was actually observed when this was compiled; it pins the local
 * toolchain's behavior, not the language.
 */
#include <stdio.h>

int main(void)
{
    printf("Testing an escape sequence the language does not define: \c\n");
    return 0;
}
