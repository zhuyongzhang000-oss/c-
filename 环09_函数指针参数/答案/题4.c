/* 题4 答案。卡点：用 *n 当长度；最后 (*n)++。 */
void insert(int arr[], int *n, int x)
{
    int pos = 0, i;
    while (pos < *n && arr[pos] < x) pos++;
    for (i = *n; i > pos; i--) arr[i] = arr[i - 1];
    arr[pos] = x;
    (*n)++;
}
