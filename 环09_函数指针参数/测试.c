/*
 * 环09 测试：一次测完 5 题。你不用改这个文件。
 * 运行 ring09_test，把最后一行复制给 Claude（有错的题，再贴上那道题的函数）。
 */
#define CAPTURE_IMPL
#include "check.h"

double trapezoid_area(double top, double bottom, double h);
void swap(double *a, double *b);
void maxmin(int arr[], int *pt1, int *pt2, int n);
void insert(int arr[], int *n, int x);
void ReverseMatrix(int a[][3], int b[][3]);
void AddMatrix(int a[][3], int b[][3], int c[][3]);
void OutputMatrix(int a[][3]);

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

static void join3(int a[][3], char *out, size_t size)
{
    char num[16];
    int i, j;
    out[0] = '\0';
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            snprintf(num, sizeof num, "%s%d", j ? " " : (i ? "/" : ""), a[i][j]);
            strncat(out, num, size - strlen(out) - 1);
        }
}

#define MARK 77777

int main(void)
{
    char got[300];
    console_utf8();
    printf("环09 函数与指针参数 测试\n\n");

    q_begin("题1");
    q_case_d("3,5,4", trapezoid_area(3, 5, 4), 16.0, 1e-9);
    q_case_d("1,2,1", trapezoid_area(1, 2, 1), 1.5, 1e-9);
    q_case_d("2.5,3.5,2", trapezoid_area(2.5, 3.5, 2), 6.0, 1e-9);
    q_end();

    q_begin("题2");
    {
        double x = 1.5, y = -2.25;
        swap(&x, &y);
        if (x == 1.5 && y == -2.25) q_case_i("1.5,-2.25", NOT_DONE, 0);
        else {
            q_case_d("交换后 x", x, -2.25, 1e-12);
            q_case_d("交换后 y", y, 1.5, 1e-12);
        }
    }
    q_end();

    q_begin("题3");
    {
        int array[10] = {10, 7, 19, 29, 4, 0, 7, 35, -16, 21}, neg[3] = {-5, -9, -1}, one[1] = {4};
        int a = MARK, b = MARK;
        maxmin(array, &a, &b, 10);
        if (a == MARK) q_case_i("真题数据", NOT_DONE, 0);
        else {
            q_case_i("真题数据 max", a, 35);
            q_case_i("真题数据 min", b, -16);
            maxmin(neg, &a, &b, 3);  q_case_i("全是负数 max", a, -1);  q_case_i("全是负数 min", b, -9);
            maxmin(one, &a, &b, 1);  q_case_i("一个数 max", a, 4);     q_case_i("一个数 min", b, 4);
        }
    }
    q_end();

    q_begin("题4");
    {
        int arr[20] = {1, 3, 5, 7, 9}, n = 5, b[20] = {2, 4}, nb = 2, c[20] = {0}, nc = 0;
        insert(arr, &n, 6);
        if (n == 5 && arr[3] == 7) q_case_i("插 6", NOT_DONE, 0);          /* 数组和长度都没动 */
        else if (n == 5) q_case_i("插 6 后长度没加 1（是不是写成了 *n++）", n, 6);
        else {
            q_case_i("插 6 后的长度", n, 6);
            join(arr, n, got, sizeof got);  q_case_s("插 6", got, "1 3 5 6 7 9");
            insert(b, &nb, 1);  insert(b, &nb, 9);
            join(b, nb, got, sizeof got);   q_case_s("插最前再插最后", got, "1 2 4 9");
            insert(c, &nc, 5);
            join(c, nc, got, sizeof got);   q_case_s("空数组插 5", got, "5");
        }
    }
    q_end();

    q_begin("题5");
    {
        int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, b[3][3], c[3][3];
        int z[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        int i, j;
        for (i = 0; i < 3; i++) for (j = 0; j < 3; j++) b[i][j] = c[i][j] = MARK;
        ReverseMatrix(a, b);
        if (b[0][0] == MARK) q_case_i("转置", NOT_DONE, 0);
        else { join3(b, got, sizeof got); q_case_s("转置", got, "1 4 7/2 5 8/3 6 9"); }
        AddMatrix(a, z, c);
        if (c[0][0] == MARK) q_case_i("相加", NOT_DONE, 0);
        else { join3(c, got, sizeof got); q_case_s("相加", got, "2 2 3/4 6 6/7 8 10"); }
        cap_reset(); OutputMatrix(a);
        q_case_text("输出", cap_buf, "1 2 3\n4 5 6\n7 8 9\n");
    }
    q_end();

    return summary("环09");
}
