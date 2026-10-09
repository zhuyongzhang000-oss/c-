/* 题2 答案。卡点：下一项 = 上一项*10 + a；结果用 long long。 */
long long repeat_sum(int a, int n)
{
    long long s = 0, t = 0;
    int i;
    for (i = 1; i <= n; i++) {
        t = t * 10 + a;     /* 3 -> 33 -> 333 */
        s += t;
    }
    return s;
}
