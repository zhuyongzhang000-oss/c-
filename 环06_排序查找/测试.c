/*
 * 环06 测试：一次测完 5 题。你不用改这个文件。
 * 运行 ring06_test，把最后一行复制给 Claude（有错的题，再贴上那道题的函数）。
 */
#define CAPTURE_IMPL
#include "check.h"

void sort_asc(int a[], int n);
int search(int a[], int n, int x);
int insert_sorted(int a[], int n, int x);
void odd_even(int a[], int n);
void merge_sorted(int a[], int na, int b[], int nb, int c[]);

/* 把数组拼成 "1 2 3" 方便比较 */
static void join(int a[], int n, char *out, size_t size)
{
    char num[16];
    int i;
    out[0] = '\0';
    for (i = 0; i < n; i++) {
        snprintf(num, sizeof num, "%s%d", i ? " " : "", a[i]);
        strncat(out, num, size - strlen(out) - 1);
    }
}

#define LEN(x) ((int)(sizeof(x) / sizeof((x)[0])))
#define NOT_TOUCHED 77777

static void sort_case(const char *label, int a[], int n, const char *expected)
{
    char got[200];
    sort_asc(a, n);
    join(a, n, got, sizeof got);
    q_case_s(label, got, expected);
}

int main(void)
{
    char got[300];
    console_utf8();
    printf("环06 排序·查找·插入·合并 测试\n\n");

    q_begin("题1");
    {
        int a[] = {5, 1, 4, 2, 3}, b[] = {3, 3, 1, 2, 1}, c[] = {7}, d[] = {-2, 10, 0, -5, 3, 3};
        int e[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        int same[] = {4, 1, 3};
        sort_asc(same, 3);
        if (same[0] == 4 && same[1] == 1 && same[2] == 3) q_case_i("没改动", NOT_DONE, 0);
        else {
            sort_case("5 1 4 2 3", a, LEN(a), "1 2 3 4 5");
            sort_case("有重复", b, LEN(b), "1 1 2 3 3");
            sort_case("一个数", c, LEN(c), "7");
            sort_case("有负数", d, LEN(d), "-5 -2 0 3 3 10");
            sort_case("倒序10个", e, LEN(e), "0 1 2 3 4 5 6 7 8 9");
        }
    }
    q_end();

    q_begin("题2");
    {
        int a[] = {1, 3, 5, 7, 9, 11, 13}, one[] = {4}, b[] = {2, 4};
        q_case_i("找 7", search(a, 7, 7), 3);
        q_case_i("找 1（第一个）", search(a, 7, 1), 0);
        q_case_i("找 13（最后一个）", search(a, 7, 13), 6);
        q_case_i("找 4（不在）", search(a, 7, 4), -1);
        q_case_i("找 20（比都大）", search(a, 7, 20), -1);
        q_case_i("找 0（比都小）", search(a, 7, 0), -1);
        q_case_i("一个数找 4", search(one, 1, 4), 0);
        q_case_i("两个数找 4", search(b, 2, 4), 1);
    }
    q_end();

    q_begin("题3");
    {
        int a[10] = {1, 3, 5, 7, 9}, b[10] = {1, 3, 5}, c[10] = {1, 3, 5}, d[10] = {0}, e[10] = {2, 4, 6};
        int n;
        n = insert_sorted(a, 5, 4);
        if (n == NOT_DONE) q_case_i("插 4", NOT_DONE, 0);
        else {
            join(a, n, got, sizeof got);  q_case_s("{1,3,5,7,9} 插 4", got, "1 3 4 5 7 9");
            n = insert_sorted(b, 3, 0);  join(b, n, got, sizeof got);  q_case_s("插在最前", got, "0 1 3 5");
            n = insert_sorted(c, 3, 8);  join(c, n, got, sizeof got);  q_case_s("插在最后", got, "1 3 5 8");
            n = insert_sorted(d, 0, 6);  join(d, n, got, sizeof got);  q_case_s("空数组", got, "6");
            n = insert_sorted(e, 3, 4);  join(e, n, got, sizeof got);  q_case_s("插相等的", got, "2 4 4 6");
        }
    }
    q_end();

    q_begin("题4");
    {
        int a[] = {5, 8, 3, 6, 1}, b[] = {2, 4, 6}, c[] = {9, 7, 11, 10, 12, 1, 2};
        cap_reset(); odd_even(a, LEN(a)); q_case_text("5 8 3 6 1", cap_buf, "5 3 1\n6 8\n");
        cap_reset(); odd_even(b, LEN(b)); q_case_text("全是偶数", cap_buf, "\n2 4 6\n");
        cap_reset(); odd_even(c, LEN(c)); q_case_text("7 个数", cap_buf, "11 9 7 1\n2 10 12\n");
    }
    q_end();

    q_begin("题5");
    {
        int a[] = {9, 2, 7, 4, 5}, b[] = {6, 1, 8, 3, 10}, c[10] = {NOT_TOUCHED};
        int d[] = {3, 3, 1}, e[] = {2, 3}, f[5] = {NOT_TOUCHED};
        merge_sorted(a, 5, b, 5, c);
        if (c[0] == NOT_TOUCHED) q_case_i("两组 5 个", NOT_DONE, 0);
        else {
            join(c, 10, got, sizeof got);  q_case_s("两组 5 个", got, "1 2 3 4 5 6 7 8 9 10");
            merge_sorted(d, 3, e, 2, f);  join(f, 5, got, sizeof got);  q_case_s("有重复、长度不同", got, "1 2 3 3 3");
        }
    }
    q_end();

    return summary("环06");
}
