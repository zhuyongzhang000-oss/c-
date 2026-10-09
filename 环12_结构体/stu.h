/* 环12 题目用到的结构体类型。题文件和测试都包含这个头文件。你不用改它，但要读懂。 */
#ifndef STU_H
#define STU_H

struct Student {            /* 题1、题3 */
    int num;
    char name[20];
    double score[3];
};

struct Date {               /* 题2 */
    int year, month, day;
};

typedef struct {            /* 题4（原题的写法） */
    char num[10];
    int s;
} STREC;

struct Node {               /* 题5 */
    int num;
    struct Node *next;
};

#endif
