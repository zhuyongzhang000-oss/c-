/* 题2 答案。卡点：中间变量是 double，不是指针；交换的是 *a 和 *b。 */
void swap(double *a, double *b)
{
    double t = *a;
    *a = *b;
    *b = t;
}
