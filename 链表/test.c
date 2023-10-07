#include <stdio.h>
#include "list.h"
// ��ʱ����һ��+3�ĺ���
void fn(ListNode *plistnode)
{
    plistnode->element += 3;
}

int main()
{
    // �½�����ʼ������
    List list_1;
    List *plist_1 = &list_1;
    ListNode *plistnode;
    ListInit(&list_1);
    // β��ڵ�
    ListInsertTail(&list_1, 5);
    ListInsertTail(&list_1, 4);
    ListInsertTail(&list_1, 3);
    ListInsertTail(&list_1, 2);
    ListInsertTail(&list_1, 1);
    printf("β�����������Ϊ:\n");
    ListPrint(&list_1);
    // �������
    ListClear(&list_1);
    printf("��պ���������Ϊ:\n");
    ListPrint(&list_1);
    // ��ȡ���ĸ��ڵ��Ԫ��
    ListInsertTail(&list_1, 5);
    ListInsertTail(&list_1, 4);
    ListInsertTail(&list_1, 3);
    ListInsertTail(&list_1, 2);
    ListInsertTail(&list_1, 1);
    ElemType elem;
    ListGetElem(&list_1, 4, &elem);
    printf("elem���ڵ�ֵΪ%d\n", elem);
    // ��λԪ��Ϊ4�Ľڵ�
    ListLocateElem(&list_1, 4, &plistnode); // ��ʱplistnodeָ��Ŀ��ڵ�
    printf("plistnodeָ��ڵ��Ԫ��Ϊ%d\n", plistnode->element);
    // ��ǰһ���ڵ�
    ListLocatePriorNode(&list_1, plistnode, &plistnode);
    printf("plistnodeָ��ڵ��Ԫ��Ϊ%d\n", plistnode->element);
    // �Һ�һ���ڵ�
    ListLocateNextNode(plistnode, &plistnode);
    printf("plistnodeָ��ڵ��Ԫ��Ϊ%d\n", plistnode->element);
    // �ڵ�����λ�ò���ڵ㣬ֵΪ8�����Ǳ��548321
    ListInsert(&list_1, 3, 8);
    printf("����8����������Ϊ:\n");
    ListPrint(&list_1);
    // �ڵ�ʮ��λ�ò���-6,�������5483210006
    ListInsert(&list_1, 10, 6);
    printf("����-6����������Ϊ:\n");
    ListPrint(&list_1);
    // ɾ��97531�ڵ�,���43106
    ListDelete(&list_1, 9);
    ListDelete(&list_1, 7);
    ListDelete(&list_1, 5);
    ListDelete(&list_1, 3);
    ListDelete(&list_1, 1);
    printf("ɾ���ڵ�����������Ϊ:\n");
    ListPrint(&list_1);
    // ����+3
    ListTraverse(&list_1, &fn);
    printf("����+3����������Ϊ:\n");
    ListPrint(&list_1);
    // ������
    printf("�����Ƿ�Ϊ��?:%d\n",ListIsEmpty(plist_1));
    printf("������Ϊ%d\n",ListGetLength(plist_1));
    
    return 0;
}