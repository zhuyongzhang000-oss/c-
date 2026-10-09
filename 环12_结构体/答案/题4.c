/* 题4 答案（原书答案就是这几行）。卡点：交换整条记录 tmp = a[i]。 */
#include "stu.h"

void fun(STREC a[], int n)
{
    STREC tmp;
    int i, j;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            if (a[i].s < a[j].s) { tmp = a[i]; a[i] = a[j]; a[j] = tmp; }
}
