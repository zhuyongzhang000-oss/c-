/* 题2 答案。第 i 行（0 开始）先 i 个空格。 */
#include "capture.h"

void shifted(int rows)
{
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < i; j++) printf(" ");
        printf("*****\n");
    }
}
