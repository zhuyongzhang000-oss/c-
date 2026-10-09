/* 题3 答案。先算平均再写；格式按题目要求。 */
#include <stdio.h>
#include "stud.h"

void save_students(struct Stud s[], int n, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    int i;
    if (fp == NULL) return;
    for (i = 0; i < n; i++) {
        s[i].avg = (s[i].score[0] + s[i].score[1] + s[i].score[2]) / 3;
        fprintf(fp, "%d %s %.1f %.1f %.1f %.2f\n", s[i].num, s[i].name,
                s[i].score[0], s[i].score[1], s[i].score[2], s[i].avg);
    }
    fclose(fp);
}
