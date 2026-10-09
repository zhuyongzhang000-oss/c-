/* 题5 答案。一格一格填（pos = 0 ~ n*n-1）；每格从 1 试到 n；行列都没出现过才填；回来后撤销。 */
#include "capture.h"

static int sq[4][4], N, total;

static int ok(int row, int col, int v)
{
    int k;
    for (k = 0; k < col; k++) if (sq[row][k] == v) return 0;   /* 这一行前面 */
    for (k = 0; k < row; k++) if (sq[k][col] == v) return 0;   /* 这一列上面 */
    return 1;
}

static void fill(int pos)
{
    int row = pos / N, col = pos % N, v, i, j;
    if (pos == N * N) {                       /* 填满了：输出一个 */
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) printf(j ? " %d" : "%d", sq[i][j]);
            printf("\n");
        }
        printf("\n");
        total++;
        return;
    }
    for (v = 1; v <= N; v++)
        if (ok(row, col, v)) {
            sq[row][col] = v;
            fill(pos + 1);
            sq[row][col] = 0;                 /* 撤销，试下一个值 */
        }
}

void latin(int n)
{
    N = n;
    total = 0;
    fill(0);
    printf("共 %d 个\n", total);
}
