/*
 * 环13 测试：一次测完 5 题。你不用改这个文件。
 * 运行 ring13_test，把最后一行复制给 Claude（有错的题，再贴上那道题的函数）。
 * 测试会在程序目录里建几个 ring13_*.txt 临时文件，测完删掉。
 */
#include <stdlib.h>
#define CAPTURE_IMPL
#include "check.h"
#include "stud.h"

void save_upper(FILE *in, const char *filename);
void save_lines(FILE *in, const char *filename);
void show_upper(const char *filename);
void save_students(struct Stud s[], int n, const char *filename);
void merge_files(const char *fa, const char *fb, const char *fc);
void sort_file(const char *in, const char *out);

static void write_file(const char *name, const char *text)
{
    FILE *fp = fopen(name, "w");
    if (fp) { fputs(text, fp); fclose(fp); }
}

/* 把文件全部读进 buf；文件不存在就是空串 */
static void read_file(const char *name, char *buf, size_t size)
{
    FILE *fp = fopen(name, "r");
    size_t n = 0;
    int ch;
    buf[0] = '\0';
    if (fp == NULL) return;
    while (n + 1 < size && (ch = fgetc(fp)) != EOF) buf[n++] = (char)ch;
    buf[n] = '\0';
    fclose(fp);
}

#define IN  "ring13_in.txt"
#define OUT "ring13_out.txt"
#define FA  "ring13_A.txt"
#define FB  "ring13_B.txt"
#define FC  "ring13_C.txt"

int main(void)
{
    char got[2000];
    FILE *in;
    console_utf8();
    printf("环13 文件 测试\n\n");

    q_begin("题1");
    remove(OUT);
    write_file(IN, "Hello, World 2!abc");
    in = fopen(IN, "r");
    if (in) { save_upper(in, OUT); fclose(in); }
    read_file(OUT, got, sizeof got);
    q_case_text("Hello, World 2!abc", got, "HELLO, WORLD 2");
    remove(OUT);
    write_file(IN, "no bang at all");
    in = fopen(IN, "r");
    if (in && got[0]) { save_upper(in, OUT); fclose(in); read_file(OUT, got, sizeof got);
                        q_case_text("没有 !（读到文件尾）", got, "NO BANG AT ALL"); }
    else if (in) fclose(in);
    q_end();

    q_begin("题2");
    remove(OUT);
    write_file(IN, "first Line\nsecond\nx y z\n");
    in = fopen(IN, "r");
    if (in) { save_lines(in, OUT); fclose(in); }
    read_file(OUT, got, sizeof got);
    q_case_text("save_lines 写进的文件", got, "first Line\nsecond\nx y z\n");
    if (got[0]) {
        cap_reset(); show_upper(OUT);
        q_case_text("show_upper 屏幕输出", cap_buf, "FIRST LINE\nSECOND\nX Y Z\n");
    }
    q_end();

    q_begin("题3");
    {
        struct Stud s[2] = {{101, "Li", {80, 90, 70}, 0}, {102, "Wang", {95, 85.5, 90}, 0}};
        remove(OUT);
        save_students(s, 2, OUT);
        read_file(OUT, got, sizeof got);
        q_case_text("文件内容", got, "101 Li 80.0 90.0 70.0 80.00\n102 Wang 95.0 85.5 90.0 90.17\n");
        if (got[0]) q_case_d("s[1].avg 也算好了", s[1].avg, 90.1666666667, 1e-6);
    }
    q_end();

    q_begin("题4");
    remove(FC);
    write_file(FA, "dbca\n");
    write_file(FB, "zay\n");
    merge_files(FA, FB, FC);
    read_file(FC, got, sizeof got);
    q_case_text("dbca + zay", got, "aabcdyz\n");
    if (got[0]) {
        remove(FC);
        write_file(FA, "q");
        write_file(FB, "\n");
        merge_files(FA, FB, FC);
        read_file(FC, got, sizeof got);
        q_case_text("q + 空行", got, "q\n");
    }
    q_end();

    q_begin("题5");
    remove(OUT);
    write_file(IN, "101 Li 80.0 90.0 70.0 80.00\n102 Wang 95.0 85.5 90.0 90.17\n103 Zhao 60.0 70.0 80.0 70.00\n");
    sort_file(IN, OUT);
    read_file(OUT, got, sizeof got);
    q_case_text("按平均分排序", got,
        "102 Wang 95.0 85.5 90.0 90.17\n101 Li 80.0 90.0 70.0 80.00\n103 Zhao 60.0 70.0 80.0 70.00\n");
    q_end();

    remove(IN); remove(OUT); remove(FA); remove(FB); remove(FC);
    return summary("环13");
}
