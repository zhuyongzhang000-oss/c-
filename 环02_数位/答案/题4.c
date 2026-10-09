/* 题4 答案。卡点：先复制 x 再数位数；10 的幂用整数乘。 */
int is_automorphic(int x)
{
    int m = x, mod = 1;
    while (m > 0) {
        mod *= 10;
        m /= 10;
    }
    return x * x % mod == x;
}
