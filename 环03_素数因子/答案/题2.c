/* 题2 答案。卡点：循环条件是余数不为 0；最小公倍数先除后乘。 */
int gcd(int m, int n)
{
    int r;
    while (n != 0) {
        r = m % n;
        m = n;
        n = r;
    }
    return m;
}

int lcm(int m, int n)
{
    return m / gcd(m, n) * n;
}
