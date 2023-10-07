#include <stdio.h>
#include <stdlib.h>
#include "list.h"


void ListInit(List *plist)
{
    /*
        新建一个空链表
        示例:
        List newlist;
        ListInit(&newlist);
    */
    plist->head = NULL;
    plist->length = 0;
}

void ListInsertTail(List *plist, ElemType e)
{
    /*
        在链表尾部插入一个新元素
        示例:
        ListInsertTail(&list,e)
    */

    // 如果是空链表
    if (ListIsEmpty(plist))
    {
        plist->head = (ListNode *)malloc(sizeof(ListNode));
        if (plist->head == NULL) // 内存分配检查
            exit(-1);
        plist->head->element = e;
        plist->head->pnext = NULL;
        plist->length++;
        return;
    }
    // 如果不是空链表
    ListNode *plistNode = plist->head;
    int i;
    for (i = 0; i < (ListGetLength(plist) - 1); i++)
    {
        plistNode = plistNode->pnext; // 得到原本的最后一个节点指针
    }
    plistNode->pnext = (ListNode *)malloc(sizeof(ListNode));
    if (plist->head == NULL) // 内存分配检查
        exit(-1);
    plistNode->pnext->element = e;
    plistNode->pnext->pnext = NULL;
    plist->length++;
    return;
}

void ListPrint(List *plist)
{
    /*
        打印所有节点的元素（以int形式）
        示例:
        ListPrint(&list);
    */
    if (ListIsEmpty(plist))
        return;
    ListNode *plistnode = plist->head;
    while (plistnode != NULL)
    {
        printf("%d\n", (int)plistnode->element);
    }
    return;
}

void ListClear(List *plist)
{
    /*
        清空链表，使之成为长度为0的空链表
        示例:
        ListClear(&list);
    */
    if (ListIsEmpty(plist))
        return;
    ListNode *plistnode_1 = NULL;
    ListNode *plistnode_2 = NULL; // plistnode_2用于临时存放需要free掉的节点
    plistnode_1 = plist->head;
    while (plistnode_1 != NULL) // 每个循环删除当前plistnode_1指向的节点，并使之指向下一个节点
    {
        plistnode_2 = plistnode_1;
        plistnode_1 = plistnode_1->pnext;
        free(plistnode_2);
    }
    plist->head = NULL;
    plist->length = 0;
    return;
}
void ListGetElem(List *plist, int n, ElemType *pelem)
{
    /*
        获得链表的第n个节点的元素(n从1开始),并将元素通过指针返回
        示例:
        ListGetElem(&list,n,&elem);
    */
    if (ListGetLength(plist) < n) // 检查是否越界
        exit(-1);
    ListNode *plistnode = plist->head;
    int i;
    for (i = 0; i < n - 1; i++)
    {
        plistnode = plistnode->pnext;
    }
    *pelem = plistnode->element;
    return;
}
void ListLocateElem(List *plist, ElemType elem, ListNode **pplistnode)
{
    /*
        定位链表的第一个元素为elem的节点,并将节点指针通过指针返回，如果没找到则返回null
        注意,pplistnode是目标节点的指针的指针,最终调用函数得到的是一个指向目标节点的指针
        示例:
        ListLocateElem(&list,elem,&plistnode);
    */
    ListNode *pnode = plist->head;
    while (pnode != NULL) // 遍历查找
    {
        if (pnode->element == elem)
        {
            *pplistnode = pnode;
            return;
        }
    }
    *pplistnode = NULL; // 未能查找到符合条件的节点
    return;
}
void ListLocatePriorNode(List *plist, ListNode *plistnode, ListNode **pplistnode)
{
    /*
        定位前一个节点,并将节点指针通过指针返回，如果没找到则返回null(已经是第一个节点，或者传入节点与传入链表不匹配)
        plistnode对应传入节点，pplistnode对应目标节点
        注意,pplistnode是目标节点的指针的指针,最终调用函数得到的是一个指向目标节点的指针
        示例:
        ListLocatePriorNode(&list,&listnode,&plistnode);
    */
    ListNode *pnode = plist->head;
    if (pnode == NULL) // 空链表
    {
        *pplistnode = NULL;
        return;
    }
    while (pnode->pnext != NULL && pnode->pnext != plistnode) // pnode不是最后一个节点，而且也不是目标节点
    {
        pnode = pnode->pnext;
    }
    if (pnode->pnext == plistnode) // 找到了目标节点
    {
        *pplistnode = pnode;
        return;
    }
    else // 没能找到目标节点
    {
        *pplistnode = NULL;
        return;
    }
}

