#include<stdio.h>
#include"stack.h"

typedef struct aaa
{
    int bbb;
    int ccc;
}aaa;

int main()
{
    StackInit(int,1);
    printf("ջ�Ƿ�Ϊ��:%d\n",StackIsEmpty(1));
    //push����
    StackPush(12,1);
    printf("ջ�Ƿ�Ϊ��:%d\n",StackIsEmpty(1));
    StackPush(13,1);
    StackPush(14,1);
    StackPush(15,1);
    printf("��ʱջ�����Ϊ:%d\n",StackGetLength(1));
    //pop����
    int a;
    StackPop(a,1);
    printf("��ʱջ�����Ϊ:%d\n",StackGetLength(1));
    printf("pop��������Ϊ%d\n",a);
    //clear����
    StackClear(1);
    printf("��ʱջ�����Ϊ:%d\n",StackGetLength(1));
    StackPop(a,1);
    printf("\n\n");
    
    StackInit(char,2);
    StackPush('a',2);
    StackPush('b',2);
    StackPush('c',2);
    StackPush('d',2);
    StackPush('e',2);
    printf("��ʱջ2�����Ϊ:%d\n",StackGetLength(2));
    char b;
    StackPop(b,2);
    printf("��ʱջ2�����Ϊ:%d\n",StackGetLength(2));
    printf("pop�������ַ�Ϊ%c\n",b);

    StackInit(aaa,3);
    aaa aaa1;
    aaa aaa2;
    StackPush(aaa1,3);
    printf("��ʱջ3�����Ϊ:%d\n",StackGetLength(2));
    StackPush(aaa2,3);
        printf("��ʱջ3�����Ϊ:%d\n",StackGetLength(2));
//������bugû��
}