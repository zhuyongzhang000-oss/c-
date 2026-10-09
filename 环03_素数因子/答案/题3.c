/* 题3 答案。卡点：先判断再打印；逗号只在两个因子之间。 */
#include "capture.h"

void print_perfect(int limit)
{
    int n, i, s;
    for (n = 2; n <= limit; n++) {
        s = 0;
        for (i = 1; i < n; i++)
            if (n % i == 0) s += i;
        if (s == n) {
            printf("%d its factors are 1", n);     /* 1 一定是因子，先打出来 */
            for (i = 2; i < n; i++)
                if (n % i == 0) printf(",%d", i);
            printf("\n");
        }
    }
}
