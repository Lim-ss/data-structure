#include <stdio.h>
#include "high_precision.h"
#include "stack.h"
#include <ctype.h>
void PreciseNumberInit2(PreciseNumber2 *pcsnum)
{
    /*
        初始化一个高精度数，使其的值为0
    */
    pcsnum->signbit = 0;
    pcsnum->precison = PRECISION + 10;
    for (int i = 0; i < pcsnum->precison; i++)
    {
        pcsnum->number[i] = 0;
    }
    return;
}
void PreciseNumberInit10(PreciseNumber10 *pcsnum)
{
    /*
        初始化一个高精度数，使其的值为0
    */
    pcsnum->signbit = 0;
    pcsnum->precison = PRECISION + 4;
    for (int i = 0; i < pcsnum->precison; i++)
    {
        pcsnum->number[i] = 0;
    }
    return;
}
void PreciseNumberPrint2(PreciseNumber2 *pcsnum)
{
    if (pcsnum->signbit == 1)
        printf("-");
    for (int i = pcsnum->precison - 1; i >= pcsnum->precison - 10; i--)
    {
        printf("%d", pcsnum->number[i]);
    }
    printf(".");
    for (int i = pcsnum->precison - 11; i >= 0; i--)
    {
        printf("%d", pcsnum->number[i]);
    }
    printf("\n");
    return;
}
void PreciseNumberPrint10(PreciseNumber10 *pcsnum)
{
    if (pcsnum->signbit == 1)
        printf("-");
    for (int i = pcsnum->precison - 1; i >= pcsnum->precison - 4; i--)
    {
        printf("%d", pcsnum->number[i]);
    }
    printf(".");
    for (int i = pcsnum->precison - 5; i >= 0; i--)
    {
        printf("%d", pcsnum->number[i]);
    }
    printf("\n");
    return;
}

void PreciseNumberInput2(PreciseNumber2 *pcsnum)
{
    char a;             // 用于接收字符
    StackInit(char, 1); // 用于存字符的栈
    a = getchar();
    if (isdigit(a))
    {
        StackPush(a, 1);
    }
    else if (a == '-')
        pcsnum->signbit = 1;
    else
    {
        printf("输入非法\n");
        exit(-1);
    }
    while (1)
    {
        a = getchar();
        if (isdigit(a))
        {
            StackPush(a, 1);
        }
        else if (a == '.' || a == '\n')
            break;
        else
        {
            printf("输入非法\n");
            exit(-1);
        }
    }
    int i = pcsnum->precison - 10;
    while (i < pcsnum->precison && StackGetLength(1) != 0) // 小数点前的十位未填满且栈中还有剩余的数字
    {
        StackPop(a, 1);               // 用a来接收来自栈的字符
        pcsnum->number[i] = atoi(&a); // 将字符转为数字并写入高精数中
        i++;
    }
    i = pcsnum->precison - 11;
    while (i >= 0)
    {
        a = getchar();
        if (isdigit(a))
        {
            pcsnum->number[i] = atoi(&a);
            i--;
        }
        else if (a == '\n')
        {
            break;
        }
        else
        {
            printf("输入非法\n");
            exit(-1);
        }
    }
    return;
}
void PreciseNumberInput10(PreciseNumber10 *pcsnum)
{
    char a;             // 用于接收字符
    StackInit(char, 1); // 用于存字符的栈
    a = getchar();
    if (isdigit(a))
    {
        StackPush(a, 1);
    }
    else if (a == '-')
        pcsnum->signbit = 1;
    else
    {
        printf("输入非法\n");
        exit(-1);
    }
    while (1)
    {
        a = getchar();
        if (isdigit(a))
        {
            StackPush(a, 1);
        }
        else if (a == '.' || a == '\n')
            break;
        else
        {
            printf("输入非法\n");
            exit(-1);
        }
    }
    int i = pcsnum->precison - 4;
    while (i < pcsnum->precison && StackGetLength(1) != 0) // 小数点前的十位未填满且栈中还有剩余的数字
    {
        StackPop(a, 1);               // 用a来接收来自栈的字符
        pcsnum->number[i] = atoi(&a); // 将字符转为数字并写入高精数中
        i++;
    }
    i = pcsnum->precison - 5;
    while (i >= 0)
    {
        a = getchar();
        if (isdigit(a))
        {
            pcsnum->number[i] = atoi(&a);
            i--;
        }
        else if (a == '\n')
        {
            break;
        }
        else
        {
            printf("输入非法\n");
            exit(-1);
        }
    }
    return;
}

