/* 题5 答案。卡点：循环条件同时判断相等和没到结尾；最后返回差。 */
int my_strcmp(char s1[], char s2[])
{
    int i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0') i++;
    return s1[i] - s2[i];
}
