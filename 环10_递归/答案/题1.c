/* 题1 答案。关系：今天 = (明天 + 1) * 2；基例第 10 天是 1。 */
int peach(int day)
{
    if (day == 10) return 1;
    return (peach(day + 1) + 1) * 2;
}
