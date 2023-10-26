#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define ListGetLength(plist) (plist->length)
#define ListIsEmpty(plist) (plist->length == 0)

typedef int ElemType;
typedef struct ListNode
{
    /*
        定义链表节点
    */
    ElemType element;
    struct ListNode *pnext;
} ListNode, *pListNode;
typedef struct List
{
    /*
        定义链表
    */
    ListNode *head; // 指向该链表的头节点
    int length;     // 链表节点数量（链表结构体自身不算一个节点）
} List, *pList;

void ListInit(List *plist);
void ListInsertTail(List *plist, ElemType e);
void ListPrint(List *plist);
void ListClear(List *plist);
void ListGetElem(List *plist, int n, ElemType *pelem);
void ListLocateElem(List *plist, ElemType elem, ListNode **plistnode);
void ListLocatePriorNode(List *plist, ListNode *plistnode, ListNode **pplistnode);
void ListLocateNextNode(ListNode *plistnode, ListNode **pplistnode);
void ListInsert(List *plist, int n, ElemType elem);
void ListDelete(List *plist, int n);
void ListTraverse(List *plist, void (*Func)(ListNode *));

#endif