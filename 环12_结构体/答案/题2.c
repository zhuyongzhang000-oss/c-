/* 题2 答案。前 month-1 个月的天数加 day；闰年 2 月 29 天。 */
#include "stu.h"

int day_of_year2(struct Date d)
{
    int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i, total = d.day;
    if ((d.year % 4 == 0 && d.year % 100 != 0) || d.year % 400 == 0) days[2] = 29;
    for (i = 1; i < d.month; i++) total += days[i];
    return total;
}
