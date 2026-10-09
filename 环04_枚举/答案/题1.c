/* 题1 答案。卡点：没找到时要打印无解——用标志变量记有没有找到。 */
#include "capture.h"

void chicken_rabbit(int heads, int legs)
{
    int x, found = 0;
    for (x = 0; x <= heads; x++) {
        if (2 * x + 4 * (heads - x) == legs) {
            printf("%d %d\n", x, heads - x);
            found = 1;
        }
    }
    if (!found) printf("无解\n");
}
