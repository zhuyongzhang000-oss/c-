/* 题5 答案。注意：真题的参考程序把 ReverseMatrix 写成了 180 度旋转，那是错的；转置是 b[j][i] = a[i][j]。 */
#include "capture.h"

void ReverseMatrix(int a[][3], int b[][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            b[j][i] = a[i][j];
}

void AddMatrix(int a[][3], int b[][3], int c[][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            c[i][j] = a[i][j] + b[i][j];
}

void OutputMatrix(int a[][3])
{
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) printf(j ? " %d" : "%d", a[i][j]);
        printf("\n");
    }
}
