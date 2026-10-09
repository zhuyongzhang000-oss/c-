/*
 * 环12 测试：一次测完 5 题。你不用改这个文件。
 * 运行 ring12_test，把最后一行复制给 Claude（有错的题，再贴上那道题的函数）。
 */
#include <stdlib.h>
#define CAPTURE_IMPL
#include "check.h"
#include "stu.h"

void course_avg(struct Student s[], int n, double avg[3]);
int best_student(struct Student s[], int n);
int day_of_year2(struct Date d);
void print(struct Student s[], int n);
void fun(STREC a[], int n);
struct Node *del(struct Node *head, int num);

static struct Node *build(const int v[], int n)
{
    struct Node *head = NULL, *tail = NULL, *q;
    int i;
    for (i = 0; i < n; i++) {
        q = (struct Node *)malloc(sizeof *q);
        q->num = v[i];
        q->next = NULL;
        if (head == NULL) head = q; else tail->next = q;
        tail = q;
    }
    return head;
}

static void list_str(struct Node *p, char *out, size_t size)
{
    char num[16];
    out[0] = '\0';
    for (; p != NULL; p = p->next) {
        snprintf(num, sizeof num, "%s%d", out[0] ? " " : "", p->num);
        strncat(out, num, size - strlen(out) - 1);
    }
}

static void del_case(const char *label, const int v[], int n, int key, const char *expected)
{
    char got[100];
    struct Node *head = build(v, n);
    head = del(head, key);
    list_str(head, got, sizeof got);
    q_case_s(label, got, expected);
}

int main(void)
{
    char got[200];
    struct Student s[4] = {
        {101, "Li", {80, 90, 70}}, {102, "Wang", {95, 85, 90}},
        {103, "Zhao", {60, 70, 80}}, {104, "Qian", {95, 90, 85}}};
    console_utf8();
    printf("环12 结构体 测试\n\n");

    q_begin("题1");
    {
        double avg[3] = {-12345, -12345, -12345};
        course_avg(s, 4, avg);
        q_case_d("第1门平均", avg[0], 82.5, 1e-9);
        q_case_d("第2门平均", avg[1], 83.75, 1e-9);
        q_case_d("第3门平均", avg[2], 81.25, 1e-9);
        q_case_i("平均分最高者下标（并列取前面）", best_student(s, 4), 1);
        q_case_i("只有前一个人", best_student(s, 1), 0);
    }
    q_end();

    q_begin("题2");
    {
        struct Date d1 = {2024, 3, 1}, d2 = {2023, 3, 1}, d3 = {2000, 12, 31}, d4 = {1900, 3, 1}, d5 = {2024, 1, 1};
        q_case_i("2024-3-1", day_of_year2(d1), 61);
        q_case_i("2023-3-1", day_of_year2(d2), 60);
        q_case_i("2000-12-31", day_of_year2(d3), 366);
        q_case_i("1900-3-1", day_of_year2(d4), 60);
        q_case_i("2024-1-1", day_of_year2(d5), 1);
    }
    q_end();

    q_begin("题3");
    {
        struct Student t[2] = {{101, "Li", {88, 92.5, 79}}, {7, "Wu", {60, 0, 100}}};
        cap_reset(); print(t, 2);
        q_case_text("两个学生", cap_buf, "101 Li 88.0 92.5 79.0\n7 Wu 60.0 0.0 100.0\n");
    }
    q_end();

    q_begin("题4");
    {
        STREC a[6] = {{"GA005", 85}, {"GA003", 76}, {"GA002", 69}, {"GA004", 85}, {"GA001", 91}, {"GA007", 72}};
        int i, ok = 1, ok85 = 1;
        char pairs[200] = "", want[] = "GA001:91 GA003:76 GA007:72 GA002:69";
        fun(a, 6);
        if (a[0].s == 85 && a[1].s == 76 && a[4].s == 91) q_case_i("6 条记录", NOT_DONE, 0);   /* 一点没动 */
        else {
            for (i = 0; i + 1 < 6; i++) if (a[i].s < a[i + 1].s) ok = 0;
            q_case_i("分数从高到低", ok, 1);
            /* 学号和分数要配套：检查 91、76、69、72 这四条（85 有两条，顺序不定，单独查） */
            for (i = 0; i < 6; i++) {
                if (a[i].s == 85) {
                    if (strcmp(a[i].num, "GA005") != 0 && strcmp(a[i].num, "GA004") != 0) ok85 = 0;
                    continue;
                }
                {
                    char one[20];
                    snprintf(one, sizeof one, "%s%s:%d", pairs[0] ? " " : "", a[i].num, a[i].s);
                    strncat(pairs, one, sizeof pairs - strlen(pairs) - 1);
                }
            }
            q_case_i("85 分那两条学号没错", ok85, 1);
            q_case_s("学号和分数配套（整条交换）", pairs, want);
        }
    }
    q_end();

    q_begin("题5");
    {
        int v[4] = {10, 20, 30, 40}, one[1] = {5};
        struct Node *probe = build(v, 4), *r = del(probe, 20);
        if (r == (struct Node *)-1) q_case_i("删中间", NOT_DONE, 0);
        else {
            list_str(r, got, sizeof got);  q_case_s("删中间 20", got, "10 30 40");
            del_case("删第一个", v, 4, 10, "20 30 40");
            del_case("删最后一个", v, 4, 40, "10 20 30");
            del_case("没找到", v, 4, 99, "10 20 30 40");
            del_case("只有一个结点", one, 1, 5, "");
        }
    }
    q_end();

    return summary("环12");
}
