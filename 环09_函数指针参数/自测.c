/*
 * ══════════════════════════════════════════════════════════════════
 *  环09 自测：猜输出 + 判断对错（运行 ring09_quiz 自动判分）
 * ══════════════════════════════════════════════════════════════════
 *  做法同前：一、把 OUT 会输出的内容写进 GUESS 的引号（空格要准，"" 算未做）；
 *            二、' ' 改成 'Y'（合法/对）或 'N'（不合法/错）。
 *  先读下面这些函数（题目会调用它们），再往下做。
 */
#include "detail.h"

int bump(int x) { x += 2; return x; }
void swap_bad(int a, int b) { int t = a; a = b; b = t; }
void swap_ok(int *a, int *b) { int t = *a; *a = *b; *b = t; }
int c1(void) { static int n = 10; n += 2; return n; }
void ff2(void)
{
    int c = 5;
    static int a = 2, b = 3;
    if (b == 3) { a += c; b++; }
    else { a += c; b--; }
    OUT("%d,%d;", a, b);
}
int g2 = 5;
int h(void) { return g2 * 2; }
int f_int(void) { return 7.9; }
double f_dbl(void) { return 7 / 2; }
void mm(int a[], int n, int *mx, int *mn)
{
    int i;
    *mx = *mn = a[0];
    for (i = 1; i < n; i++) { if (a[i] > *mx) *mx = a[i]; if (a[i] < *mn) *mn = a[i]; }
}
void add_ok(int *n) { (*n)++; }
void add_bad(int *n) { *n++; }
void dbl(int b[], int n) { int i; for (i = 0; i < n; i++) b[i] *= 2; }
void f45(int *p) { p = p + 3; OUT("%d,", *p); }
void f46(int *q) { int i = 0; for (; i < 3; i++) (*q)++; }
int sq(int x) { return x * x; }

int main(void)
{
    console_utf8();
    printf("环09 自测\n");

    d_section("一、猜输出");

    { int a = 3, b;  bump(a);  b = bump(a);  OUT("%d %d", a, b); }
    GUESS(1, "");                                   /* → ③ */

    { int a = 4, b = 7;  swap_bad(a, b);  OUT("%d%d", a, b);  swap_ok(&a, &b);  OUT(" %d%d", a, b); }
    GUESS(2, "");                                   /* [A-2017-1] → ⑤ */

    { int x1 = c1(), x2 = c1(), x3 = c1();  OUT("%d %d %d", x1, x2, x3); }
    GUESS(3, "");                                   /* → 细5 */

    { ff2();  ff2(); }
    GUESS(4, "");                                   /* [仿真选23·华南理工2018] → 细5 */

    { int g2 = 1;  OUT("%d %d", g2, h()); }
    GUESS(5, "");                                   /* → 细4 */

    { OUT("%d %.1f", f_int(), f_dbl()); }
    GUESS(6, "");                                   /* → ② */

    { int a[3] = {1, 5, 9}, *q = a, v;  v = *q++;  OUT("%d ", v);  v = (*q)++;  OUT("%d %d", v, a[1]); }
    GUESS(7, "");                                   /* → 细10 */

    { int x = 5, *p = &x;  ++*p;  OUT("%d %d", x, *p + 1); }
    GUESS(8, "");                                   /* → 细9 */

    { int a[4] = {3, -2, 8, 0}, mx, mn;  mm(a, 4, &mx, &mn);  OUT("%d %d", mx, mn); }
    GUESS(9, "");                                   /* [A-2013-3] → ⑥ */

    { int n = 3, m = 3;  add_ok(&n);  add_ok(&n);  add_bad(&m);  OUT("%d %d", n, m); }
    GUESS(10, "");                                  /* → ⑦ 细10 */

    { int a[3] = {1, 2, 3};  dbl(a, 2);  OUT("%d %d %d", a[0], a[1], a[2]); }
    GUESS(11, "");                                  /* [仿配-6-38] → ⑦ */

    { int a[5] = {1, 2, 3, 4, 5}, *r = a;  f45(r);  OUT("%d", *r); }
    GUESS(12, "");                                  /* [配-6-45] → ③ */

    { int a[5] = {1, 2, 3, 4, 5};  f46(a);  OUT("%d %d", a[0], a[1]); }
    GUESS(13, "");                                  /* [仿配-6-46] → 细9 */

    { OUT("%d", sq(sq(2))); }
    GUESS(14, "");                                  /* → 细1 嵌套调用 */


    d_section("二、判断（Y 合法/对，N 不合法/错）");

    JUDGE(1,  ' ');   /* C 语言的函数可以嵌套定义（函数里再定义函数）            [配-2-9] → 细1 */
    JUDGE(2,  ' ');   /* C 语言的函数可以嵌套调用，如 fun(fun(x))                 [配-2-7] → 细1 */
    JUDGE(3,  ' ');   /* 按教材，函数省略返回类型时默认是 int                     [真选18·华南理工2018] → 细1 */
    JUDGE(4,  ' ');   /* 形参的缺省存储类别是 auto                                [真选46·川大2017] → 细6 */
    JUDGE(5,  ' ');   /* 实参和形参之间的数据传递是单向的值传递                  [教材7.4] → 细3 */
    JUDGE(6,  ' ');   /* 在函数的复合语句里定义的变量，在整个函数里都有效        [真选22·华南理工2018] → 细4 */
    JUDGE(7,  ' ');   /* 不同的函数里可以使用同名的变量                          [真选22·华南理工2018] → 细4 */
    JUDGE(8,  ' ');   /* static 局部变量每次调用函数都会重新初始化               [真选23·华南理工2018] → 细5 */
    JUDGE(9,  ' ');   /* 一个函数里的 static 局部变量，可以在别的函数里直接使用  [教材7.9] → 细5 */
    JUDGE(10, ' ');   /* 没有初始化的全局变量，值是 0                            [教材7.9] → 细5 */
    JUDGE(11, ' ');   /* 可以对 register 变量取地址                              [教材7.9] → 细6 */
    JUDGE(12, ' ');   /* f 是 void 函数时，t = f(); 能通过编译                    [真选11·武科大2019] → 细2 */
    JUDGE(13, ' ');   /* int func(int *p); int x; 调用 func(x); 是正确的           [真选13·武科大2019] → 细8 */
    JUDGE(14, ' ');   /* int *p, *s, c; 写 s = &p; 能通过编译                      [真选25·华南理工2018] → 细9 */
    JUDGE(15, ' ');   /* int *p, n; p = &n; scanf("%d", p); 能正确给 n 读入数据    [真选20·华南理工2018] → 细9 */
    JUDGE(16, ' ');   /* 函数里写 *n++; 能让 n 指向的变量加 1                      [A-2018-5] → 细10 */
    JUDGE(17, ' ');   /* 函数里修改数组形参的元素，会改变主函数里的实参数组      [配-6-38] → ⑦ */
    JUDGE(18, ' ');   /* printf("%d %d", f(), f()); 里两次调用一定从左到右执行    [教材7.4] → 细7 */
    JUDGE(19, ' ');   /* 一条 return 语句只能带回一个值                           [教材7.3] → ⑥ */
    JUDGE(20, ' ');   /* 函数定义里的形参可以写成常量，如 int f(5)               [教材7.4] → 细3 */

    return d_summary("环09");
}
