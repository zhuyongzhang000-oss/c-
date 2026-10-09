/* 题2 答案。卡点：左下三角是 j <= i；空格只在数之间。 */
#include "capture.h"

void lower_triangle(int n)
{
    int a[10][10], i, j, num = 1;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) { a[i][j] = num; num += 2; }
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) printf(j ? " %d" : "%d", a[i][j]);
        printf("\n");
    }
}
