/*
 * 环01 测试：一次测完 5 题。你不用改这个文件。
 * 运行 ring01_test，把最后一行复制给 Claude。
 */
#include "check.h"

/* 5 道题的函数，写在同一文件夹的 题1~题5 文件里 */
double e_series(int n);
long long repeat_sum(int a, int n);
double frac_sum(int n);
double cos_series(double x);
int day_of_year(int y, int m, int d);

int main(void)
{
    console_utf8();
    printf("环01 级数 测试\n\n");

    q_begin("题1");
    q_case_d("n=0", e_series(0), 1.0, 1e-9);
    q_case_d("n=1", e_series(1), 2.0, 1e-9);
    q_case_d("n=3", e_series(3), 2.6666666666666667, 1e-9);
    q_case_d("n=15", e_series(15), 2.718281828458995, 1e-9);
    q_case_d("n=20", e_series(20), 2.7182818284590455, 1e-9);
    q_end();

    q_begin("题2");
    q_case_i("a=3,n=1", repeat_sum(3, 1), 3);
    q_case_i("a=3,n=5", repeat_sum(3, 5), 37035);
    q_case_i("a=2,n=4", repeat_sum(2, 4), 2468);
    q_case_i("a=9,n=10", repeat_sum(9, 10), 11111111100LL);
    q_end();

    q_begin("题3");
    q_case_d("n=1", frac_sum(1), 2.0, 1e-9);
    q_case_d("n=2", frac_sum(2), 3.5, 1e-9);
    q_case_d("n=3", frac_sum(3), 5.1666666666666667, 1e-9);
    q_case_d("n=20", frac_sum(20), 32.66026079864164, 1e-9);
    q_end();

    q_begin("题4");
    q_case_d("x=0", cos_series(0), 1.0, 1e-5);
    q_case_d("x=0.5", cos_series(0.5), 0.8775825618903728, 1e-5);
    q_case_d("x=1", cos_series(1), 0.5403023058681398, 1e-5);
    q_case_d("x=-2", cos_series(-2), -0.4161468365471424, 1e-5);
    q_case_d("x=3.14159", cos_series(3.14159), -0.9999999999964793, 1e-5);
    q_end();

    q_begin("题5");
    q_case_i("2024-1-1", day_of_year(2024, 1, 1), 1);
    q_case_i("2024-3-1", day_of_year(2024, 3, 1), 61);
    q_case_i("2023-3-1", day_of_year(2023, 3, 1), 60);
    q_case_i("1900-3-1", day_of_year(1900, 3, 1), 60);
    q_case_i("2000-12-31", day_of_year(2000, 12, 31), 366);
    q_case_i("2024-2-29", day_of_year(2024, 2, 29), 60);
    q_end();

    return summary("环01");
}
