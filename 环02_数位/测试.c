/*
 * 环02 测试：一次测完 5 题。你不用改这个文件。
 * 运行 ring02_test，把最后一行复制给 Claude。
 */
#include <string.h>
#include "check.h"

int is_narcissus(int x);
int check(int x);
void to_binary(int n, char out[]);
int is_automorphic(int x);
int count_one(int n);

/* 用 f 把 lo~hi 扫一遍，把返回 1 的数连成 "a,b,c" 跟期望比 */
static void sweep(const char *label, int (*f)(int), int lo, int hi, const char *expected)
{
    char buf[200] = "";
    char num[16];
    int x;
    if (f(lo) == NOT_DONE) { q_case_i(label, NOT_DONE, 0); return; }
    for (x = lo; x <= hi; x++) {
        if (f(x) == 1) {
            snprintf(num, sizeof num, "%s%d", buf[0] ? "," : "", x);
            strncat(buf, num, sizeof buf - strlen(buf) - 1);
        }
    }
    q_case_s(label, buf, expected);
}

static void bin_case(int n, const char *expected)
{
    char out[40], label[20];
    memset(out, 'X', 39);
    out[39] = '\0';
    to_binary(n, out);
    snprintf(label, sizeof label, "n=%d", n);
    q_case_s(label, out, expected);
}

int main(void)
{
    console_utf8();
    printf("环02 数位 测试\n\n");

    q_begin("题1");
    q_case_i("153", is_narcissus(153), 1);
    q_case_i("154", is_narcissus(154), 0);
    sweep("100~999 全部", is_narcissus, 100, 999, "153,370,371,407");
    q_end();

    q_begin("题2");
    q_case_i("550", check(550), 1);
    q_case_i("121", check(121), 0);
    sweep("100~999 全部", check, 100, 999, "550,803");
    q_end();

    q_begin("题3");
    bin_case(1, "1");
    bin_case(6, "110");
    bin_case(100, "1100100");
    bin_case(1023, "1111111111");
    bin_case(0, "0");
    q_end();

    q_begin("题4");
    q_case_i("25", is_automorphic(25), 1);
    q_case_i("26", is_automorphic(26), 0);
    sweep("1~99 全部", is_automorphic, 1, 99, "1,5,6,25,76");
    q_end();

    q_begin("题5");
    q_case_i("n=1", count_one(1), 1);
    q_case_i("n=10", count_one(10), 2);
    q_case_i("n=11", count_one(11), 4);
    q_case_i("n=20", count_one(20), 12);
    q_case_i("n=100", count_one(100), 21);
    q_case_i("n=1000", count_one(1000), 301);
    q_end();

    return summary("环02");
}
