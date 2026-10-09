/*
 * 环08 测试：一次测完 5 题。你不用改这个文件。
 * 运行 ring08_test，把最后一行复制给 Claude（有错的题，再贴上那道题的函数）。
 */
#define CAPTURE_IMPL
#include "check.h"

void print_reverse(char s[]);
int is_palindrome(char s[]);
int str_to_int(char s[]);
void my_strcat(char dest[], char src[]);
int my_strcmp(char s1[], char s2[]);

static void pal_case(const char *s, int expected)
{
    char buf[40], label[50];
    snprintf(buf, sizeof buf, "%s", s);
    snprintf(label, sizeof label, "\"%s\"", s);
    q_case_i(label, is_palindrome(buf), expected);
}

static void sti_case(const char *s, int expected)
{
    char buf[20], label[30];
    snprintf(buf, sizeof buf, "%s", s);
    snprintf(label, sizeof label, "\"%s\"", s);
    q_case_i(label, str_to_int(buf), expected);
}

/* dest 后面先填满 X：没补 '\0' 就会看到 X */
static int cat_case(const char *d, const char *s, const char *expected)
{
    char dest[40], src[20], label[60];
    memset(dest, 'X', sizeof dest - 1);
    dest[sizeof dest - 1] = '\0';
    memcpy(dest, d, strlen(d) + 1);
    snprintf(src, sizeof src, "%s", s);
    snprintf(label, sizeof label, "\"%s\"+\"%s\"", d, s);
    my_strcat(dest, src);
    if (strcmp(dest, d) == 0 && s[0] != '\0') { q_case_i(label, NOT_DONE, 0); return 0; }
    q_case_s(label, dest, expected);
    return 1;
}

static void cmp_case(const char *a, const char *b, int expected)
{
    char x[20], y[20], label[40];
    snprintf(x, sizeof x, "%s", a);
    snprintf(y, sizeof y, "%s", b);
    snprintf(label, sizeof label, "\"%s\"和\"%s\"", a, b);
    q_case_i(label, my_strcmp(x, y), expected);
}

int main(void)
{
    char s[40];
    console_utf8();
    printf("环08 字符串 测试\n\n");

    q_begin("题1");
    strcpy(s, "abcde");  cap_reset(); print_reverse(s);  q_case_text("abcde", cap_buf, "edcba\n");
    strcpy(s, "a b");    cap_reset(); print_reverse(s);  q_case_text("a b", cap_buf, "b a\n");
    strcpy(s, "x");      cap_reset(); print_reverse(s);  q_case_text("x", cap_buf, "x\n");
    q_end();

    q_begin("题2");
    pal_case("level", 1); pal_case("abba", 1); pal_case("a", 1); pal_case("", 1);
    pal_case("ab", 0); pal_case("abca", 0); pal_case("abcda", 0);
    q_end();

    q_begin("题3");
    sti_case("123456", 123456); sti_case("0", 0); sti_case("007", 7); sti_case("9", 9);
    sti_case("100", 100); sti_case("987654321", 987654321);
    q_end();

    q_begin("题4");
    if (cat_case("code", "block", "codeblock")) {      /* 第一组没动过就算未做，后面不测 */
        cat_case("", "abc", "abc");
        cat_case("abc", "", "abc");
        cat_case("a b", " c", "a b c");
    }
    q_end();

    q_begin("题5");
    cmp_case("A", "C", -2); cmp_case("And", "Aid", 5); cmp_case("abc", "abc", 0);
    cmp_case("ab", "abc", -99); cmp_case("abc", "ab", 99); cmp_case("", "", 0); cmp_case("b", "a", 1);
    q_end();

    return summary("环08");
}
