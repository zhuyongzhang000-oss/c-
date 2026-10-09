/* 题3 答案。卡点：n=0 单独处理；余数要倒序放；最后补 '\0'。 */
void to_binary(int n, char out[])
{
    int bits[32], len = 0, i;
    if (n == 0) { out[0] = '0'; out[1] = '\0'; return; }
    while (n > 0) {
        bits[len++] = n % 2;
        n /= 2;
    }
    for (i = 0; i < len; i++)
        out[i] = (char)('0' + bits[len - 1 - i]);
    out[len] = '\0';
}
