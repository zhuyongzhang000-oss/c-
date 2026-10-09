/* 题5 答案。卡点：每个 i 都要重新复制到 t 再拆；一个数里可能有多个 1。 */
int count_one(int n)
{
    int i, t, count = 0;
    for (i = 1; i <= n; i++) {
        t = i;
        while (t > 0) {
            if (t % 10 == 1) count++;
            t /= 10;
        }
    }
    return count;
}
