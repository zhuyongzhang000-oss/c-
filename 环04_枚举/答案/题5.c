/* 题5 答案。范围：公鸡 <= 20，母鸡 <= 33；小鸡 = 100 - 公鸡 - 母鸡。卡点：先判 z % 3 == 0。 */
#include "capture.h"

void hundred_chickens(void)
{
    int x, y, z, count = 0;
    for (x = 0; x <= 20; x++)
        for (y = 0; y <= 33; y++) {
            z = 100 - x - y;
            if (z >= 0 && z % 3 == 0 && 5 * x + 3 * y + z / 3 == 100) {
                printf("%d %d %d\n", x, y, z);
                count++;
            }
        }
    printf("%d\n", count);
}
