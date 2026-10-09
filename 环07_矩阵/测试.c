/*
 * 环07 测试：一次测完 5 题。你不用改这个文件。
 * 运行 ring07_test，把最后一行复制给 Claude（有错的题，再贴上那道题的函数）。
 */
#define CAPTURE_IMPL
#include "check.h"

void transpose(int a[][10], int n);
void lower_triangle(int n);
void local_max(int a[][10], int m, int n);
void rotate(int a[][4], int b[][4]);
void mul3(int a[][10], int b[][10], int c[][10], int d[][10], int n);

/* 把 n×n（列宽 10）的矩阵拼成 "1 2/3 4" 的样子 */
static void join10(int a[][10], int m, int n, char *out, size_t size)
{
    char num[16];
    int i, j;
    out[0] = '\0';
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++) {
            snprintf(num, sizeof num, "%s%d", j ? " " : (i ? "/" : ""), a[i][j]);
            strncat(out, num, size - strlen(out) - 1);
        }
}

static void join4(int a[][4], char *out, size_t size)
{
    char num[16];
    int i, j;
    out[0] = '\0';
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++) {
            snprintf(num, sizeof num, "%s%d", j ? " " : (i ? "/" : ""), a[i][j]);
            strncat(out, num, size - strlen(out) - 1);
        }
}

#define MARK 77777

int main(void)
{
    char got[600];
    int i, j;
    console_utf8();
    printf("环07 矩阵 测试\n\n");

    q_begin("题1");
    {
        int a[10][10], b[10][10] = {{5}}, c[10][10];
        for (i = 0; i < 3; i++) for (j = 0; j < 3; j++) a[i][j] = i * 3 + j + 1;
        for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) c[i][j] = i * 4 + j;
        transpose(a, 3);
        if (a[0][1] == 2 && a[1][0] == 4) q_case_i("3×3", NOT_DONE, 0);     /* 一点没变 */
        else {
            join10(a, 3, 3, got, sizeof got);  q_case_s("3×3", got, "1 4 7/2 5 8/3 6 9");
            transpose(b, 1);  join10(b, 1, 1, got, sizeof got);  q_case_s("1×1", got, "5");
            transpose(c, 4);  join10(c, 4, 4, got, sizeof got);
            q_case_s("4×4", got, "0 4 8 12/1 5 9 13/2 6 10 14/3 7 11 15");
        }
    }
    q_end();

    q_begin("题2");
    cap_reset(); lower_triangle(3);  q_case_text("n=3", cap_buf, "1\n7 9\n13 15 17\n");
    cap_reset(); lower_triangle(5);
    q_case_text("n=5", cap_buf, "1\n11 13\n21 23 25\n31 33 35 37\n41 43 45 47 49\n");
    cap_reset(); lower_triangle(1);  q_case_text("n=1", cap_buf, "1\n");
    q_end();

    q_begin("题3");
    {
        int a[10][10] = {{5, 5, 5, 5}, {5, 6, 7, 5}, {5, 8, 4, 5}, {5, 5, 5, 5}};
        int b[10][10] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        int c[10][10] = {{0, 0, 0, 0, 0}, {0, 9, 0, 9, 0}, {0, 0, 0, 0, 0}};
        int d[10][10] = {{9, 9, 9}, {9, 1, 9}};
        cap_reset(); local_max(a, 4, 4);  q_case_text("4×4", cap_buf, "2 3 7\n3 2 8\n");
        cap_reset(); local_max(b, 3, 3);  q_case_text("没有极大值", cap_buf, "无\n");
        cap_reset(); local_max(c, 3, 5);  q_case_text("3×5", cap_buf, "2 2 9\n2 4 9\n");
        cap_reset(); local_max(d, 2, 3);  q_case_text("只有两行（没有内部）", cap_buf, "无\n");
    }
    q_end();

    q_begin("题4");
    {
        int a[4][4], b[4][4];
        for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) { a[i][j] = i * 4 + j + 1; b[i][j] = MARK; }
        rotate(a, b);
        if (b[0][0] == MARK) q_case_i("1~16", NOT_DONE, 0);
        else {
            join4(b, got, sizeof got);
            q_case_s("1~16", got, "13 9 5 1/14 10 6 2/15 11 7 3/16 12 8 4");
            join4(a, got, sizeof got);
            q_case_s("原数组没被改", got, "1 2 3 4/5 6 7 8/9 10 11 12/13 14 15 16");
        }
    }
    q_end();

    q_begin("题5");
    {
        int a[10][10] = {{1, 2}, {3, 4}}, b[10][10] = {{0, 1}, {1, 0}}, c[10][10] = {{2, 0}, {0, 3}};
        int d[10][10];
        int e[10][10] = {{1, 0, 2}, {0, 1, 0}, {3, 0, 1}}, f[10][10] = {{1, 1, 0}, {0, 1, 1}, {1, 0, 1}};
        int g[10][10] = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}};
        for (i = 0; i < 10; i++) for (j = 0; j < 10; j++) d[i][j] = MARK;
        mul3(a, b, c, d, 2);
        if (d[0][0] == MARK) q_case_i("2×2", NOT_DONE, 0);
        else {
            join10(d, 2, 2, got, sizeof got);  q_case_s("2×2", got, "4 3/8 9");
            mul3(e, f, g, d, 3);  join10(d, 3, 3, got, sizeof got);  q_case_s("3×3", got, "6 2 4/0 2 2/8 6 2");
            join10(a, 2, 2, got, sizeof got);  q_case_s("A 没被改", got, "1 2/3 4");
        }
    }
    q_end();

    return summary("环07");
}
