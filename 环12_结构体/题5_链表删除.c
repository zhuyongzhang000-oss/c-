/*
 * 环12 题5【限时】教材第9章习题7
 * 原题：在第 9 章例 9.9 和例 9.10 的基础上，写一个函数 del，用来删除动态链表中指定的结点。
 *
 * 你要写：del(head, num) 删除链表里第一个 num 等于给定值的结点，返回删除后的链表头指针；
 *         没找到就原样返回。被删的结点用 free 释放（结点都是 malloc 来的）。
 * 思路：p 找结点，pre 跟在 p 后面；删的是第一个结点时头指针要变。
 * 限时 15 分钟。卡住先看：讲义 第⑧节
 */
#include <stdlib.h>
#include "stu.h"

struct Node *del(struct Node *head, int num)
{
    return (struct Node *)-1;    /* 未做标记：删掉这行，开始写 */
}
