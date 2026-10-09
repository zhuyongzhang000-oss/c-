/* 题1 答案。卡点：按列求平均；最高者记下标，比较平均分。 */
#include "stu.h"

void course_avg(struct Student s[], int n, double avg[3])
{
    int i, k;
    for (k = 0; k < 3; k++) {
        double sum = 0;
        for (i = 0; i < n; i++) sum += s[i].score[k];
        avg[k] = sum / n;
    }
}

int best_student(struct Student s[], int n)
{
    int i, best = 0;
    double a, b;
    for (i = 1; i < n; i++) {
        a = (s[i].score[0] + s[i].score[1] + s[i].score[2]) / 3;
        b = (s[best].score[0] + s[best].score[1] + s[best].score[2]) / 3;
        if (a > b) best = i;
    }
    return best;
}
