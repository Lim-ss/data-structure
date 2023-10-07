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
        ��������ڵ�
    */
    ElemType element;
    struct ListNode *pnext;
} ListNode, *pListNode;
typedef struct List
{
    /*
        ��������
    */
    ListNode *head; // ָ��������ͷ�ڵ�
    int length;     // ����ڵ�����������ṹ��������һ���ڵ㣩
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

void ListInit(List *plist)
{
    /*
        �½�һ��������
        ʾ��:
        List newlist;
        ListInit(&newlist);
    */
    plist->head = NULL;
    plist->length = 0;
}

void ListInsertTail(List *plist, ElemType e)
{
    /*
        ������β������һ����Ԫ��
        ʾ��:
        ListInsertTail(&list,e)
    */

    // ����ǿ�����
    if (ListIsEmpty(plist))
    {
        plist->head = (ListNode *)malloc(sizeof(ListNode));
        if (plist->head == NULL) // �ڴ������
            exit(-1);
        plist->head->element = e;
        plist->head->pnext = NULL;
        plist->length++;
        return;
    }
    // ������ǿ�����
    ListNode *plistNode = plist->head;
    int i;
    for (i = 0; i < (ListGetLength(plist) - 1); i++)
    {
        plistNode = plistNode->pnext; // �õ�ԭ�������һ���ڵ�ָ��
    }
    plistNode->pnext = (ListNode *)malloc(sizeof(ListNode));
    if (plist->head == NULL) // �ڴ������
        exit(-1);
    plistNode->pnext->element = e;
    plistNode->pnext->pnext = NULL;
    plist->length++;
    return;
}

void ListPrint(List *plist)
{
    /*
        ��ӡ���нڵ��Ԫ�أ���int��ʽ��
        ʾ��:
        ListPrint(&list);
    */
    if (ListIsEmpty(plist))
        return;
    ListNode *plistnode = plist->head;
    while (plistnode != NULL)
    {
        printf("%d\n", (int)plistnode->element);
        plistnode = plistnode->pnext;
    }
    return;
}

void ListClear(List *plist)
{
    /*
        �������ʹ֮��Ϊ����Ϊ0�Ŀ�����
        ʾ��:
        ListClear(&list);
    */
    if (ListIsEmpty(plist))
        return;
    ListNode *plistnode_1 = NULL;
    ListNode *plistnode_2 = NULL; // plistnode_2������ʱ�����Ҫfree���Ľڵ�
    plistnode_1 = plist->head;
    while (plistnode_1 != NULL) // ÿ��ѭ��ɾ����ǰplistnode_1ָ��Ľڵ㣬��ʹָ֮����һ���ڵ�
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
        �������ĵ�n���ڵ��Ԫ��(n��1��ʼ),����Ԫ��ͨ��ָ�뷵��
        ʾ��:
        ListGetElem(&list,n,&elem);
    */
    if (ListGetLength(plist) < n) // ����Ƿ�Խ��
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
        ��λ����ĵ�һ��Ԫ��Ϊelem�Ľڵ�,�����ڵ�ָ��ͨ��ָ�뷵�أ����û�ҵ��򷵻�null
        ע��,pplistnode��Ŀ��ڵ��ָ���ָ��,���յ��ú����õ�����һ��ָ��Ŀ��ڵ��ָ��
        ʾ��:
        ListLocateElem(&list,elem,&plistnode);
    */
    ListNode *pnode = plist->head;
    while (pnode != NULL) // ��������
    {
        if (pnode->element == elem)
        {
            *pplistnode = pnode;
            return;
        }
        pnode = pnode->pnext;
    }
    *pplistnode = NULL; // δ�ܲ��ҵ����������Ľڵ�
    return;
}
void ListLocatePriorNode(List *plist, ListNode *plistnode, ListNode **pplistnode)
{
    /*
        ��λǰһ���ڵ�,�����ڵ�ָ��ͨ��ָ�뷵�أ����û�ҵ��򷵻�null(�Ѿ��ǵ�һ���ڵ㣬���ߴ���ڵ��봫������ƥ��)
        plistnode��Ӧ����ڵ㣬pplistnode��ӦĿ��ڵ�
        ע��,pplistnode��Ŀ��ڵ��ָ���ָ��,���յ��ú����õ�����һ��ָ��Ŀ��ڵ��ָ��
        ʾ��:
        ListLocatePriorNode(&list,&listnode,&plistnode);
    */
    ListNode *pnode = plist->head;
    if (pnode == NULL) // ������
    {
        *pplistnode = NULL;
        return;
    }
    while (pnode->pnext != NULL && pnode->pnext != plistnode) // pnode�������һ���ڵ㣬����Ҳ����Ŀ��ڵ�
    {
        pnode = pnode->pnext;
    }
    if (pnode->pnext == plistnode) // �ҵ���Ŀ��ڵ�
    {
        *pplistnode = pnode;
        return;
    }
    else // û���ҵ�Ŀ��ڵ�
    {
        *pplistnode = NULL;
        return;
    }
}

void ListLocateNextNode(ListNode *plistnode, ListNode **pplistnode)
{
    /*
        ��λ��һ���ڵ�,�����ڵ�ָ��ͨ��ָ�뷵�أ����û�ҵ��򷵻�null(�Ѿ������һ���ڵ㣩
        plistnode��Ӧ����ڵ㣬pplistnode��ӦĿ��ڵ�
        ע��,pplistnode��Ŀ��ڵ��ָ���ָ��,���յ��ú����õ�����һ��ָ��Ŀ��ڵ��ָ��
        ʾ��:
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
        ��Ԫ�ز��뵽��n(n>0)λ(�½�һ���ڵ�),��������Ԫ����������n��������n֮ǰ����ֵΪ0�Ľڵ�
        ʾ��:
        ListInsert(&list,6,26);
    */
    ListNode *pnode_1 = plist->head;
    ListNode *pnode_2 = NULL;
    if (n == 1) // ���n=1�������⴦��
    {
        plist->head = (ListNode *)malloc(sizeof(ListNode));
        plist->head->element = elem;
        plist->head->pnext = pnode_1;
        plist->length++;
        return;
    }
    // n>1ʱ
    int count = 1; // countָʾ��ǰpnodeָ���λ��,ע��pnode�п����ǿ�ָ��
    while (1)
    {
        if (count + 1 == n) // �ҵ��˲���λ��
        {
            pnode_2 = pnode_1->pnext;
            pnode_1->pnext = (ListNode *)malloc(sizeof(ListNode));
            pnode_1->pnext->element = elem;
            pnode_1->pnext->pnext = pnode_2;
            plist->length++;
            return;
        }
        else // ����������λ��
        {
            count++;
            if (pnode_1->pnext == NULL) // ���pnode_1����ĩβ����һ���µĿսڵ�
            {
                
                pnode_1->pnext = (ListNode *)malloc(sizeof(ListNode));
                pnode_1->pnext->element = 0;
                pnode_1->pnext->pnext = NULL;
                plist->length ++;
            }
            pnode_1 = pnode_1->pnext;
        }
    }
}
void ListDelete(List *plist, int n)
{
    /*
        ����n���ڵ�ɾ�������������û�е�n���ڵ���ʲôҲ����
        ʾ��:
        ListDelete(&list,4);
    */
    ListNode *pnode_1 = plist->head;
    ListNode *pnode_2 = NULL;
    if (ListGetLength(plist) < n)
        return; // ʲôҲ����
    if (n == 1) // n=1ʱ���⴦��
    {
        pnode_2 = pnode_1->pnext;
        free(pnode_1);
        plist->head = pnode_2;
        plist->length--;
        return;
    }
    // n>1ʱ
    int i;
    for (i = 1; i < n - 1; i++)
    {
        pnode_1 = pnode_1->pnext;
    }
    // ��ʱpnode_1����һ���ڵ�Ҫɾ��
    pnode_2 = pnode_1->pnext->pnext;
    free(pnode_1->pnext);
    pnode_1->pnext = pnode_2;
    plist->length--;
    return;
}
void ListTraverse(List *plist, void (*Func)(ListNode *))
{
    /*
        �ú���Func������������
        ʾ��:
        add2(ListNode* plistnode)
        {
            ...;
        }
        ListTraverse(&list,add2);
    */
    if (ListGetLength(plist) == 0)
        return;
    ListNode *pnode = plist->head;
    while (pnode != NULL)
    {
        Func(pnode);
        pnode = pnode->pnext;
    }
    return;
}

#endif