/* 题1 答案。第 i 行（1 开始）有 n-i+1 个星号。 */
#include "capture.h"

void triangle(int n)
{
    int i, j;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n - i + 1; j++) printf("*");
        printf("\n");
    }
}
