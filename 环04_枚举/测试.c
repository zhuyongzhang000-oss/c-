/*
 * 环04 测试：一次测完 5 题。你不用改这个文件。
 * 运行 ring04_test，把最后一行复制给 Claude（有错的题，再贴上那道题的函数）。
 */
#define CAPTURE_IMPL
#include "check.h"

void chicken_rabbit(int heads, int legs);
void exchange(int total);
int count_ways(int total);
void print_pairs(void);
void hundred_chickens(void);

/* 期望输出由测试自己算，按题目规定的顺序 */
static void expect_exchange(int total, char *out, size_t size)
{
    int y, z, count = 0;
    char line[40];
    out[0] = '\0';
    for (z = 0; z <= total / 5; z++)
        for (y = 0; y <= (total - 5 * z) / 2; y++) {
            snprintf(line, sizeof line, "%d %d %d\n", total - 5 * z - 2 * y, y, z);
            strncat(out, line, size - strlen(out) - 1);
            count++;
        }
    snprintf(line, sizeof line, "%d\n", count);
    strncat(out, line, size - strlen(out) - 1);
}

int main(void)
{
    static char want[20000];
    console_utf8();
    printf("环04 枚举与组合 测试\n\n");

    q_begin("题1");
    cap_reset(); chicken_rabbit(35, 94);  q_case_text("35头94腿", cap_buf, "23 12\n");
    cap_reset(); chicken_rabbit(10, 30);  q_case_text("10头30腿", cap_buf, "5 5\n");
    cap_reset(); chicken_rabbit(10, 20);  q_case_text("10头20腿", cap_buf, "10 0\n");
    cap_reset(); chicken_rabbit(3, 7);    q_case_text("3头7腿", cap_buf, "无解\n");
    cap_reset(); chicken_rabbit(5, 30);   q_case_text("5头30腿", cap_buf, "无解\n");
    q_end();

    q_begin("题2");
    cap_reset(); exchange(10);  expect_exchange(10, want, sizeof want);  q_case_text("10元", cap_buf, want);
    cap_reset(); exchange(100); expect_exchange(100, want, sizeof want); q_case_text("100元", cap_buf, want);
    q_end();

    q_begin("题3");
    q_case_i("total=10", count_ways(10), 10);
    q_case_i("total=100", count_ways(100), 541);
    q_case_i("total=1", count_ways(1), 1);
    q_case_i("total=0", count_ways(0), 1);
    q_end();

    q_begin("题4");
    cap_reset(); print_pairs();  q_case_text("名单", cap_buf, "A--Z B--X C--Y\n");
    q_end();

    q_begin("题5");
    cap_reset(); hundred_chickens();
    q_case_text("百钱百鸡", cap_buf, "0 25 75\n4 18 78\n8 11 81\n12 4 84\n4\n");
    q_end();

    return summary("环04");
}
