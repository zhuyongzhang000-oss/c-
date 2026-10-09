/* 题5 答案。卡点：只加前 m-1 个月；闰年条件三段写全。 */
int day_of_year(int y, int m, int d)
{
    int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int leap = (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
    int i, sum = d;
    for (i = 1; i < m; i++)
        sum += days[i];
    if (m > 2 && leap)
        sum += 1;
    return sum;
}
