/* 让测试能看到你用 printf / putchar / puts 打印的内容。
 * 你照常写 printf 就行，不用管这个文件。 */
#ifndef CAPTURE_H
#define CAPTURE_H
#include <stdio.h>

int cap_printf(const char *fmt, ...);
int cap_putchar(int c);
int cap_puts(const char *s);

#define printf  cap_printf
#define putchar cap_putchar
#define puts    cap_puts
#endif