void ListLocateNextNode(ListNode *plistnode, ListNode **pplistnode)
{
    /*
        定位后一个节点,并将节点指针通过指针返回，如果没找到则返回null(已经是最后一个节点）
        plistnode对应传入节点，pplistnode对应目标节点
        注意,pplistnode是目标节点的指针的指针,最终调用函数得到的是一个指向目标节点的指针
        示例:
        ListLocatePriorNode(&listnode,&plistnode);
    */
    if (plistnode->pnext != NULL)
    {
        *pplistnode = plistnode->pnext;
        return;
    }
    else
    {
        *pplistnode = NULL;
        return;
    }
}
void ListInsert(List *plist, int n, ElemType elem)
{
    /*
        将元素插入到第n(n>0)位(新建一个节点),如果插入后元素总数不足n个，则在n之前补满值为0的节点
        示例:
        ListInsert(&list,6,26);
    */
    ListNode *pnode_1 = plist->head;
    ListNode *pnode_2 = NULL;
    if (n == 1) // 如果n=1，做特殊处理
    {
        plist->head = (ListNode *)malloc(sizeof(ListNode));
        plist->head->element = elem;
        plist->head->pnext = pnode_1;
        plist->length++;
        return;
    }
    // n>1时
    int count = 1; // count指示当前pnode指针的位置,注意pnode有可能是空指针
    while (1)
    {
        if (count + 1 == n) // 找到了插入位置
        {
            pnode_2 = pnode_1->pnext;
            pnode_1->pnext = (ListNode *)malloc(sizeof(ListNode));
            pnode_1->pnext->element = elem;
            pnode_1->pnext->pnext = pnode_2;
            plist->length++;
            return;
        }
        else // 继续往下找位置
        {
            count++;
            if (pnode_1->pnext == NULL) // 如果pnode_1已是末尾，则补一个新的空节点
            {
                pnode_1->pnext == (ListNode *)malloc(sizeof(ListNode));
                pnode_1->pnext->element = 0;
                pnode_1->pnext = NULL;
            }
            pnode_1 = pnode_1->pnext;
        }
    }
}
void ListDelete(List *plist, int n)
{
    /*
        将第n个节点删除，如果本来就没有第n个节点则什么也不做
        示例:
        ListDelete(&list,4);
    */
    ListNode *pnode_1 = plist->head;
    ListNode *pnode_2 = NULL;
    if (ListGetLength(plist) < n)
        return; // 什么也不做
    if (n == 1) // n=1时特殊处理
    {
        pnode_2 = pnode_1->pnext;
        free(pnode_1);
        plist->head = pnode_2;
        plist->length--;
        return;
    }
    // n>1时
    int i;
    for (i = 1; i < n - 1; i++)
    {
        pnode_1 = pnode_1->pnext;
    }
    // 此时pnode_1的下一个节点要删除
    pnode_2 = pnode_1->pnext->pnext;
    free(pnode_1->pnext);
    pnode_1->pnext = pnode_2;
    plist->length--;
    return;
}
void ListTraverse(List* plist,void (*Func)(ListNode*))
{
    /*
        用函数Func遍历整个链表
        示例:
        add2(ListNode* plistnode)
        {
            ...;
        }
        ListTraverse(&list,add2);
    */
    if(ListGetLength(plist) == 0)
    return;
    ListNode* pnode = plist->head;
    while(pnode != NULL)
    {
        Func(pnode);
        pnode = pnode->pnext;
    }
    return;
}
