/*
 * 环11 测试：一次测完 5 题。你不用改这个文件。
 * 运行 ring11_test，把最后一行复制给 Claude（有错的题，再贴上那道题的函数）。
 */
#include "check.h"

void copy_from_k(char *src, char *dest, int k);
int my_strcmp(char *p1, char *p2);
void reverse(int *a, int n);
int find_len_word(char *s1, char *s2);
void move(int *a, int n, int m);

static void join(int a[], int n, char *out, size_t size)
{
    char num[16];
    int i;
    out[0] = '\0';
    for (i = 0; i < n; i++) {
        snprintf(num, sizeof num, "%s%d", i ? " " : "", a[i]);
        strncat(out, num, size - strlen(out) - 1);
    }
}

/* dest 先填满 X：没补 '\0'、或者非法 k 时没清空，都能看出来 */
static void copy_case(const char *src, int k, const char *expected)
{
    char s[40], d[40], label[60];
    memset(d, 'X', sizeof d - 1);
    d[sizeof d - 1] = '\0';
    snprintf(s, sizeof s, "%s", src);
    snprintf(label, sizeof label, "\"%s\" k=%d", src, k);
    copy_from_k(s, d, k);
    q_case_s(label, d, expected);
}

static void cmp_case(const char *a, const char *b, int expected)
{
    char x[20], y[20], label[40];
    snprintf(x, sizeof x, "%s", a);
    snprintf(y, sizeof y, "%s", b);
    snprintf(label, sizeof label, "\"%s\"和\"%s\"", a, b);
    q_case_i(label, my_strcmp(x, y), expected);
}

static void find_case(const char *s1, const char *s2, int expected)
{
    char a[60], b[20], label[80];
    snprintf(a, sizeof a, "%s", s1);
    snprintf(b, sizeof b, "%s", s2);
    snprintf(label, sizeof label, "\"%s\" 比\"%s\"长", s1, s2);
    q_case_i(label, find_len_word(a, b), expected);
}

int main(void)
{
    char got[200];
    console_utf8();
    printf("环11 指针处理数组与字符串 测试\n\n");

    q_begin("题1");
    copy_case("computer", 4, "puter");
    copy_case("computer", 1, "computer");
    copy_case("computer", 8, "r");
    copy_case("computer", 9, "");
    copy_case("computer", 0, "");
    q_end();

    q_begin("题2");
    cmp_case("BOY", "BAD", 14); cmp_case("BAD", "BOY", -14); cmp_case("abc", "abc", 0);
    cmp_case("ab", "abc", -99); cmp_case("", "a", -97);
    q_end();

    q_begin("题3");
    {
        int a[5] = {1, 2, 3, 4, 5}, b[4] = {7, 8, 9, 10}, c[1] = {6}, d[2] = {1, 2};
        reverse(a, 5);
        if (a[0] == 1 && a[4] == 5) q_case_i("1 2 3 4 5", NOT_DONE, 0);
        else {
            join(a, 5, got, sizeof got);  q_case_s("奇数个", got, "5 4 3 2 1");
            reverse(b, 4);  join(b, 4, got, sizeof got);  q_case_s("偶数个", got, "10 9 8 7");
            reverse(c, 1);  join(c, 1, got, sizeof got);  q_case_s("一个", got, "6");
            reverse(d, 0);  join(d, 2, got, sizeof got);  q_case_s("n=0 不动", got, "1 2");
        }
    }
    q_end();

    q_begin("题4");
    find_case("I am a student", "abc", 7);
    find_case("I am a student", "student", -1);
    find_case("   hello  world", "abcd", 3);
    find_case("hi  there ", "hi", 4);
    find_case("", "a", -1);
    find_case("abc", "ab", 0);
    q_end();

    q_begin("题5");
    {
        int a[5] = {1, 2, 3, 4, 5}, b[5] = {1, 2, 3, 4, 5}, c[5] = {1, 2, 3, 4, 5}, d[6] = {1, 2, 3, 4, 5, 6};
        move(a, 5, 2);
        if (a[0] == 1 && a[1] == 2) q_case_i("移 2 位", NOT_DONE, 0);
        else {
            join(a, 5, got, sizeof got);  q_case_s("移 2 位", got, "4 5 1 2 3");
            move(b, 5, 0);  join(b, 5, got, sizeof got);  q_case_s("移 0 位", got, "1 2 3 4 5");
            move(c, 5, 7);  join(c, 5, got, sizeof got);  q_case_s("移 7 位（=2 位）", got, "4 5 1 2 3");
            move(d, 6, 5);  join(d, 6, got, sizeof got);  q_case_s("6 个移 5 位", got, "2 3 4 5 6 1");
        }
    }
    q_end();

    return summary("环11");
}
