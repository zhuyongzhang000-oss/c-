/* 题4 答案。读两个文件进同一个数组（跳过换行）→ 冒泡排序 → 写。 */
#include <stdio.h>

void merge_files(const char *fa, const char *fb, const char *fc)
{
    char c[200];
    int n = 0, ch, i, j, t;
    const char *names[2];
    FILE *fp;
    names[0] = fa;
    names[1] = fb;
    for (i = 0; i < 2; i++) {
        fp = fopen(names[i], "r");
        if (fp == NULL) return;
        while ((ch = fgetc(fp)) != EOF && n < 199)
            if (ch != '\n') c[n++] = (char)ch;
        fclose(fp);
    }
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - 1 - i; j++)
            if (c[j] > c[j + 1]) { t = c[j]; c[j] = c[j + 1]; c[j + 1] = (char)t; }
    fp = fopen(fc, "w");
    if (fp == NULL) return;
    for (i = 0; i < n; i++) fputc(c[i], fp);
    fputc('\n', fp);
    fclose(fp);
}
