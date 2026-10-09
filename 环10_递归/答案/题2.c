/* 题2 答案。卡点：先递归后输出，高位才在前；负数先处理符号。 */
#include "capture.h"

void convert(int n)
{
    if (n < 0) { putchar('-'); n = -n; }
    if (n >= 10) convert(n / 10);
    putchar('0' + n % 10);
}
