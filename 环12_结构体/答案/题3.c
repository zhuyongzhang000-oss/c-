/* 题3 答案。逐个成员输出。 */
#include "stu.h"
#include "capture.h"

void print(struct Student s[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d %s %.1f %.1f %.1f\n", s[i].num, s[i].name, s[i].score[0], s[i].score[1], s[i].score[2]);
}
