/* 题4 答案。卡点：项要 fabs 再比较；相邻两项比是 -x*x/((2n-1)*(2n))。 */
#include <math.h>

double cos_series(double x)
{
    double s = 0, t = 1;     /* 第一项 1 */
    int n = 0;
    while (fabs(t) >= 1e-5) {
        s += t;
        n++;
        t = -t * x * x / ((2 * n - 1) * (2 * n));
    }
    return s;
}
