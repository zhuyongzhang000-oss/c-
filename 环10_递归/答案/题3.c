/* 题3 答案。两处错：① fun(n) 没写返回类型和形参类型 → int fun(int n)；② if(n=1) 是赋值 → if(n==1)。 */
int fun(int n)
{
    int c;
    if (n == 1)
        c = 10;
    else
        c = fun(n - 1) + 2;
    return (c);
}
