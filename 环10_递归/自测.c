/*
 * ══════════════════════════════════════════════════════════════════
 *  环10 自测：猜输出 + 判断对错（运行 ring10_quiz 自动判分）
 * ══════════════════════════════════════════════════════════════════
 *  做法同前：一、把 OUT 会输出的内容写进 GUESS 的引号（空格要准，"" 算未做）；
 *            二、' ' 改成 'Y'（合法/对）或 'N'（不合法/错）。
 *  先读下面的函数和宏，题目会用到。
 */
#include "detail.h"

int f1(int n) { if (n <= 1) return 1; return n * f1(n - 2); }
void pr(int n) { if (n > 0) { OUT("%d", n % 10); pr(n / 10); } }
void pr2(int n) { if (n > 0) { pr2(n / 10); OUT("%d", n % 10); } }
int fun(int n) { int c; if (n == 1) c = 10; else c = fun(n - 1) + 2; return c; }
int cnt;
int fibc(int n) { cnt++; if (n <= 2) return 1; return fibc(n - 1) + fibc(n - 2); }
int steps(int n) { if (n == 1) return 1; return 2 * steps(n - 1) + 1; }
int g(int n) { static int s = 0; s += n; if (n > 1) g(n - 1); return s; }
int p(int d) { if (d == 4) return 1; return (p(d + 1) + 1) * 2; }
double P(int n, double x)
{
    if (n == 0) return 1;
    if (n == 1) return x;
    return ((2 * n - 1) * x * P(n - 1, x) - (n - 1) * P(n - 2, x)) / n;
}
void rv(char s[], int i) { if (s[i] != '\0') { rv(s, i + 1); OUT("%c", s[i]); } }

#define SQ1(x) x * x
#define SQ2(x) ((x) * (x))
#define F(x) x * x + 1
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define N 3
#define M N + 1

int main(void)
{
    console_utf8();
    printf("环10 自测\n");

    d_section("一、猜输出");

    { OUT("%d %d", f1(7), f1(6)); }
    GUESS(1, "");                                   /* → 细9 */

    { pr(123); }
    GUESS(2, "");                                   /* → ③ */

    { pr2(123); }
    GUESS(3, "");                                   /* → ③④ */

    { OUT("%d", fun(4)); }
    GUESS(4, "");                                   /* [配-4-改1] → 细8 */

    { int v;  cnt = 0;  v = fibc(5);  OUT("%d %d", v, cnt); }
    GUESS(5, "");                                   /* fibc 一共被调用几次 → ⑦ */

    { OUT("%d", steps(4)); }
    GUESS(6, "");                                   /* Hanoi 4 个盘要几步 → ⑥ */

    { OUT("%d %d", SQ1(2 + 3), SQ2(2 + 3)); }
    GUESS(7, "");                                   /* → 细2 */

    { OUT("%d", F(1 + 1) * 2); }
    GUESS(8, "");                                   /* [仿真选34·北航2018] → 细2 */

    { int i = 2, j = 4, m;  m = MAX(i++, j);  OUT("%d %d", m, i); }
    GUESS(9, "");                                   /* → 细4 */

    { OUT("%d", M * 2); }
    GUESS(10, "");                                  /* → 细1 细2 */

    { int a = g(3), b = g(2);  OUT("%d %d", a, b); }
    GUESS(11, "");                                  /* 递归 + static → ② 环09 细5 */

    { OUT("%d", p(1)); }
    GUESS(12, "");                                  /* [仿教-5-12] → ⑤ */

    { OUT("%.3f", P(2, 0.5)); }
    GUESS(13, "");                                  /* [教-7-13] → ⑦ */

    { char s[] = "abc";  rv(s, 0); }
    GUESS(14, "");                                  /* → ③ */


    d_section("二、判断（Y 合法/对，N 不合法/错）");

    JUDGE(1,  ' ');   /* 递归函数必须有不再调用自己就能返回的情况（基例）        [教材7.6] → ① */
    JUDGE(2,  ' ');   /* 递归的每一层共用同一份局部变量                          [教材7.6] → ② */
    JUDGE(3,  ' ');   /* #define 命令行的末尾必须加分号                           [真选39·中财2018] → 细1 */
    JUDGE(4,  ' ');   /* #define N 5 会为 N 分配一块内存                          [教材] → 细1 */
    JUDGE(5,  ' ');   /* 带参数的宏在展开时会先把实参的值算出来                  [真选34·北航2018] → 细3 */
    JUDGE(6,  ' ');   /* #include <stdio.h> 和 #include "stdio.h" 都能用          [教材] → 细5 */
    JUDGE(7,  ' ');   /* 预处理命令是在程序运行的过程中处理的                    [真选39·中财2018] → 细7 */
    JUDGE(8,  ' ');   /* 以 # 开头的语句行都是预处理命令行                       [真选39·中财2018] → 细7 */
    JUDGE(9,  ' ');   /* #define N 5 之后，可以写 N = 6; 修改它                    [教材] → 细1 */
    JUDGE(10, ' ');   /* #define SQ (x) x*x（SQ 后面有空格）定义的是带参数的宏     [教材] → 细2 */
    JUDGE(11, ' ');   /* 同一个问题，递归写法一定比循环写法快                    [教材7.6] → ⑤ */
    JUDGE(12, ' ');   /* 递归函数里写 if (n = 1) 能正确判断 n 是不是 1           [配-4-改1] → 细8 */
    JUDGE(13, ' ');   /* #define N 5 之后，printf("N") 输出的是 5                  [教材] → 细1 */
    JUDGE(14, ' ');   /* 每次递归调用，问题规模都要更接近基例                    [教材7.6] → ① */
    JUDGE(15, ' ');   /* C 语言的函数可以直接调用它自己                          [教材7.6] → ① */

    return d_summary("环10");
}
