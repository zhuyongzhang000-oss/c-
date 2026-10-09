/* 题4 答案。卡点：两组各自计数；奇数降序、偶数升序比较方向不同；空格只在两个数之间。 */
#include "capture.h"

void odd_even(int a[], int n)
{
    int odd[100], even[100], no = 0, ne = 0, i, j, t;
    for (i = 0; i < n; i++) {
        if (a[i] % 2 != 0) odd[no++] = a[i];
        else even[ne++] = a[i];
    }
    for (i = 0; i < no - 1; i++)
        for (j = 0; j < no - 1 - i; j++)
            if (odd[j] < odd[j + 1]) { t = odd[j]; odd[j] = odd[j + 1]; odd[j + 1] = t; }
    for (i = 0; i < ne - 1; i++)
        for (j = 0; j < ne - 1 - i; j++)
            if (even[j] > even[j + 1]) { t = even[j]; even[j] = even[j + 1]; even[j + 1] = t; }
    for (i = 0; i < no; i++) printf(i ? " %d" : "%d", odd[i]);
    printf("\n");
    for (i = 0; i < ne; i++) printf(i ? " %d" : "%d", even[i]);
    printf("\n");
}
