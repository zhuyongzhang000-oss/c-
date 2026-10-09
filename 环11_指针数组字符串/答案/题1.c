/* 题1 答案。卡点：第 k 个是 src+k-1；先判断 k 合法；最后补 '\0'。 */
void copy_from_k(char *src, char *dest, int k)
{
    char *p = src;
    int len = 0;
    while (*p != '\0') { len++; p++; }       /* 用指针数长度 */
    if (k < 1 || k > len) { *dest = '\0'; return; }
    p = src + k - 1;
    while (*p != '\0') { *dest = *p; dest++; p++; }
    *dest = '\0';
}
