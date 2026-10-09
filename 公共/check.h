/* 测试用的小工具。你不用改这个文件。 */
#ifndef CHECK_H
#define CHECK_H

#include <math.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

/* 题目文件里 return -12345; 是"未做"标记，测试会显示「未做」而不是「错」 */
#define NOT_DONE (-12345)

static int  g_pass, g_fail, g_todo;     /* 本环统计 */
static int  q_fail, q_todo, q_total;    /* 当前这一题 */
static char q_name[40];                 /* 当前题名 */
static char q_first[200];               /* 当前题第一处错误 */
static char g_report[1500];             /* 一行汇报 */

static inline void console_utf8(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);        /* 让 Windows 控制台正常显示中文 */
#endif
}

/* 先打印题名再开始测：如果程序停在这一行不动（死循环）或直接退出（崩溃），就是这道题的问题 */
static inline void q_begin(const char *name) {
    q_fail = q_todo = q_total = 0;
    q_first[0] = 0;
    snprintf(q_name, sizeof q_name, "%s", name);
    printf("  %s  ", name);
    fflush(stdout);
}

static inline void q_case_i(const char *input, long long actual, long long expected) {
    q_total++;
    if (actual == NOT_DONE) { q_todo++; return; }
    if (actual != expected && q_fail++ == 0)
        snprintf(q_first, sizeof q_first, "%s 期望 %lld 实际 %lld", input, expected, actual);
}

static inline void q_case_d(const char *input, double actual, double expected, double tol) {
    q_total++;
    if (actual == NOT_DONE) { q_todo++; return; }
    if (!(fabs(actual - expected) <= tol * (1.0 + fabs(expected))) && q_fail++ == 0)
        snprintf(q_first, sizeof q_first, "%s 期望 %.10g 实际 %.10g", input, expected, actual);
}

/* 字符串题：测试先把结果数组填满 X，函数没动它就算「未做」 */
static inline void q_case_s(const char *input, const char *actual, const char *expected) {
    q_total++;
    if (actual[0] == 'X' && strspn(actual, "X") >= 30) { q_todo++; return; }
    if (strcmp(actual, expected) != 0 && q_fail++ == 0)
        snprintf(q_first, sizeof q_first, "%s 期望 \"%s\" 实际 \"%.60s\"%s", input, expected, actual,
                 strchr(actual, 'X') && !strchr(expected, 'X') ? " 后面的X说明没补'\\0'" : "");
}

/* 比较多行文本（打印类题目）：找出第一处不同的行。空输出算「未做」。 */
static inline void q_case_text(const char *input, const char *actual, const char *expected) {
    int line = 1;
    const char *a = actual, *e = expected;
    q_total++;
    if (actual[0] == '\0') { q_todo++; return; }
    if (strcmp(actual, expected) == 0) return;
    while (*a && *e && *a == *e) {             /* 跳到第一处不同所在的行首 */
        if (*a == '\n') line++;
        a++; e++;
    }
    while (a > actual && a[-1] != '\n') { a--; e--; }
    if (q_fail++ == 0) {
        char la[60], le[60];
        int i;
        for (i = 0; a[i] && a[i] != '\n' && i < 59; i++) la[i] = a[i];
        la[i] = '\0';
        for (i = 0; e[i] && e[i] != '\n' && i < 59; i++) le[i] = e[i];
        le[i] = '\0';
        snprintf(q_first, sizeof q_first, "%s 第%d行 期望[%s] 实际[%s]%s", input, line, le, la,
                 (!*e && *a) ? " 多打了内容" : (!*a && *e) ? " 少打了内容" : "");
    }
}

/* 打印类题目的捕获：测试.c 在 #include "check.h" 之前写 #define CAPTURE_IMPL */
#ifdef CAPTURE_IMPL
#include <stdarg.h>
static char cap_buf[40000];
static void cap_reset(void) { cap_buf[0] = '\0'; }
int cap_printf(const char *fmt, ...) {
    size_t n = strlen(cap_buf);
    int r;
    va_list ap;
    va_start(ap, fmt);
    r = vsnprintf(cap_buf + n, sizeof cap_buf - n, fmt, ap);
    va_end(ap);
    return r;
}
int cap_putchar(int c) {
    size_t n = strlen(cap_buf);
    if (n + 1 < sizeof cap_buf) { cap_buf[n] = (char)c; cap_buf[n + 1] = '\0'; }
    return c;
}
int cap_puts(const char *s) { cap_printf("%s\n", s); return 0; }
#endif

static inline void q_end(void) {
    char part[260];
    const char *sep = g_report[0] ? " " : "";
    if (q_todo == q_total) {
        g_todo++;
        printf("未做\n");
        snprintf(part, sizeof part, "%s%s未做", sep, q_name);
    } else if (q_fail == 0 && q_todo == 0) {
        g_pass++;
        printf("通过 (%d/%d)\n", q_total, q_total);
        snprintf(part, sizeof part, "%s%s对", sep, q_name);
    } else {
        g_fail++;
        printf("错   %s\n", q_fail ? q_first : "有的用例没有输出或返回了未做标记");
        snprintf(part, sizeof part, "%s%s错(%s)", sep, q_name, q_fail ? q_first : "有用例没输出");
    }
    strncat(g_report, part, sizeof g_report - strlen(g_report) - 1);
}

static inline int summary(const char *ring) {
    printf("\n通过 %d ／ 错 %d ／ 未做 %d\n", g_pass, g_fail, g_todo);
    printf("\n把下面这一行复制给 Claude（有错的题，再贴上那道题的函数）：\n%s 测试：%s\n", ring, g_report);
    return 0;
}

#endif
