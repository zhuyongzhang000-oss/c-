/* 题1 答案。卡点：n<2 先排除；上界 i*i<=n（带等号）。 */
int is_prime(int n)
{
    int i;
    if (n < 2) return 0;
    for (i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}
