/* 题4 答案。公式：b[j][n-1-i] = a[i][j]（n=4）。 */
void rotate(int a[][4], int b[][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            b[j][3 - i] = a[i][j];
}
