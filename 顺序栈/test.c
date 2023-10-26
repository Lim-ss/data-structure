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
    printf("栈是否为空:%d\n",StackIsEmpty(1));
    //push测试
    StackPush(12,1);
    printf("栈是否为空:%d\n",StackIsEmpty(1));
    StackPush(13,1);
    StackPush(14,1);
    StackPush(15,1);
    printf("此时栈的深度为:%d\n",StackGetLength(1));
    //pop测试
    int a;
    StackPop(a,1);
    printf("此时栈的深度为:%d\n",StackGetLength(1));
    printf("pop出来的数为%d\n",a);
    //clear测试
    StackClear(1);
    printf("此时栈的深度为:%d\n",StackGetLength(1));
    StackPop(a,1);
    printf("\n\n");
    
    StackInit(char,2);
    StackPush('a',2);
    StackPush('b',2);
    StackPush('c',2);
    StackPush('d',2);
    StackPush('e',2);
    printf("此时栈2的深度为:%d\n",StackGetLength(2));
    char b;
    StackPop(b,2);
    printf("此时栈2的深度为:%d\n",StackGetLength(2));
    printf("pop出来的字符为%c\n",b);

    StackInit(aaa,3);
    aaa aaa1;
    aaa aaa2;
    StackPush(aaa1,3);
    printf("此时栈3的深度为:%d\n",StackGetLength(2));
    StackPush(aaa2,3);
        printf("此时栈3的深度为:%d\n",StackGetLength(2));
//这里有bug没修
}