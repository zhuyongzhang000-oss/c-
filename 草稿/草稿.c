/*
 * 草稿：随便写完整程序的地方（运行 draft）
 * 用来：出口前练手写的完整程序（main + scanf + printf），或试一下 Claude 讲的某个写法。
 * 内容随便改，不影响测试。运行后在黑色窗口里输入数据，回车。
 */
#include <stdio.h>

int main(void)
{
    int n;
    printf("输入一个整数：");
    if (scanf("%d", &n) != 1) return 0;
    printf("你输入的是 %d\n", n);
    return 0;
}
