/* 题2 答案（二分）。卡点：条件 left <= right；移动时是 mid+1 / mid-1。 */
int search(int a[], int n, int x)
{
    int left = 0, right = n - 1, mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (a[mid] == x) return mid;
        else if (a[mid] < x) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
