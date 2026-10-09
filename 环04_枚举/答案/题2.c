/* 题2 答案。卡点：y 的上界随 z 变；x 算出来不用枚举；count 在循环外清零。 */
#include "capture.h"

void exchange(int total)
{
    int y, z, count = 0;
    for (z = 0; z <= total / 5; z++)
        for (y = 0; y <= (total - 5 * z) / 2; y++) {
            printf("%d %d %d\n", total - 5 * z - 2 * y, y, z);
            count++;
        }
    printf("%d\n", count);
}
