/*
 * ══════════════════════════════════════════════════════════════════
 *  环13 自测：猜输出 + 判断对错（运行 ring13_quiz 自动判分）
 * ══════════════════════════════════════════════════════════════════
 *  做法同前：一、把 OUT 会输出的内容写进 GUESS 的引号（空格要准，"" 算未做）；
 *            二、' ' 改成 'Y'（合法/对）或 'N'（不合法/错）。
 *  题目会读写一个临时文件 ring13_quiz.tmp，最后会删掉。
 */
#include "detail.h"

#define TMP "ring13_quiz.tmp"

static void put(const char *mode, const char *text)
{
    FILE *fp = fopen(TMP, mode);
    if (fp) { fputs(text, fp); fclose(fp); }
}

int main(void)
{
    FILE *fp;
    int ch, n;
    console_utf8();
    printf("环13 自测\n");

    d_section("一、猜输出");

    { OUT("%d", EOF); }
    GUESS(1, "");                                   /* → 细6 */

    { put("w", "abc");  n = 0;  fp = fopen(TMP, "r");
      if (fp) { while ((ch = fgetc(fp)) != EOF) n++; fclose(fp); }
      OUT("%d", n); }
    GUESS(2, "");                                   /* → ③ */

    { char line[4];  put("w", "hello\n");  fp = fopen(TMP, "r");
      if (fp) { fgets(line, sizeof line, fp); fclose(fp); OUT("[%s]", line); } }
    GUESS(3, "");                                   /* fgets 最多读 大小-1 个字符 → ④ */

    { int a = 0, b = 0, r = -9;  put("w", "12 ab");  fp = fopen(TMP, "r");
      if (fp) { r = fscanf(fp, "%d %d", &a, &b); fclose(fp); }
      OUT("%d %d", r, a); }
    GUESS(4, "");                                   /* fscanf 的返回值 → ⑤ */

    { put("w", "xyz");  n = 0;  fp = fopen(TMP, "r");
      if (fp) { while (!feof(fp)) { ch = fgetc(fp); n++; } fclose(fp); }
      OUT("%d", n); }
    GUESS(5, "");                                   /* → ⑦ */

    { char buf[20] = "";  put("w", "ab");  put("a", "cd");  put("a", "ef");
      fp = fopen(TMP, "r");  if (fp) { fgets(buf, sizeof buf, fp); fclose(fp); }
      OUT("%s", buf); }
    GUESS(6, "");                                   /* → ② */

    { char buf[20] = "";  put("w", "ab");  put("a", "cd");  put("w", "ef");
      fp = fopen(TMP, "r");  if (fp) { fgets(buf, sizeof buf, fp); fclose(fp); }
      OUT("%s", buf); }
    GUESS(7, "");                                   /* → 细3 */

    { long pos = -1;  put("w", "hello");  fp = fopen(TMP, "r");
      if (fp) { fseek(fp, 2, SEEK_SET); ch = fgetc(fp); pos = ftell(fp); fclose(fp); }
      OUT("%c %ld", ch, pos); }
    GUESS(8, "");                                   /* → ⑧ */

    { int x = 42, in[3] = {0};  size_t got = 0;  fp = fopen(TMP, "wb");
      if (fp) { fwrite(&x, sizeof(int), 1, fp); fclose(fp); }
      fp = fopen(TMP, "rb");  if (fp) { got = fread(in, sizeof(int), 3, fp); fclose(fp); }
      OUT("%d %d", (int)got, in[0]); }
    GUESS(9, "");                                   /* fread 的返回值 → ⑥ */

    remove(TMP);


    d_section("二、判断（Y 合法/对，N 不合法/错）");

    JUDGE(1,  ' ');   /* 定义文件指针时可以写成小写 file *fp;                     [教材10.1] → 细1 */
    JUDGE(2,  ' ');   /* fopen 打开失败时返回 NULL                                [教材10.2] → ① */
    JUDGE(3,  ' ');   /* 用 "w" 打开一个已有的文件，原来的内容会被清空            [教材10.2] → 细3 */
    JUDGE(4,  ' ');   /* 用 "r" 打开一个不存在的文件，会自动新建这个文件          [教材10.2] → ② */
    JUDGE(5,  ' ');   /* 用 "a" 方式写入的数据加在文件末尾                        [教材10.2] → ② */
    JUDGE(6,  ' ');   /* 文件还没有结束时，feof 的返回值是 0                      [真选28·华南理工2018] → 细4 */
    JUDGE(7,  ' ');   /* 文件还没有结束时，feof 的返回值是 -1（EOF）              [真选28·华南理工2018] → 细4 */
    JUDGE(8,  ' ');   /* fgetc 读到文件末尾时返回 EOF                             [教材10.3] → ③ */
    JUDGE(9,  ' ');   /* 接收 fgetc 返回值的变量应该定义成 char                   [教材10.3] → 细6 */
    JUDGE(10, ' ');   /* char filename[] = "paper"; fopen(filename, "r") 打开的是叫 filename 的文件  [真选29·华南理工2018] → 细5 */
    JUDGE(11, ' ');   /* fgets 会把行末的换行符也读进数组                         [教材10.3] → ④ */
    JUDGE(12, ' ');   /* fread 的返回值是成功读到的块数                           [教材10.3] → ⑥ */
    JUDGE(13, ' ');   /* 用 while (!feof(fp)) { ch = fgetc(fp); … } 读文件不会多处理一次  [教材10.3] → ⑦ */
    JUDGE(14, ' ');   /* 文件用完以后可以不调用 fclose                            [教材10.2] → 细8 */
    JUDGE(15, ' ');   /* "rb+" 表示以二进制方式打开文件，可读可写                 [真选29·华南理工2018] → ② */
    JUDGE(16, ' ');   /* fprintf(stdout, "%d", x); 相当于 printf("%d", x);        [教材10.3] → 细7 */

    return d_summary("环13");
}
