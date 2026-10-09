/*
 * 环13 题1【代表题】教材第10章习题3（也是圣才考研真题精选综合题7）
 * 原题：从键盘输入一个字符串，将其中的小写字母全部转换成大写字母，然后输出到一个磁盘文件 test 中保存，
 *       输入的字符串以「!」结束。
 *
 * 你要写：save_upper(in, filename)：从 in 一个字符一个字符地读（fgetc(in)），读到 '!' 或文件结束就停；
 *         小写字母变大写，其他字符原样；全部写进名为 filename 的文件（"w" 方式），最后关闭文件。
 *         '!' 本身不写。考试时把 fgetc(in) 换成 getchar() 就是原题。
 * 卡住先看：讲义 第①③节
 */
#include <stdio.h>

void save_upper(FILE *in, const char *filename)
{
    /* 在这里写 */
}
