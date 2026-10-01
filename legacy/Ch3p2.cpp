/* SUPERSEDED. Kept for reference only -- this file is not part of the
 * build and is known to be incorrect.
 *
 * 1. `int void escape(...)` -- two type specifiers on one declaration;
 *    does not compile.
 * 2. `s[j] = '\0'` is missing its terminating semicolon.
 * 3. The closing brace for the `for` loop is missing, so the next
 *    statement (`s[j] = '\0'`) and the function's own closing brace end
 *    up mismatched; as written the braces do not balance at all.
 * 4. There is no `main`, and only `escape` is attempted -- exercise 3-2
 *    also asks for the reverse transform, `unescape`.
 *
 * Replaced by chapter3/ex3_02.c, which adds unescape() and a main that
 * round-trips a line through both; pinned by the
 * test_escape_unescape() case in tests/unit_tests.c.
 */

# include <stdio.h>

int void escape(char s[], char t[]) {
  int i, j;
  for(i = j = 0; t[i] != '\0'; i++) {
    switch(t[i]){
      case '\n': {
        s[j++] = '\\';
        s[j++] = 'n';
        break;
      }
      case '\t': {
        s[j++] = '\\';
        s[j++] = 't';
        break;
      }
      default: {
        s[j++] = t[i];
        break;
      }
    }
  s[j] = '\0'
  }
}
