/* 题2 答案。卡点：先判断能被 11 整除，再比商和平方和。 */
int check(int x)
{
    int a = x / 100, b = x / 10 % 10, c = x % 10;
    return x % 11 == 0 && x / 11 == a * a + b * b + c * c;
}
