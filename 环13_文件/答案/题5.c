/* 题5 答案。fscanf 返回 6 才算读到一条；整条记录交换；同样格式写回。 */
#include <stdio.h>
#include "stud.h"

void sort_file(const char *in, const char *out)
{
    struct Stud s[50], t;
    int n = 0, i, j;
    FILE *fp = fopen(in, "r");
    if (fp == NULL) return;
    while (n < 50 && fscanf(fp, "%d %s %lf %lf %lf %lf", &s[n].num, s[n].name,
                            &s[n].score[0], &s[n].score[1], &s[n].score[2], &s[n].avg) == 6)
        n++;
    fclose(fp);
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - 1 - i; j++)
            if (s[j].avg < s[j + 1].avg) { t = s[j]; s[j] = s[j + 1]; s[j + 1] = t; }
    fp = fopen(out, "w");
    if (fp == NULL) return;
    for (i = 0; i < n; i++)
        fprintf(fp, "%d %s %.1f %.1f %.1f %.2f\n", s[i].num, s[i].name,
                s[i].score[0], s[i].score[1], s[i].score[2], s[i].avg);
    fclose(fp);
}
