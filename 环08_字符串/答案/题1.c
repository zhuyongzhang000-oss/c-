/* 题1 答案。卡点：从 len-1 开始；空串时循环一次都不跑。 */
#include <string.h>
#include "capture.h"

void print_reverse(char s[])
{
    int i;
    for (i = (int)strlen(s) - 1; i >= 0; i--) printf("%c", s[i]);
    printf("\n");
}
