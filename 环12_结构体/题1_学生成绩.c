/*
 * 环12 题1【代表题】教材第9章习题5（川师本科卷 2016-17、2018-19 都考过这个题型）
 * 原题：有 10 个学生，每个学生的数据包括学号、姓名、3 门课程的成绩，从键盘输入 10 个学生数据，
 *       要求输出 3 门课程总平均成绩，以及最高分的学生的数据（包括学号、姓名、3 门课程成绩、平均分数）。
 *
 * 「3 门课程总平均成绩」有两种理解，这里两个都写：
 *   course_avg(s, n, avg)：avg[0]、avg[1]、avg[2] 分别是三门课各自的平均分。
 *   best_student(s, n)：返回平均分最高的学生的下标（并列取前面那个）。
 * 结构体 struct Student 在 stu.h 里。
 * 卡住先看：讲义 第③节
 */
#include "stu.h"

void course_avg(struct Student s[], int n, double avg[3])
{
    /* 在这里写 */
}

int best_student(struct Student s[], int n)
{
    return -12345;    /* 未做标记：删掉这行，开始写 */
}
