/* 题4 答案。卡点：两个下标分开；最后补 '\0'。 */
void my_strcat(char dest[], char src[])
{
    int i = 0, j = 0;
    while (dest[i] != '\0') i++;
    while (src[j] != '\0') dest[i++] = src[j++];
    dest[i] = '\0';
}
