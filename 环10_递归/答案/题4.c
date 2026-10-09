/* 题4 答案。两个基例；n 是 int，但式子里有 double 的 x，整体按 double 算。 */
double legendre(int n, double x)
{
    if (n == 0) return 1;
    if (n == 1) return x;
    return ((2 * n - 1) * x * legendre(n - 1, x) - (n - 1) * legendre(n - 2, x)) / n;
}
