/* 题3 答案。卡点：z、y 确定后 x 唯一且一定 >= 0，所以每组 (z, y) 就是一种。 */
int count_ways(int total)
{
    int y, z, count = 0;
    for (z = 0; z <= total / 5; z++)
        for (y = 0; y <= (total - 5 * z) / 2; y++)
            count++;
    return count;
}
