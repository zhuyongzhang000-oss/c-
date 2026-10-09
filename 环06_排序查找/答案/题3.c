/* 题3 答案。卡点：pos 找第一个不小于 x 的；从右往左搬。 */
int insert_sorted(int a[], int n, int x)
{
    int pos = 0, i;
    while (pos < n && a[pos] < x) pos++;
    for (i = n; i > pos; i--) a[i] = a[i - 1];
    a[pos] = x;
    return n + 1;
}