void PreciseNumberAdd2(PreciseNumber2 *pcsnum1, PreciseNumber2 *pcsnum2, PreciseNumber2 *pcsnum3)
{
    if (pcsnum2->signbit == pcsnum3->signbit) // 两加数同正负
    {
        pcsnum1->signbit = pcsnum2->signbit;
        for (int i = 0; i < pcsnum1->precison; i++)
        {
            pcsnum1->number[i] = pcsnum2->number[i] + pcsnum3->number[i];
        }
        for (int i = 0; i < pcsnum1->precison - 1; i++) // 进位，除了最高位做特殊处理
        {
            pcsnum1->number[i + 1] += pcsnum1->number[i] / 2;
            pcsnum1->number[i] = pcsnum1->number[i] % 2;
        }
        if (pcsnum1->number[pcsnum1->precison - 1] >= 2)
            printf("溢出");
        pcsnum1->number[pcsnum1->precison - 1] = pcsnum1->number[pcsnum1->precison - 1] % 2;
        return;
    }
    else // 两加数正负相反
    {
        int thebigone = 0;
        for (int i = pcsnum1->precison - 1; i >= 0; i--)
        {
            if (pcsnum2->number[i] > pcsnum3->number[i])
            {
                thebigone = 2;
                break;
            }
            else if (pcsnum2->number[i] < pcsnum3->number[i])
            {
                thebigone = 3;
                break;
            }
        }
        if (thebigone == 2)
        {
            // printf("a\n");
            for (int i = 0; i < pcsnum1->precison; i++)
            {
                pcsnum1->number[i] = pcsnum2->number[i] - pcsnum3->number[i];
            }
            for (int i = 0; i < pcsnum1->precison - 1; i++) // 借位，最高位不做处理
            {
                if (pcsnum1->number[i] < 0)
                {
                    pcsnum1->number[i + 1] -= 1;
                    pcsnum1->number[i] += 2;
                }
            }
            pcsnum1->signbit = pcsnum2->signbit;
        }
        else if (thebigone == 3)
        {
            // printf("b\n");
            for (int i = 0; i < pcsnum1->precison; i++)
            {
                pcsnum1->number[i] = pcsnum3->number[i] - pcsnum2->number[i];
            }
            for (int i = 0; i < pcsnum1->precison - 1; i++) // 借位，除了最高位不做处理
            {
                if (pcsnum1->number[i] < 0)
                {
                    pcsnum1->number[i + 1] -= 1;
                    pcsnum1->number[i] += 2;
                }
            }
            pcsnum1->signbit = pcsnum3->signbit;
        }
        else // 两数绝对值相等，计算结果为0
        {
            PreciseNumberInit2(pcsnum1);
        }
    }
    return;
}
void PreciseNumberAdd10(PreciseNumber10 *pcsnum1, PreciseNumber10 pcsnum2, PreciseNumber10 pcsnum3)
{
    if (pcsnum2.signbit == pcsnum3.signbit) // 两加数同正负
    {
        pcsnum1->signbit = pcsnum2.signbit;
        for (int i = 0; i < pcsnum1->precison; i++)
        {
            pcsnum1->number[i] = pcsnum2.number[i] + pcsnum3.number[i];
        }
        for (int i = 0; i < pcsnum1->precison - 1; i++) // 进位，除了最高位做特殊处理
        {
            pcsnum1->number[i + 1] += pcsnum1->number[i] / 10;
            pcsnum1->number[i] = pcsnum1->number[i] % 10;
        }
        if (pcsnum1->number[pcsnum1->precison - 1] >= 10)
            printf("溢出");
        pcsnum1->number[pcsnum1->precison - 1] = pcsnum1->number[pcsnum1->precison - 1] % 10;
        return;
    }
    else // 两加数正负相反
    {
        int thebigone = 0;
        for (int i = pcsnum1->precison - 1; i >= 0; i--)
        {
            if (pcsnum2.number[i] > pcsnum3.number[i])
            {
                thebigone = 2;
                break;
            }
            else if (pcsnum2.number[i] < pcsnum3.number[i])
            {
                thebigone = 3;
                break;
            }
        }
        if (thebigone == 2)
        {
            // printf("a\n");
            for (int i = 0; i < pcsnum1->precison; i++)
            {
                pcsnum1->number[i] = pcsnum2.number[i] - pcsnum3.number[i];
            }
            for (int i = 0; i < pcsnum1->precison - 1; i++) // 借位，最高位不做处理
            {
                if (pcsnum1->number[i] < 0)
                {
                    pcsnum1->number[i + 1] -= 1;
                    pcsnum1->number[i] += 10;
                }
            }
            pcsnum1->signbit = pcsnum2.signbit;
        }
        else if (thebigone == 3)
        {
            // printf("b\n");
            for (int i = 0; i < pcsnum1->precison; i++)
            {
                pcsnum1->number[i] = pcsnum3.number[i] - pcsnum2.number[i];
            }
            for (int i = 0; i < pcsnum1->precison - 1; i++) // 借位，除了最高位不做处理
            {
                if (pcsnum1->number[i] < 0)
                {
                    pcsnum1->number[i + 1] -= 1;
                    pcsnum1->number[i] += 10;
                }
            }
            pcsnum1->signbit = pcsnum3.signbit;
        }
        else // 两数绝对值相等，计算结果为0
        {
            PreciseNumberInit10(pcsnum1);
        }
    }
    return;
}
void PreciseNumberSub10(PreciseNumber10 *pcsnum1, PreciseNumber10 pcsnum2, PreciseNumber10 pcsnum3)
{
    /*
        pcsnum1 = pcsnum2 - pcsnum3
    */
    PreciseNumber10 t = pcsnum3;
    t.signbit = 1 - t.signbit;
    PreciseNumberAdd10(pcsnum1, pcsnum2, t);
    return;
}
void PreciseNumberMul2(PreciseNumber2 *pcsnum1, PreciseNumber2 *pcsnum2, PreciseNumber2 *pcsnum3)
{
    pcsnum1->signbit = (pcsnum2->signbit == pcsnum3->signbit) ? 0 : 1;
    int rawresult[PRECISION * 2 + 10] = {0};

    for (int i = 0; i < pcsnum1->precison; i++)
    {
        for (int j = 0; j < pcsnum1->precison; j++)
        {
            if (i + j >= PRECISION * 2 + 10)
                // printf("溢出\n");
                ;
            else
            {

                rawresult[i + j] += pcsnum2->number[i] * pcsnum3->number[j];
            }
        }
    }
    // 进位
    for (int i = 0; i < (PRECISION * 2 + 10) - 1; i++) // 最高位做特殊处理
    {
        rawresult[i + 1] += rawresult[i] / 2;
        rawresult[i] = rawresult[i] % 2;
    }
    if (rawresult[(PRECISION * 2 + 10) - 1] >= 2)
        printf("溢出\n");
    rawresult[(PRECISION * 2 + 10) - 1] = rawresult[(PRECISION * 2 + 10) - 1] % 2;

    for (int i = 0; i < (PRECISION + 10); i++)
    {
        pcsnum1->number[i] = rawresult[i + PRECISION];
    }
    return;
}
void PreciseNumberMul10(PreciseNumber10 *pcsnum1, PreciseNumber10 pcsnum2, PreciseNumber10 pcsnum3)
{
    pcsnum1->signbit = (pcsnum2.signbit == pcsnum3.signbit) ? 0 : 1;
    int rawresult[PRECISION * 2 + 4] = {0};

    for (int i = 0; i < pcsnum1->precison; i++)
    {
        for (int j = 0; j < pcsnum1->precison; j++)
        {
            if (i + j >= PRECISION * 2 + 10)
                // printf("溢出\n");
                ;
            else
            {

                rawresult[i + j] += pcsnum2.number[i] * pcsnum3.number[j];
            }
        }
    }
    // 进位
    for (int i = 0; i < (PRECISION * 2 + 4) - 1; i++) // 最高位做特殊处理
    {
        rawresult[i + 1] += rawresult[i] / 10;
        rawresult[i] = rawresult[i] % 10;
    }
    if (rawresult[(PRECISION * 2 + 4) - 1] >= 10)
        printf("溢出\n");
    rawresult[(PRECISION * 2 + 4) - 1] = rawresult[(PRECISION * 2 + 4) - 1] % 10;

    for (int i = 0; i < (PRECISION + 4); i++)
    {
        pcsnum1->number[i] = rawresult[i + PRECISION];
    }
    return;
}
void PreciseNumber10to2(PreciseNumber2 *pcsnum1, PreciseNumber10 pcsnum2)
{
    pcsnum1->signbit = pcsnum2.signbit;
    int num; // 余数
    int integerPart = 1000 * pcsnum2.number[PRECISION + 3] + 100 * pcsnum2.number[PRECISION + 2] + 10 * pcsnum2.number[PRECISION + 1] + 1 * pcsnum2.number[PRECISION];
    int i = PRECISION;
    while (integerPart != 0 && i < PRECISION + 10) // 整数部分做短除法
    {
        num = integerPart % 2;
        integerPart = integerPart / 2;
        pcsnum1->number[i] = num;
        i++;
    }
    pcsnum2.number[PRECISION] = 0;           // 清空个位，用于后面小数部分的转换
    for (int i = PRECISION - 1; i >= 0; i--) // 计算二进制第i位
    {
        for (int j = 0; j < PRECISION; j++) // 十进制数的小数部分乘2，个位获得的进位作为二进制的第i个数字
        {
            pcsnum2.number[j] *= 2;
        }
        for (int j = 0; j < PRECISION; j++)
        {
            pcsnum2.number[j + 1] += pcsnum2.number[j] / 10;
            pcsnum2.number[j] = pcsnum2.number[j] % 10;
        }
        pcsnum1->number[i] = pcsnum2.number[PRECISION];
        pcsnum2.number[PRECISION] = 0;
    }
    return;
}
void PreciseNumber10toN(PreciseNumber10 pcsnum, int N)
{
    if (pcsnum.signbit == 1)
        printf("-");
    int num; // 余数
    int integerPart = 1000 * pcsnum.number[PRECISION + 3] + 100 * pcsnum.number[PRECISION + 2] + 10 * pcsnum.number[PRECISION + 1] + 1 * pcsnum.number[PRECISION];
    StackInit(int, 1);
    while (integerPart != 0) // 整数部分做短除法
    {
        num = integerPart % N;
        integerPart = integerPart / N;
        StackPush(num, 1);
    }
    while (!StackIsEmpty(1))
    {
        StackPop(num, 1);
        printf("%d ", num);
    }
    printf(".");
    // 小数部分
    pcsnum.number[PRECISION] = 0;            // 清空个位，用于后面小数部分的转换
    for (int i = PRECISION - 1; i >= 0; i--) // 计算二进制第i位
    {
        for (int j = 0; j < PRECISION; j++) // 十进制数的小数部分乘2，个位获得的进位作为二进制的第i个数字
        {
            pcsnum.number[j] *= N;
        }
        for (int j = 0; j < PRECISION; j++)
        {
            pcsnum.number[j + 1] += pcsnum.number[j] / 10;
            pcsnum.number[j] = pcsnum.number[j] % 10;
        }
        printf("%d ", pcsnum.number[PRECISION]);
        pcsnum.number[PRECISION] = 0;
    }
    printf("\n");
    return;
}
void PreciseNumberPolynomial(PreciseNumber10 x)
{
    PreciseNumber10 sum, coefficient,t; // 总和、系数、临时数
    int index;//指数
    PreciseNumberInit10(&sum);

    
    char a;             // 用于接收字符
    StackInit(char, 1); // 用于存字符的栈
    while (1)
    {
        // 接收系数整数部分
        PreciseNumberInit10(&coefficient); // 刷新系数为0
        a = getchar();
        if (isdigit(a))
        {
            StackPush(a, 1);
        }
        else if (a == '-')
            coefficient.signbit = 1;
        else if (a == '+')
            coefficient.signbit = 0;
        else if(a == '\n')
        break;
        else
        {
            printf("输入非法\n");
            exit(-1);
        }
        while (1)
        {
            a = getchar();
            if (isdigit(a))
            {
                StackPush(a, 1);
            }
            else if (a == '.')
                break;
            else
            {
                printf("输入非法\n");
                exit(-1);
            }
        }
        int i = coefficient.precison - 4;
        while (i < coefficient.precison && StackGetLength(1) != 0) // 小数点前的十位未填满且栈中还有剩余的数字
        {
            StackPop(a, 1);                   // 用a来接收来自栈的字符
            coefficient.number[i] = atoi(&a); // 将字符转为数字并写入高精数中
            i++;
        }
        // 接收系数小数部分
        i = coefficient.precison - 5;
        while (1)
        {
            a = getchar();
            if (isdigit(a))
            {
                coefficient.number[i] = atoi(&a);
                i--;
            }
            else if (a == '*')
                break; // 进入下一阶段
            else
            {
                printf("输入非法\n");
                exit(-1);
            }
        }
        // 接收指数部分
        a = getchar();
        if (a != 'x')//检查合法性
        {
            printf("输入非法\n");
            exit(-1);
        }
        a = getchar();
        if (a != '^')//检查合法性
        {
            printf("输入非法\n");
            exit(-1);
        }
        a = getchar();
        if(isdigit(a))
        {
            index = atoi(&a);
        }
        else
        {
            printf("输入非法\n");
            exit(-1);
        }
        //增加总和
        PreciseNumberInit10(&t);
            t.number[PRECISION] = 1;
        for(int i = 0;i<index;i++)//x^index
        {
            PreciseNumberMul10(&t,t,x);
        }
        PreciseNumberMul10(&t,t,coefficient);
        PreciseNumberAdd10(&sum,sum,t);
    }
    //打印结果
    PreciseNumberPrint10(&sum);
}