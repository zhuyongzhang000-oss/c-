/* 题1 答案。卡点：不要真的算阶乘（int 到 13! 就溢出），用 t = t/i 递推。 */
double e_series(int n)
{
    double s = 1, t = 1;    /* 第 0 项是 1 */
    int i;
    for (i = 1; i <= n; i++) {
        t = t / i;          /* t 从 1/(i-1)! 变成 1/i! */
        s += t;
    }
    return s;
}
