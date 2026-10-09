/* 题5 答案。卡点：pre 跟着 p；删头结点要改 head；free 被删的结点。 */
#include <stdlib.h>
#include "stu.h"

struct Node *del(struct Node *head, int num)
{
    struct Node *p = head, *pre = NULL;
    while (p != NULL && p->num != num) { pre = p; p = p->next; }
    if (p == NULL) return head;            /* 没找到 */
    if (pre == NULL) head = p->next;       /* 删的是第一个 */
    else pre->next = p->next;
    free(p);
    return head;
}
