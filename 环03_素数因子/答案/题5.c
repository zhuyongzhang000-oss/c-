/* 题5 答案。卡点：内层上界带等号；空格只在两个数之间；最后换行。 */
#include "capture.h"

void print_primes(int a, int b)
{
    int n, j, flag, first = 1;
    for (n = a; n <= b; n++) {
        flag = (n >= 2);
        for (j = 2; j * j <= n; j++)
            if (n % j == 0) { flag = 0; break; }
        if (flag) {
            printf(first ? "%d" : " %d", n);
            first = 0;
        }
    }
    printf("\n");
}
