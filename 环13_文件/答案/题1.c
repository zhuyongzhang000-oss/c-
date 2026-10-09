/* 题1 答案。卡点：ch 用 int；判 NULL；'!' 不写；最后 fclose。 */
#include <stdio.h>

void save_upper(FILE *in, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    int ch;
    if (fp == NULL) { printf("打不开文件\n"); return; }
    while ((ch = fgetc(in)) != EOF && ch != '!') {
        if (ch >= 'a' && ch <= 'z') ch = ch - 32;
        fputc(ch, fp);
    }
    fclose(fp);
}
