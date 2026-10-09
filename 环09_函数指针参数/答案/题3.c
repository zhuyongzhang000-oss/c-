/* 题3 答案。卡点：初值用 arr[0]；结果写进 *pt1、*pt2。 */
void maxmin(int arr[], int *pt1, int *pt2, int n)
{
    int i;
    *pt1 = *pt2 = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] > *pt1) *pt1 = arr[i];
        if (arr[i] < *pt2) *pt2 = arr[i];
    }
}
