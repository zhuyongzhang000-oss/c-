/*
 * ══════════════════════════════════════════════════════════════════
 *  环12 自测：猜输出 + 判断对错（运行 ring12_quiz 自动判分）
 * ══════════════════════════════════════════════════════════════════
 *  做法同前：一、把 OUT 会输出的内容写进 GUESS 的引号（空格要准，"" 算未做）；
 *            二、' ' 改成 'Y'（合法/对）或 'N'（不合法/错）。
 *  先读下面的类型和函数。
 */
#include "detail.h"

struct P { int x; int y; };
struct Stu { int num; char name[20]; double score; };
struct Node { int data; struct Node *next; };
struct D { int y, m, d; };
struct E { char n[10]; struct D birth; };

void inc(struct P q) { q.x++; }
void incp(struct P *q) { q->x++; }

int main(void)
{
    console_utf8();
    printf("环12 自测\n");

    d_section("一、猜输出");

    { struct P a = {1, 2}, b;  b = a;  b.x = 5;  OUT("%d %d", a.x, b.x); }
    GUESS(1, "");                                   /* → 细4 */

    { struct Stu s[3] = {{1, "Al", 60}, {2, "Bo", 90}, {3, "Cy", 75}}, *p = s;  p++;
      OUT("%s %.0f", p->name, (p + 1)->score); }
    GUESS(2, "");                                   /* → 细7 */

    { struct Stu s[3] = {{1, "Al", 60}, {2, "Bo", 90}, {3, "Cy", 75}}, *p = &s[2];
      OUT("%d %d", (*p).num, (int)(p - s)); }
    GUESS(3, "");                                   /* → 细3 细7 */

    { struct person { char title[20]; int code; } book[3] = {{"Physics", 17}, {"Math", 18}};
      OUT("%c %d", book[1].title[2], book[2].code); }
    GUESS(4, "");                                   /* [仿真选15·武科大2019] → 细5 */

    { enum { A, B = 3, C, D2 = 10, E2 } ;  OUT("%d %d %d", A, C, E2); }
    GUESS(5, "");                                   /* → 细9 */

    { typedef struct { int a, b; } T;  T t = {3, 4};  OUT("%d", t.a * t.b); }
    GUESS(6, "");                                   /* → 细10 */

    { struct P a = {1, 2};  inc(a);  incp(&a);  incp(&a);  OUT("%d", a.x); }
    GUESS(7, "");                                   /* → ⑥ */

    { struct Node c = {3, NULL}, b = {2, &c}, a = {1, &b}, *p;  int s = 0;
      for (p = &a; p != NULL; p = p->next) s += p->data;
      OUT("%d %d", s, a.next->next->data); }
    GUESS(8, "");                                   /* → ⑦ */

    { struct Node c = {3, NULL}, b = {2, &c}, a = {1, &b}, *head = &a;
      head = head->next;  OUT("%d", head->data); }
    GUESS(9, "");                                   /* 删除头结点 → ⑧ */

    { struct Stu s[2] = {{1, "A", 50}, {2, "B", 90}};  double t;
      if (s[0].score < s[1].score) { t = s[0].score; s[0].score = s[1].score; s[1].score = t; }
      OUT("%d %.0f", s[0].num, s[0].score); }
    GUESS(10, "");                                  /* 只换了成绩 → ④ */

    { struct E e = {"Li", {2000, 5, 1}};  OUT("%d/%d", e.birth.m, e.birth.d); }
    GUESS(11, "");                                  /* [仿真选14·武科大2019] → 细3 */


    d_section("二、判断（Y 合法/对，N 不合法/错）");

    JUDGE(1,  ' ');   /* 结构体类型声明的 } 后面可以不写分号                      [川师卷2018-19 一-9] → 细1 */
    JUDGE(2,  ' ');   /* 声明一个结构体类型时，系统就为它分配了内存               [教材9.1] → ① */
    JUDGE(3,  ' ');   /* 两个同类型的结构体变量可以整体赋值 a = b;                [教材9.1] → 细4 */
    JUDGE(4,  ' ');   /* 可以用 a == b 比较两个结构体变量是否相等                 [教材9.1] → 细4 */
    JUDGE(5,  ' ');   /* scanf("%d", &s); 可以把一个结构体变量整体读进来          [教材9.1] → ② */
    JUDGE(6,  ' ');   /* struct worker work, *p = &work; 写 work->no 是正确的     [真选42·中财2018] → 细3 */
    JUDGE(7,  ' ');   /* (*p).no 和 p->no 是等价的                                [真选42·中财2018] → 细3 */
    JUDGE(8,  ' ');   /* *p.no 和 p->no 是等价的                                  [教材9.3] → 细3 */
    JUDGE(9,  ' ');   /* name 是结构体里的字符数组成员，s.name = "Li"; 是正确的   [教材9.1] → 细4 */
    JUDGE(10, ' ');   /* 结构体的成员可以是另一个结构体类型                       [真选14·武科大2019] → 细3 */
    JUDGE(11, ' ');   /* 共用体的各个成员可以同时保存各自的值                     [教材9.5] → 细8 */
    JUDGE(12, ' ');   /* 共用体变量的大小至少等于它最大的那个成员                 [教材9.5] → 细8 */
    JUDGE(13, ' ');   /* enum { RED, GREEN = 5, BLUE }; 中 BLUE 的值是 2           [教材9.6] → 细9 */
    JUDGE(14, ' ');   /* typedef 创造了一种新的数据类型                            [教材9.7] → 细10 */
    JUDGE(15, ' ');   /* 链表最后一个结点的 next 应该是 NULL                       [川师卷2022-23 一-8] → ⑦ */
    JUDGE(16, ' ');   /* 释放链表时写 free(p); p = p->next; 顺序是对的             [教材9.4] → ⑦ */
    JUDGE(17, ' ');   /* 指针 p 指向结构体数组的某个元素，p++ 指向下一条记录       [教材9.3] → 细7 */
    JUDGE(18, ' ');   /* sizeof(结构体) 一定等于各成员大小之和                     [教材9.1] → 细6 */

    return d_summary("环12");
}
