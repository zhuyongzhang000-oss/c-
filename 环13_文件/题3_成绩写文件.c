/*
 * 环13 题3【变式】教材第10章习题5
 * 原题：有 5 个学生，每个学生有 3 门课程的成绩，从键盘输入学生数据（包括学号、姓名、3 门课程成绩），
 *       计算出平均成绩，将原有数据和计算出的平均分数存放在磁盘文件 stud 中。
 *
 * 你要写：save_students(s, n, filename)：先算出每个学生的 s[i].avg（三门平均），
 *         再把每个学生写成一行："学号 姓名 成绩1 成绩2 成绩3 平均\n"，
 *         成绩保留 1 位小数，平均保留 2 位，例如 "101 Li 80.0 90.0 70.0 80.00\n"。
 *         struct Stud 在 stud.h 里。
 * 说明：教材答案多用 fwrite 按块写（二进制）；这里用 fprintf 写文本，测试才能逐字检查。
 * 卡住先看：讲义 第⑤节
 */
#include <stdio.h>
#include "stud.h"

void save_students(struct Stud s[], int n, const char *filename)
{
    /* 在这里写 */
}
