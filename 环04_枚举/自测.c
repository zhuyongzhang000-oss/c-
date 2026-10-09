/*
 * ══════════════════════════════════════════════════════════════════
 *  环04 自测：猜输出 + 判断对错（运行 ring04_quiz 自动判分）
 * ══════════════════════════════════════════════════════════════════
 *  做法同前：一、把 OUT 会输出的内容写进 GUESS 的引号（空格要准，"" 算未做）；
 *            二、' ' 改成 'Y'（合法/对）或 'N'（不合法/错）。
 *  这个文件里故意有「看着像错」的写法，编译器可能出黄色警告，不影响运行。
 */
#include "detail.h"

int main(void)
{
    console_utf8();
    printf("环04 自测\n");

    d_section("一、猜输出");

    { int i = 1, s = 0;  for (; i <= 4;) { s += i; i += 2; }  OUT("%d %d", s, i); }
    GUESS(1, "");                                   /* → 细1 */

    { int x, y, n = 0;  for (x = 0, y = 0; y != 5 && x < 3; x++) n++;  OUT("%d", n); }
    GUESS(2, "");                                   /* [仿配-5-28] → 细1 */

    { int i = 2;  for (OUT("%d", i); i < 4; i++) OUT("%d", i); }
    GUESS(3, "");                                   /* [仿配-5-37] → 细1 */

    { int i, j, n = 0;  for (i = 1; i <= 3; i++) for (j = i; j <= 3; j++) n++;  OUT("%d", n); }
    GUESS(4, "");                                   /* → 细2 */

    { int i, j;  for (i = 1; i <= 2; i++) { for (j = 3; j >= 2; j--) OUT("%d", i * j); OUT(" "); } }
    GUESS(5, "");                                   /* [仿配-5-50] → 细2 */

    { int i, j, m = 1;  for (i = 1; i < 4; i++) for (j = 2; j > 0; j--) { if (i + j > 4) break; m *= i + j; }
      OUT("%d", m); }
    GUESS(6, "");                                   /* [仿配-5-51] → 细2 细9 */

    { int a = -1, b = 0;  while (a++) ++b;  OUT("%d,%d", a, b); }
    GUESS(7, "");                                   /* [仿配-5-12] → 细3 */

    { int a = -1, b = 0;  do { ++b; } while (a++);  OUT("%d,%d", a, b); }
    GUESS(8, "");                                   /* [仿配-5-18] → 细3 */

    { int sum = 0, x = 3;  do { sum += x; } while (!--x);  OUT("%d", sum); }
    GUESS(9, "");                                   /* [仿配-5-21] → 细3 */

    { int x = 0, y = 4;  do { while (--y) x++; } while (y--);  OUT("%d,%d", x, y); }
    GUESS(10, "");                                  /* [仿配-5-26] → 细3 */

    { int a = 10, b = 0, c = 0;  for (; a;) { b += a; a -= ++c; }  OUT("%d,%d,%d", a, b, c); }
    GUESS(11, "");                                  /* [仿配-5-49] → 细1 细3 */

    { int n = 2;
      switch (n) { case 1: OUT("a"); case 2: OUT("b"); case 3: OUT("c"); break; default: OUT("d"); } }
    GUESS(12, "");                                  /* → 细6 */

    { int s = 0, n;
      for (n = 0; n < 3; n++) switch (n) { default: s += 5; case 1: s += 1; break; case 2: s += 2; }
      OUT("%d", s); }
    GUESS(13, "");                                  /* [仿配-4-73] → 细6 */

    { int s = 0, n;
      for (n = 0; n < 3; n++) {
          switch (s) { case 0: case 1: s += 1; case 2: s += 2; break; case 3: s += 3; default: s += 4; }
          OUT("%d,", s);
      } }
    GUESS(14, "");                                  /* [仿配-4-65] → 细6 */

    { int x = 1, y = 1, a = 0, b = 0;
      switch (x) {
          case 1: switch (y) { case 0: a++; break; case 1: b++; break; }
          case 2: a++; b++; break;
          case 3: a++; b++;
      }
      OUT("%d %d", a, b); }
    GUESS(15, "");                                  /* [仿配-4-71] → 细8 */

    { char c = '3';
      switch (c - '0') { case 1: case 3: OUT("odd"); break; case 2: OUT("even"); break; default: OUT("?"); } }
    GUESS(16, "");                                  /* → 细5 细6 */

    { int y = 10;  for (; y > 0; y--) if (y % 4 == 0) OUT("%d", --y); }
    GUESS(17, "");                                  /* [仿配-5-46] → 细3 */

    { int i, data = 2;  for (i = 0; i < 5; i++) { if (i < data) continue; OUT("%d,", i); } }
    GUESS(18, "");                                  /* [仿配-5-59] → 细7 */

    { int i;  for (i = 1; i <= 4; i++) { if (i % 2) OUT("*"); else continue; OUT("#"); }  OUT("$"); }
    GUESS(19, "");                                  /* [仿配-5-61] → 细7 */

    { int x, y, n = 0;  for (x = 0; x <= 10; x++) for (y = 0; y <= 10; y++) if (x + y == 10 && x < y) n++;
      OUT("%d", n); }
    GUESS(20, "");                                  /* → ①② 枚举计数 */


    d_section("二、判断（Y 合法/对，N 不合法/错）");

    JUDGE(1,  ' ');   /* for (;;) 是合法的写法（无限循环，靠 break 出来）       [教材5.4] → 细1 */
    JUDGE(2,  ' ');   /* for (i = 0 i < 10 i++) 省略分号也能编译               [教材5.4] → 细1 */
    JUDGE(3,  ' ');   /* double x; switch (x) { … } 能通过编译                  [真选5·武科大2019] → 细5 */
    JUDGE(4,  ' ');   /* case 后面可以写变量，如 case c:                        [配-4-59] → 细5 */
    JUDGE(5,  ' ');   /* switch 语句里必须有 default                            [配-4-58] → 细6 */
    JUDGE(6,  ' ');   /* switch 语句里不一定要用 break                          [配-4-58] → 细6 */
    JUDGE(7,  ' ');   /* default 只能写在 switch 的最后                         [配-4-73] → 细6 */
    JUDGE(8,  ' ');   /* 同一个 switch 里两个 case 的值可以相同                  [教材4.7] → 细5 */
    JUDGE(9,  ' ');   /* switch (a + b); { case 3: w = 1; } 能通过编译           [真选5·武科大2019] → 细5 */
    JUDGE(10, ' ');   /* case 'A': 是合法的 case 写法                           [教材4.7] → 细5 */
    JUDGE(11, ' ');   /* case 1, 2: 可以让 1 和 2 走同一段代码                   [配-4-60] → 细5 */
    JUDGE(12, ' ');   /* 循环里的 switch 中写 break，只跳出 switch，不结束循环   [配-4-67] → 细7 */
    JUDGE(13, ' ');   /* continue 可以写在 switch 里，外面没有循环也行           [配-5-57] → 细7 */
    JUDGE(14, ' ');   /* while (ch = getchar() != 'N') 能把读到的字符存进 ch      [配-5-2] → 细4 */
    JUDGE(15, ' ');   /* while (scanf("%d", &x)) 遇到输入结束一定会退出          [A-2012-4] → 细4 */
    JUDGE(16, ' ');   /* 任何 while 循环改写成 do-while 后功能都完全一样          [配-5-27] → 细9 */
    JUDGE(17, ' ');   /* n = 10; while (n); { n--; } 是死循环                     [配-5-33] → 细10 */
    JUDGE(18, ' ');   /* for (k = 2; k == 0; ) … 循环体会执行一次                 [配-5-32] → 细10 */
    JUDGE(19, ' ');   /* 内层循环里的 break 会把外层循环也结束                    [配-5-51] → 细2 */
    JUDGE(20, ' ');   /* 1/2/5 凑 100 的组合数，两层循环也能求对                  [A-2016-5] → ② */
    JUDGE(21, ' ');   /* 计数器 count 应在最外层循环之前清零                      → ③ */
    JUDGE(22, ' ');   /* 百钱百鸡里直接用 z/3、不判 z%3==0，也能求对              [G4-1] → ④ */

    return d_summary("环04");
}
