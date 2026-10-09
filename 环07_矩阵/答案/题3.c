/* 题3 答案。卡点：只在内部找；用 found 记有没有找到。 */
#include "capture.h"

void local_max(int a[][10], int m, int n)
{
    int i, j, found = 0;
    for (i = 1; i < m - 1; i++)
        for (j = 1; j < n - 1; j++)
            if (a[i][j] > a[i - 1][j] && a[i][j] > a[i + 1][j] &&
                a[i][j] > a[i][j - 1] && a[i][j] > a[i][j + 1]) {
                printf("%d %d %d\n", i + 1, j + 1, a[i][j]);
                found = 1;
            }
    if (!found) printf("无\n");
}
