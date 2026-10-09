/* 题5 答案。卡点：先各自排序；合并后两个 while 收尾。 */
static void bubble(int a[], int n)
{
    int i, j, t;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - 1 - i; j++)
            if (a[j] > a[j + 1]) { t = a[j]; a[j] = a[j + 1]; a[j + 1] = t; }
}

void merge_sorted(int a[], int na, int b[], int nb, int c[])
{
    int i = 0, j = 0, k = 0;
    bubble(a, na);
    bubble(b, nb);
    while (i < na && j < nb) {
        if (a[i] <= b[j]) c[k++] = a[i++];
        else c[k++] = b[j++];
    }
    while (i < na) c[k++] = a[i++];
    while (j < nb) c[k++] = b[j++];
}
