/* 题4 答案。卡点：每行右移 2 格；最后一个星号后面不加空格。 */
#include "capture.h"

void slanted(int rows)
{
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < 2 * i; j++) printf(" ");
        for (j = 1; j <= 5; j++) {
            printf("*");
            if (j < 5) printf(" ");
        }
        printf("\n");
    }
}
