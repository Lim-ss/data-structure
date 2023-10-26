#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define STACK_INIT_SIZE 20
#define STACK_EXTEND_SIZE 20

/*
    ��ʼ��һ��ջ��num�������ֶ��ջ
    ���統datatype=int,num=2��
    ջ��Ϊpstackbase_2
    ջ��Ϊpstacktop_2
    ��СΪstacksize_2
*/
#define StackInit(datatype, num)                                               \
    datatype *pstackbase_##num;                                                \
    datatype *pstacktop_##num;                                                 \
    int stacksize_##num = STACK_INIT_SIZE;                                     \
    pstackbase_##num = (datatype *)malloc(sizeof(datatype) * stacksize_##num); \
    if (pstackbase_##num != NULL)                                              \
    {                                                                          \
        pstacktop_##num = pstackbase_##num;                                    \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        printf("malloc failure\n");                                            \
        exit(-1);                                                              \
    }

/*
    �ж�ջ�Ƿ��
*/
#define StackIsEmpty(num) \
    ((pstacktop_##num == pstackbase_##num) ? 1 : 0)

/*

*/
#define StackPush(data, num)                                                                              \
    if (pstacktop_##num - pstackbase_##num == stacksize_##num)                                            \
    {                                                                                                     \
        pstackbase_##num = realloc(pstackbase_##num,sizeof(data) * (stacksize_##num + STACK_EXTEND_SIZE)); \
        if (pstackbase_##num == NULL)                                                                     \
        {                                                                                                 \
            printf("realloc failure");                                                                    \
            exit(-1);                                                                                     \
        }                                                                                                 \
        else                                                                                              \
        {                                                                                                 \
            pstacktop_##num = pstackbase_##num + stacksize_##num;                                         \
            stacksize_##num += STACK_EXTEND_SIZE;                                                         \
        }                                                                                                 \
    }                                                                                                     \
    *pstacktop_##num = data;                                                                              \
    pstacktop_##num++

/*
    ���ջ�գ��������ʾ��Ȼ��ʲôҲ����
*/
#define StackPop(data, num)      \
    if (StackIsEmpty(num))       \
    {                            \
        printf("pop failure");   \
    }                            \
    else                         \
    {                            \
        pstacktop_##num--;       \
        data = *pstacktop_##num; \
    }

#define StackClear(num) \
    pstacktop_##num = pstackbase_##num

#define StackGetLength(num) \
    (pstacktop_##num - pstackbase_##num)



#endif