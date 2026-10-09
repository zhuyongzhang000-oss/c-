/*
 * 环10 测试：一次测完 5 题。你不用改这个文件。
 * 运行 ring10_test，把最后一行复制给 Claude（有错的题，再贴上那道题的函数）。
 * 递归写错（没有基例）程序会卡住不动或直接退出——看停在哪一题。
 */
#define CAPTURE_IMPL
#include "check.h"

int peach(int day);
void convert(int n);
int fun(int n);
double legendre(int n, double x);
void latin(int n);

/* 只看最后一行 */
static const char *last_line(const char *s)
{
    const char *end = s + strlen(s), *p;
    if (end > s && end[-1] == '\n') end--;
    for (p = end; p > s && p[-1] != '\n'; p--) ;
    return p;
}

int main(void)
{
    console_utf8();
    printf("环10 递归 测试\n\n");

    q_begin("题1");
    q_case_i("第10天", peach(10), 1);
    q_case_i("第9天", peach(9), 4);
    q_case_i("第8天", peach(8), 10);
    q_case_i("第1天", peach(1), 1534);
    q_end();

    q_begin("题2");
    cap_reset(); convert(483);    q_case_text("483", cap_buf, "483");
    cap_reset(); convert(7);      q_case_text("7", cap_buf, "7");
    cap_reset(); convert(1000);   q_case_text("1000", cap_buf, "1000");
    cap_reset(); convert(0);      q_case_text("0", cap_buf, "0");
    cap_reset(); convert(-205);   q_case_text("-205", cap_buf, "-205");
    q_end();

    q_begin("题3");
    q_case_i("n=1", fun(1), 10);
    q_case_i("n=3", fun(3), 14);
    q_case_i("n=5", fun(5), 18);
    q_end();

    q_begin("题4");
    q_case_d("P0(0.3)", legendre(0, 0.3), 1.0, 1e-9);
    q_case_d("P1(0.3)", legendre(1, 0.3), 0.3, 1e-9);
    q_case_d("P2(0.5)", legendre(2, 0.5), -0.125, 1e-9);
    q_case_d("P3(0.5)", legendre(3, 0.5), -0.4375, 1e-9);
    q_case_d("P2(2)", legendre(2, 2.0), 5.5, 1e-9);
    q_case_d("P4(1)", legendre(4, 1.0), 1.0, 1e-9);
    q_end();

    q_begin("题5");
    cap_reset(); latin(1);  q_case_text("n=1", cap_buf, "1\n\n共 1 个\n");
    cap_reset(); latin(2);  q_case_text("n=2", cap_buf, "1 2\n2 1\n\n2 1\n1 2\n\n共 2 个\n");
    cap_reset(); latin(3);
    q_case_text("n=3", cap_buf,
        "1 2 3\n2 3 1\n3 1 2\n\n1 2 3\n3 1 2\n2 3 1\n\n1 3 2\n2 1 3\n3 2 1\n\n1 3 2\n3 2 1\n2 1 3\n\n"
        "2 1 3\n1 3 2\n3 2 1\n\n2 1 3\n3 2 1\n1 3 2\n\n2 3 1\n1 2 3\n3 1 2\n\n2 3 1\n3 1 2\n1 2 3\n\n"
        "3 1 2\n1 2 3\n2 3 1\n\n3 1 2\n2 3 1\n1 2 3\n\n3 2 1\n1 3 2\n2 1 3\n\n3 2 1\n2 1 3\n1 3 2\n\n"
        "共 12 个\n");
    cap_reset(); latin(4);
    q_case_text("n=4 最后一行", cap_buf[0] ? last_line(cap_buf) : "", "共 576 个\n");
    q_end();

    return summary("环10");
}
