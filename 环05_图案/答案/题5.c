/* 题5 答案。卡点：两端先置 1；中间 j 从 1 到 i-1；数之间才加空格。 */
#include "capture.h"

void yanghui(int n)
{
    int a[10][10], i, j;
    for (i = 0; i < n; i++) {
        a[i][0] = a[i][i] = 1;
        for (j = 1; j < i; j++)
            a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            if (j > 0) printf(" ");
            printf("%d", a[i][j]);
        }
        printf("\n");
    }
}
