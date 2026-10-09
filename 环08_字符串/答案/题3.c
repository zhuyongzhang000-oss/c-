/* 题3 答案。卡点：减 '0' 才是数值。 */
int str_to_int(char s[])
{
    int v = 0, i;
    for (i = 0; s[i] != '\0'; i++) v = v * 10 + (s[i] - '0');
    return v;
}
