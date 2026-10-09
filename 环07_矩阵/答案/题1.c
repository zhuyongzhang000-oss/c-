/* 题1 答案。卡点：j 从 i+1 开始，只换上三角那一侧。 */
void transpose(int a[][10], int n)
{
    int i, j, t;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++) {
            t = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = t;
        }
}
