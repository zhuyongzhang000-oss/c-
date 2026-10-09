/*
 * ══════════════════════════════════════════════════════════════════
 *  环08 自测：猜输出 + 判断对错（运行 ring08_quiz 自动判分）
 * ══════════════════════════════════════════════════════════════════
 *  做法同前：一、把 OUT 会输出的内容写进 GUESS 的引号（空格要准，"" 算未做）；
 *            二、' ' 改成 'Y'（合法/对）或 'N'（不合法/错）。
 */
#include "detail.h"
#include <ctype.h>

int main(void)
{
    int i, v;
    console_utf8();
    printf("环08 自测\n");

    d_section("一、猜输出");

    { char s[] = "abc";  OUT("%d %d", (int)sizeof(s), (int)strlen(s)); }
    GUESS(1, "");                                   /* → 细1 */

    { char s[10] = "hi";  OUT("%d %d", (int)sizeof(s), (int)strlen(s)); }
    GUESS(2, "");                                   /* → 细1 */

    { char s[] = {'a', 'b', '\0', 'c'};  OUT("%d %d", (int)sizeof(s), (int)strlen(s)); }
    GUESS(3, "");                                   /* → 细1 */

    { OUT("%d %d", (int)strlen("a\tb\\c"), (int)strlen("ab\0cd")); }
    GUESS(4, "");                                   /* → 细7 */

    { char s[] = "hello";  OUT("%s|%c", s + 3, s[1]); }
    GUESS(5, "");                                   /* → 细4 */

    { char s[] = "0305";  v = 0;  for (i = 0; s[i] != '\0'; i++) v = v * 10 + (s[i] - '0');  OUT("%d", v + 1); }
    GUESS(6, "");                                   /* [A-2021-1] → ④ */

    { char s[] = "12";  v = 0;  for (i = 0; s[i] != '\0'; i++) v = v * 10 + s[i];  OUT("%d", v); }
    GUESS(7, "");                                   /* 忘了减 '0' → ④ */

    { char a[10] = "ab";  strcat(a, "cd");  OUT("%s %d", a, (int)strlen(a)); }
    GUESS(8, "");                                   /* → 细5 */

    { char a[10] = "hello";  strcpy(a, "hi");  OUT("%s %c", a, a[3]); }
    GUESS(9, "");                                   /* strcpy 只改前面几格 → 细5 */

    { OUT("%d %d %d", strcmp("abc", "abd") < 0, strcmp("b", "abc") > 0, strcmp("x", "x")); }
    GUESS(10, "");                                  /* → 细5 */

    { char a[] = "And", b[] = "Aid";  i = 0;  while (a[i] == b[i] && a[i] != '\0') i++;  OUT("%d", a[i] - b[i]); }
    GUESS(11, "");                                  /* [教-6-14] → ⑥ */

    { const char *w[2] = {"abcba", "abca"};  int r, len, ok;
      for (r = 0; r < 2; r++) { len = (int)strlen(w[r]); ok = 1;
          for (i = 0; i < len / 2; i++) if (w[r][i] != w[r][len - 1 - i]) ok = 0;
          OUT("%d", ok); } }
    GUESS(12, "");                                  /* [A-2012-5] → ③ */

    { char s[] = "a  bc d ";  int in = 0, n = 0;
      for (i = 0; s[i] != '\0'; i++) { if (s[i] == ' ') in = 0; else if (!in) { in = 1; n++; } }
      OUT("%d", n); }
    GUESS(13, "");                                  /* → ⑧ */

    { char s[] = "a1 B2!";  int L = 0, d = 0;
      for (i = 0; s[i]; i++) { if (isalpha((unsigned char)s[i])) L++; else if (isdigit((unsigned char)s[i])) d++; }
      OUT("%d %d", L, d); }
    GUESS(14, "");                                  /* → ⑦ */

    { char s[10] = {'6', '1', '5', '3', 'a', '2'};  v = 0;  i = 0;
      while (s[i] <= '9' && s[i] >= '0') { v = 10 * v + s[i] - '0'; i++; }
      OUT("%d", v); }
    GUESS(15, "");                                  /* [仿配-6-57] → ④ */

    { char s1[] = "Hi", s2[] = "Hi";  OUT("%s", s1 == s2 ? "E" : "U"); }
    GUESS(16, "");                                  /* [真选35·北航2018] → 细6 */

    { char s[] = "abc";  for (i = (int)strlen(s) - 1; i >= 0; i--) OUT("%c", s[i]); }
    GUESS(17, "");                                  /* [A-2015-1] → ② */

    { char s[] = "aBc1";  for (i = 0; s[i]; i++) s[i] = (char)toupper((unsigned char)s[i]);  OUT("%s", s); }
    GUESS(18, "");                                  /* → 细8 */


    d_section("二、判断（Y 合法/对，N 不合法/错）");

    JUDGE(1,  ' ');   /* char s[10]; s = "abc"; 能通过编译                       [真选38·中财2018] → 细3 */
    JUDGE(2,  ' ');   /* char *p; p = "abc"; 能通过编译                          [配-6-100] → 细3 */
    JUDGE(3,  ' ');   /* char s[3] = "abc"; 之后 s 是一个以 '\0' 结尾的字符串    [配-6-100] → 细2 */
    JUDGE(4,  ' ');   /* char s[3] = "abcd"; 能通过编译                          [教材6.3] → 细2 */
    JUDGE(5,  ' ');   /* char s[2] = {"A", "B"}; 能通过编译                      [配-6-6] → 细2 */
    JUDGE(6,  ' ');   /* char s[] = "\0"; 能通过编译                             [配-6-97] → 细2 */
    JUDGE(7,  ' ');   /* 字符数组只能用来存放字符串                              [配-6-94] → 细1 */
    JUDGE(8,  ' ');   /* 可以用 == 判断两个字符数组里的字符串是否相同            [真选35·北航2018] → 细6 */
    JUDGE(9,  ' ');   /* a 比 b 大时，strcmp(a, b) 的值一定是 1                   [教材6.3] → 细5 */
    JUDGE(10, ' ');   /* scanf("%s", s); 能读入带空格的一整行                    [配-3-22] → 细4 */
    JUDGE(11, ' ');   /* gets(s); 能读入带空格的一整行                           [教材6.3] → 细4 */
    JUDGE(12, ' ');   /* puts(s); 输出字符串后会自动换行                         [教材6.3] → 细4 */
    JUDGE(13, ' ');   /* strlen 求出的长度包括最后的 '\0'                        [教材6.3] → 细1 */
    JUDGE(14, ' ');   /* strcat(a, b) 时 a 的空间要能放下连接后的字符串和 '\0'   [教材6.3] → 细5 */
    JUDGE(15, ' ');   /* strcpy(a, b) 会把 b 末尾的 '\0' 一起复制过去            [教材6.3] → 细5 */
    JUDGE(16, ' ');   /* char s[3][10]; 可以写 s[0] = s[1]; 把第 1 行复制给第 0 行  [教材6.3] → 细9 */
    JUDGE(17, ' ');   /* 字符串 "a" 和字符 'a' 占用的内存一样多                  [配-3-34] → 细1 */
    JUDGE(18, ' ');   /* strlwr、strupr 是 C 标准库函数                          [教材6.3] → 细5 */
    JUDGE(19, ' ');   /* 手工复制字符串后要在末尾补 '\0'                         [A-2024-3] → ⑤ */
    JUDGE(20, ' ');   /* sizeof(字符数组) 和数组里实际存的字符串长短无关         [教材6.3] → 细1 */

    return d_summary("环08");
}
