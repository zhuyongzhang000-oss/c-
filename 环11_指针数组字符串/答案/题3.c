/* 题3 答案。卡点：n <= 1 先返回，避免形成 a-1；l < r 时才交换。 */
void reverse(int *a, int n)
{
    int *l = a, *r, t;
    if (n <= 1) return;
    r = a + n - 1;
    while (l < r) { t = *l; *l = *r; *r = t; l++; r--; }
}
