/* 题4 答案。卡点：标记数组下标就是数本身；划倍数从 i*i 开始也可以从 2*i 开始。 */
int sieve(int n, int primes[])
{
    int mark[1001] = {0};
    int i, j, cnt = 0;
    for (i = 2; i <= n; i++) mark[i] = 1;
    for (i = 2; i * i <= n; i++)
        if (mark[i])
            for (j = i * i; j <= n; j += i) mark[j] = 0;
    for (i = 2; i <= n; i++)
        if (mark[i]) primes[cnt++] = i;
    return cnt;
}
