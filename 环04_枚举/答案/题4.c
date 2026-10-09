/* 题4 答案。卡点：三人的对手要互不相同；字符可以直接 ++ 和比较。 */
#include "capture.h"

void print_pairs(void)
{
    char a, b, c;
    for (a = 'X'; a <= 'Z'; a++)
        for (b = 'X'; b <= 'Z'; b++)
            for (c = 'X'; c <= 'Z'; c++)
                if (a != b && a != c && b != c && a != 'X' && c != 'X' && c != 'Z')
                    printf("A--%c B--%c C--%c\n", a, b, c);
}
