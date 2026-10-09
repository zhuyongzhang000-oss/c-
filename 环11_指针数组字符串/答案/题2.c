/* 题2 答案。卡点：相等且没到结尾才往后走；返回差值。 */
int my_strcmp(char *p1, char *p2)
{
    while (*p1 == *p2 && *p1 != '\0') { p1++; p2++; }
    return *p1 - *p2;
}
