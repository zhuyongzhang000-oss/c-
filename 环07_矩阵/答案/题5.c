/* 题5 答案。卡点：中间矩阵 t；每次乘法先清零。 */
void mul3(int a[][10], int b[][10], int c[][10], int d[][10], int n)
{
    int t[10][10], i, j, k;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            t[i][j] = 0;
            for (k = 0; k < n; k++) t[i][j] += a[i][k] * b[k][j];
        }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            d[i][j] = 0;
            for (k = 0; k < n; k++) d[i][j] += t[i][k] * c[k][j];
        }
}
