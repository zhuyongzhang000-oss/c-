/* 细节自测用的小工具。你不用改这个文件。
 *
 * 自测.c 里有两种题：
 *   一、猜输出  { 代码…  OUT("%d", x); }   GUESS(1, "你猜的输出");
 *   二、判断    JUDGE(1, 'Y');   Y = 合法/对，N = 不合法/错，空格 ' ' = 还没做
 * 写代码的题在 题1~题5 里（启动项 ringNN_test）。
 */
#ifndef DETAIL_H
#define DETAIL_H

#include <stdarg.h>
#include "check.h"

/* 判断题答案在 答案/判断答案.c 里（和自测一起编译） */
extern const char judge_key[];
extern const char *const judge_why[];

static char d_out[512];                 /* OUT 写到这里，GUESS 拿它和你猜的比 */
static int  d_guess_ok, d_guess_n, d_judge_ok, d_judge_n;
static char d_wrong[600];               /* 错题编号，最后汇总 */
static int  d_todo;                     /* 没做的题数 */

/* 用法和 printf 一样，只是不打印，先存起来等 GUESS 比较 */
static inline void OUT(const char *fmt, ...) {
    size_t n = strlen(d_out);
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(d_out + n, sizeof d_out - n, fmt, ap);
    va_end(ap);
}

static inline void d_mark(const char *tag, int no) {
    char t[16];
    snprintf(t, sizeof t, "%s%s%d", d_wrong[0] ? " " : "", tag, no);
    strncat(d_wrong, t, sizeof d_wrong - strlen(d_wrong) - 1);
}

/* 换行在屏幕上显示成 \n，空格看得见边界：[ 3.14] */
static inline void d_show(const char *s) {
    putchar('[');
    for (; *s; s++) {
        if (*s == '\n') printf("\\n");
        else putchar(*s);
    }
    putchar(']');
}

static inline void d_section(const char *title) {
    printf("\n%s\n", title);
}

static inline void GUESS(int no, const char *guess) {
    d_guess_n++;
    printf("  猜%-2d ", no);
#ifdef D_REVEAL
    printf("<%s> ", d_out);             /* 出题人自查用，平时不会编译进来 */
#endif
    if (guess[0] == '\0') {
        printf("未做\n");                 /* 没填就不揭晓，免得看到答案 */
        d_todo++;
    } else if (strcmp(guess, d_out) == 0) {
        d_guess_ok++;
        printf("对\n");
    } else {
        printf("错   你写 ");
        d_show(guess);
        printf("  实际 ");
        d_show(d_out);
        printf("\n");
        d_mark("猜", no);
    }
    d_out[0] = '\0';
}

static inline void JUDGE(int no, char ans) {
    char key = judge_key[no - 1];
    d_judge_n++;
    printf("  判%-2d ", no);
    if (ans != 'Y' && ans != 'N' && ans != 'y' && ans != 'n') {
        printf("未做\n");
        d_todo++;
    } else if ((ans == 'Y' || ans == 'y') == (key == 'Y')) {
        d_judge_ok++;
        printf("对\n");
    } else {
        printf("错   应为 %c：%s\n", key, judge_why[no - 1]);
        d_mark("判", no);
    }
}

static inline int d_summary(const char *ring) {
    printf("\n猜输出 对 %d/%d ／ 判断 对 %d/%d", d_guess_ok, d_guess_n, d_judge_ok, d_judge_n);
    if (d_todo) printf(" ／ 还有 %d 题没做", d_todo);
    printf("\n\n%s 自测：猜 %d/%d 判 %d/%d%s%s%s\n", ring,
           d_guess_ok, d_guess_n, d_judge_ok, d_judge_n,
           d_wrong[0] ? " ｜ 错：" : "", d_wrong,
           d_todo ? " ｜ 有未做" : (d_wrong[0] ? "" : " ｜ 全对"));
    return 0;
}

#endif
