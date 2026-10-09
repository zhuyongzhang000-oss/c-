/* 题1 答案（冒泡）。卡点：内层上界 n-1-i；相等时不交换。 */
void sort_asc(int a[], int n)
{
    int i, j, t;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - 1 - i; j++)
            if (a[j] > a[j + 1]) { t = a[j]; a[j] = a[j + 1]; a[j + 1] = t; }
}
