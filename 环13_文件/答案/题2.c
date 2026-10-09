/* 题2 答案。按字符复制；读出来时转大写再输出。 */
#include <stdio.h>
#include "capture.h"

void save_lines(FILE *in, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    int ch;
    if (fp == NULL) return;
    while ((ch = fgetc(in)) != EOF) fputc(ch, fp);
    fclose(fp);
}

void show_upper(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    int ch;
    if (fp == NULL) return;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch >= 'a' && ch <= 'z') ch = ch - 32;
        putchar(ch);
    }
    fclose(fp);
}
