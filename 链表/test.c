#include <stdio.h>
#include "list.h"
// 临时定义一个+3的函数
void fn(ListNode *plistnode)
{
    plistnode->element += 3;
}

int main()
{
    // 新建并初始化链表
    List list_1;
    List *plist_1 = &list_1;
    ListNode *plistnode;
    ListInit(&list_1);
    // 尾插节点
    ListInsertTail(&list_1, 5);
    ListInsertTail(&list_1, 4);
    ListInsertTail(&list_1, 3);
    ListInsertTail(&list_1, 2);
    ListInsertTail(&list_1, 1);
    printf("尾插后链表内容为:\n");
    ListPrint(&list_1);
    // 清空链表
    ListClear(&list_1);
    printf("清空后链表内容为:\n");
    ListPrint(&list_1);
    // 获取第四个节点的元素
    ListInsertTail(&list_1, 5);
    ListInsertTail(&list_1, 4);
    ListInsertTail(&list_1, 3);
    ListInsertTail(&list_1, 2);
    ListInsertTail(&list_1, 1);
    ElemType elem;
    ListGetElem(&list_1, 4, &elem);
    printf("elem现在的值为%d\n", elem);
    // 定位元素为4的节点
    ListLocateElem(&list_1, 4, &plistnode); // 此时plistnode指向目标节点
    printf("plistnode指向节点的元素为%d\n", plistnode->element);
    // 找前一个节点
    ListLocatePriorNode(&list_1, plistnode, &plistnode);
    printf("plistnode指向节点的元素为%d\n", plistnode->element);
    // 找后一个节点
    ListLocateNextNode(plistnode, &plistnode);
    printf("plistnode指向节点的元素为%d\n", plistnode->element);
    // 在第三个位置插入节点，值为8，于是变成548321
    ListInsert(&list_1, 3, 8);
    printf("插入8后链表内容为:\n");
    ListPrint(&list_1);
    // 在第十个位置插入-6,次数变成5483210006
    ListInsert(&list_1, 10, 6);
    printf("插入-6后链表内容为:\n");
    ListPrint(&list_1);
    // 删除97531节点,变成43106
    ListDelete(&list_1, 9);
    ListDelete(&list_1, 7);
    ListDelete(&list_1, 5);
    ListDelete(&list_1, 3);
    ListDelete(&list_1, 1);
    printf("删除节点后后链表内容为:\n");
    ListPrint(&list_1);
    // 遍历+3
    ListTraverse(&list_1, &fn);
    printf("遍历+3后链表内容为:\n");
    ListPrint(&list_1);
    // 两个宏
    printf("链表是否为空?:%d\n",ListIsEmpty(plist_1));
    printf("链表长度为%d\n",ListGetLength(plist_1));
    
    return 0;
}