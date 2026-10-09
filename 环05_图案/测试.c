/*
 * 环05 测试：一次测完 5 题。你不用改这个文件。
 * 运行 ring05_test，把最后一行复制给 Claude（有错的题，再贴上那道题的函数）。
 * 出错时会告诉你第几行不一样：[ ] 里能看到行首、行尾的空格。
 */
#define CAPTURE_IMPL
#include "check.h"

void triangle(int n);
void shifted(int rows);
void diamond(int n);
void slanted(int rows);
void yanghui(int n);

int main(void)
{
    console_utf8();
    printf("环05 图案 测试\n\n");

    q_begin("题1");
    cap_reset(); triangle(5);  q_case_text("n=5", cap_buf, "*****\n****\n***\n**\n*\n");
    cap_reset(); triangle(1);  q_case_text("n=1", cap_buf, "*\n");
    q_end();

    q_begin("题2");
    cap_reset(); shifted(4);   q_case_text("4行", cap_buf, "*****\n *****\n  *****\n   *****\n");
    cap_reset(); shifted(1);   q_case_text("1行", cap_buf, "*****\n");
    q_end();

    q_begin("题3");
    cap_reset(); diamond(4);
    q_case_text("n=4", cap_buf, "   *\n  ***\n *****\n*******\n *****\n  ***\n   *\n");
    cap_reset(); diamond(1);   q_case_text("n=1", cap_buf, "*\n");
    cap_reset(); diamond(2);   q_case_text("n=2", cap_buf, " *\n***\n *\n");
    q_end();

    q_begin("题4");
    cap_reset(); slanted(5);
    q_case_text("5行", cap_buf,
        "* * * * *\n  * * * * *\n    * * * * *\n      * * * * *\n        * * * * *\n");
    cap_reset(); slanted(2);   q_case_text("2行", cap_buf, "* * * * *\n  * * * * *\n");
    q_end();

    q_begin("题5");
    cap_reset(); yanghui(1);   q_case_text("n=1", cap_buf, "1\n");
    cap_reset(); yanghui(4);   q_case_text("n=4", cap_buf, "1\n1 1\n1 2 1\n1 3 3 1\n");
    cap_reset(); yanghui(10);
    q_case_text("n=10", cap_buf,
        "1\n1 1\n1 2 1\n1 3 3 1\n1 4 6 4 1\n1 5 10 10 5 1\n1 6 15 20 15 6 1\n"
        "1 7 21 35 35 21 7 1\n1 8 28 56 70 56 28 8 1\n1 9 36 84 126 126 84 36 9 1\n");
    q_end();

    return summary("环05");
}
