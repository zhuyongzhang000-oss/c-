/* 题3 答案。卡点：分子分母同时更新要先存旧值；除法前转 double。 */
double frac_sum(int n)
{
    double s = 0;
    long long a = 2, b = 1, old;   /* 分子 a，分母 b */
    int i;
    for (i = 1; i <= n; i++) {
        s += (double)a / b;
        old = a;
        a = a + b;
        b = old;
    }
    return s;
}
