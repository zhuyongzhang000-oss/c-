/* 题1 答案。参数都是 double，/2 不会整除。 */
double trapezoid_area(double top, double bottom, double h)
{
    return (top + bottom) * h / 2;
}
