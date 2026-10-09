/*
 * 环13 题2【变式】教材第10章习题11
 * 原题：从键盘输入若干行字符（每行长度不等），输入后把它们存储到一磁盘文件中。
 *       再从该文件中读入这些数据，将其中小写字母转换成大写字母后在显示屏上输出。
 *
 * 你要写两个函数：
 *   save_lines(in, filename)：把 in 里的全部内容（读到 EOF 为止）原样写进文件 filename。
 *   show_upper(filename)：打开文件，把内容读出来，小写变大写后输出到屏幕（printf 或 putchar）。
 * 用 fgetc/fputc 或 fgets/fputs 都可以。考试时 in 就是 stdin（键盘）。
 * 卡住先看：讲义 第③④节
 */
#include <stdio.h>
#include "capture.h"     /* 让测试看到你的屏幕输出，照常写就行 */

void save_lines(FILE *in, const char *filename)
{
    /* 在这里写 */
}

void show_upper(const char *filename)
{
    /* 在这里写 */
}
