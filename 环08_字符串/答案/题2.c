/* 题2 答案。卡点：只比前一半；有一对不同立刻返回 0。 */
#include <string.h>

int is_palindrome(char s[])
{
    int len = (int)strlen(s), i;
    for (i = 0; i < len / 2; i++)
        if (s[i] != s[len - 1 - i]) return 0;
    return 1;
}
