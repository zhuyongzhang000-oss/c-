/*
 * 环03 测试：一次测完 5 题。你不用改这个文件。
 * 运行 ring03_test，把最后一行复制给 Claude（有错的题，再贴上那道题的函数）。
 */
#define CAPTURE_IMPL
#include "check.h"

int is_prime(int n);
int gcd(int m, int n);
int lcm(int m, int n);
void print_perfect(int limit);
int sieve(int n, int primes[]);
void print_primes(int a, int b);

static void prime_case(int n, int expected)
{
    char label[20];
    snprintf(label, sizeof label, "n=%d", n);
    q_case_i(label, is_prime(n), expected);
}

static void gl_case(int m, int n, int g, int l)
{
    char label[40];
    snprintf(label, sizeof label, "gcd(%d,%d)", m, n);
    q_case_i(label, gcd(m, n), g);
    snprintf(label, sizeof label, "lcm(%d,%d)", m, n);
    q_case_i(label, lcm(m, n), l);
}

static void sieve_case(int n, const char *expected)
{
    int primes[400], cnt, i;
    char buf[1200] = "", num[12], label[20];
    snprintf(label, sizeof label, "n=%d", n);
    cnt = sieve(n, primes);
    if (cnt == NOT_DONE) { q_case_i(label, NOT_DONE, 0); return; }
    if (cnt < 0 || cnt > 400) { q_case_i(label, cnt, -1); return; }
    for (i = 0; i < cnt; i++) {
        snprintf(num, sizeof num, "%s%d", i ? " " : "", primes[i]);
        strncat(buf, num, sizeof buf - strlen(buf) - 1);
    }
    q_case_s(label, buf, expected);
}

int main(void)
{
    console_utf8();
    printf("环03 素数与因子 测试\n\n");

    q_begin("题1");
    prime_case(2, 1);  prime_case(1, 0);  prime_case(0, 0);  prime_case(9, 0);
    prime_case(97, 1); prime_case(121, 0); prime_case(169, 0); prime_case(997, 1);
    if (is_prime(2) != NOT_DONE) {
        int s = 0, i;
        for (i = 2; i < 1000; i++) if (is_prime(i)) s += i;
        q_case_i("1000以内素数和", s, 76127);
    }
    q_end();

    q_begin("题2");
    gl_case(12, 18, 6, 36);
    gl_case(18, 12, 6, 36);
    gl_case(7, 5, 1, 35);
    gl_case(24, 6, 6, 24);
    gl_case(1, 1, 1, 1);
    gl_case(60000, 70000, 10000, 420000);
    q_end();

    q_begin("题3");
    cap_reset(); print_perfect(30);
    q_case_text("limit=30", cap_buf, "6 its factors are 1,2,3\n28 its factors are 1,2,4,7,14\n");
    cap_reset(); print_perfect(1000);
    q_case_text("limit=1000", cap_buf,
        "6 its factors are 1,2,3\n28 its factors are 1,2,4,7,14\n"
        "496 its factors are 1,2,4,8,16,31,62,124,248\n");
    q_end();

    q_begin("题4");
    sieve_case(2, "2");
    sieve_case(30, "2 3 5 7 11 13 17 19 23 29");
    sieve_case(100, "2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97");
    sieve_case(1, "");
    q_end();

    q_begin("题5");
    cap_reset(); print_primes(2, 10);
    q_case_text("2~10", cap_buf, "2 3 5 7\n");
    cap_reset(); print_primes(1, 3);
    q_case_text("1~3", cap_buf, "2 3\n");
    cap_reset(); print_primes(110, 130);
    q_case_text("110~130", cap_buf, "113 127\n");
    cap_reset(); print_primes(100, 200);
    q_case_text("100~200", cap_buf,
        "101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199\n");
    q_end();

    return summary("环03");
}
