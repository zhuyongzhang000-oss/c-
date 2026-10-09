/* 题5 答案。思路：重复 m 次「最后一个存起来，其余后移一格，放到最前」。m 先对 n 取模。 */
void move(int *a, int n, int m)
{
    int k, t, *p;
    if (n <= 0) return;
    m %= n;
    for (k = 0; k < m; k++) {
        t = *(a + n - 1);
        for (p = a + n - 1; p > a; p--) *p = *(p - 1);
        *a = t;
    }
}
