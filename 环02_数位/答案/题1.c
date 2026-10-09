/* 题1 答案。卡点：十位是 x/10%10；比较的是立方和与原数。 */
int is_narcissus(int x)
{
    int a = x / 100, b = x / 10 % 10, c = x % 10;
    return a * a * a + b * b * b + c * c * c == x;
}
