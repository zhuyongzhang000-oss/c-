/* 题4 答案。卡点：跳空格 → 记起点 → 数长度；位置是起点 - s1。 */
#include <string.h>

int find_len_word(char *s1, char *s2)
{
    int len2 = (int)strlen(s2), len;
    char *p = s1, *start;
    while (*p != '\0') {
        while (*p == ' ') p++;              /* 跳过空格 */
        if (*p == '\0') break;
        start = p;
        len = 0;
        while (*p != ' ' && *p != '\0') { len++; p++; }
        if (len > len2) return (int)(start - s1);
    }
    return -1;
}
