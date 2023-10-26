#include <stdio.h>
#include "high_precision.h"
#include "stack.h"
#include <ctype.h>
void PreciseNumberInit2(PreciseNumber2 *pcsnum)
{
    /*
        ��ʼ��һ���߾�������ʹ���ֵΪ0
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
        ��ʼ��һ���߾�������ʹ���ֵΪ0
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
    char a;             // ���ڽ����ַ�
    StackInit(char, 1); // ���ڴ��ַ���ջ
    a = getchar();
    if (isdigit(a))
    {
        StackPush(a, 1);
    }
    else if (a == '-')
        pcsnum->signbit = 1;
    else
    {
        printf("����Ƿ�\n");
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
            printf("����Ƿ�\n");
            exit(-1);
        }
    }
    int i = pcsnum->precison - 10;
    while (i < pcsnum->precison && StackGetLength(1) != 0) // С����ǰ��ʮλδ������ջ�л���ʣ�������
    {
        StackPop(a, 1);               // ��a����������ջ���ַ�
        pcsnum->number[i] = atoi(&a); // ���ַ�תΪ���ֲ�д��߾�����
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
            printf("����Ƿ�\n");
            exit(-1);
        }
    }
    return;
}
void PreciseNumberInput10(PreciseNumber10 *pcsnum)
{
    char a;             // ���ڽ����ַ�
    StackInit(char, 1); // ���ڴ��ַ���ջ
    a = getchar();
    if (isdigit(a))
    {
        StackPush(a, 1);
    }
    else if (a == '-')
        pcsnum->signbit = 1;
    else
    {
        printf("����Ƿ�\n");
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
            printf("����Ƿ�\n");
            exit(-1);
        }
    }
    int i = pcsnum->precison - 4;
    while (i < pcsnum->precison && StackGetLength(1) != 0) // С����ǰ��ʮλδ������ջ�л���ʣ�������
    {
        StackPop(a, 1);               // ��a����������ջ���ַ�
        pcsnum->number[i] = atoi(&a); // ���ַ�תΪ���ֲ�д��߾�����
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
            printf("����Ƿ�\n");
            exit(-1);
        }
    }
    return;
}

void PreciseNumberAdd2(PreciseNumber2 *pcsnum1, PreciseNumber2 *pcsnum2, PreciseNumber2 *pcsnum3)
{
    if (pcsnum2->signbit == pcsnum3->signbit) // ������ͬ����
    {
        pcsnum1->signbit = pcsnum2->signbit;
        for (int i = 0; i < pcsnum1->precison; i++)
        {
            pcsnum1->number[i] = pcsnum2->number[i] + pcsnum3->number[i];
        }
        for (int i = 0; i < pcsnum1->precison - 1; i++) // ��λ���������λ�����⴦��
        {
            pcsnum1->number[i + 1] += pcsnum1->number[i] / 2;
            pcsnum1->number[i] = pcsnum1->number[i] % 2;
        }
        if (pcsnum1->number[pcsnum1->precison - 1] >= 2)
            printf("���");
        pcsnum1->number[pcsnum1->precison - 1] = pcsnum1->number[pcsnum1->precison - 1] % 2;
        return;
    }
    else // �����������෴
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
            for (int i = 0; i < pcsnum1->precison - 1; i++) // ��λ�����λ��������
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
            for (int i = 0; i < pcsnum1->precison - 1; i++) // ��λ���������λ��������
            {
                if (pcsnum1->number[i] < 0)
                {
                    pcsnum1->number[i + 1] -= 1;
                    pcsnum1->number[i] += 2;
                }
            }
            pcsnum1->signbit = pcsnum3->signbit;
        }
        else // ��������ֵ��ȣ�������Ϊ0
        {
            PreciseNumberInit2(pcsnum1);
        }
    }
    return;
}
void PreciseNumberAdd10(PreciseNumber10 *pcsnum1, PreciseNumber10 pcsnum2, PreciseNumber10 pcsnum3)
{
    if (pcsnum2.signbit == pcsnum3.signbit) // ������ͬ����
    {
        pcsnum1->signbit = pcsnum2.signbit;
        for (int i = 0; i < pcsnum1->precison; i++)
        {
            pcsnum1->number[i] = pcsnum2.number[i] + pcsnum3.number[i];
        }
        for (int i = 0; i < pcsnum1->precison - 1; i++) // ��λ���������λ�����⴦��
        {
            pcsnum1->number[i + 1] += pcsnum1->number[i] / 10;
            pcsnum1->number[i] = pcsnum1->number[i] % 10;
        }
        if (pcsnum1->number[pcsnum1->precison - 1] >= 10)
            printf("���");
        pcsnum1->number[pcsnum1->precison - 1] = pcsnum1->number[pcsnum1->precison - 1] % 10;
        return;
    }
    else // �����������෴
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
            for (int i = 0; i < pcsnum1->precison - 1; i++) // ��λ�����λ��������
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
            for (int i = 0; i < pcsnum1->precison - 1; i++) // ��λ���������λ��������
            {
                if (pcsnum1->number[i] < 0)
                {
                    pcsnum1->number[i + 1] -= 1;
                    pcsnum1->number[i] += 10;
                }
            }
            pcsnum1->signbit = pcsnum3.signbit;
        }
        else // ��������ֵ��ȣ�������Ϊ0
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
                // printf("���\n");
                ;
            else
            {

                rawresult[i + j] += pcsnum2->number[i] * pcsnum3->number[j];
            }
        }
    }
    // ��λ
    for (int i = 0; i < (PRECISION * 2 + 10) - 1; i++) // ���λ�����⴦��
    {
        rawresult[i + 1] += rawresult[i] / 2;
        rawresult[i] = rawresult[i] % 2;
    }
    if (rawresult[(PRECISION * 2 + 10) - 1] >= 2)
        printf("���\n");
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
                // printf("���\n");
                ;
            else
            {

                rawresult[i + j] += pcsnum2.number[i] * pcsnum3.number[j];
            }
        }
    }
    // ��λ
    for (int i = 0; i < (PRECISION * 2 + 4) - 1; i++) // ���λ�����⴦��
    {
        rawresult[i + 1] += rawresult[i] / 10;
        rawresult[i] = rawresult[i] % 10;
    }
    if (rawresult[(PRECISION * 2 + 4) - 1] >= 10)
        printf("���\n");
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
    int num; // ����
    int integerPart = 1000 * pcsnum2.number[PRECISION + 3] + 100 * pcsnum2.number[PRECISION + 2] + 10 * pcsnum2.number[PRECISION + 1] + 1 * pcsnum2.number[PRECISION];
    int i = PRECISION;
    while (integerPart != 0 && i < PRECISION + 10) // �����������̳���
    {
        num = integerPart % 2;
        integerPart = integerPart / 2;
        pcsnum1->number[i] = num;
        i++;
    }
    pcsnum2.number[PRECISION] = 0;           // ��ո�λ�����ں���С�����ֵ�ת��
    for (int i = PRECISION - 1; i >= 0; i--) // ��������Ƶ�iλ
    {
        for (int j = 0; j < PRECISION; j++) // ʮ��������С�����ֳ�2����λ��õĽ�λ��Ϊ�����Ƶĵ�i������
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
    int num; // ����
    int integerPart = 1000 * pcsnum.number[PRECISION + 3] + 100 * pcsnum.number[PRECISION + 2] + 10 * pcsnum.number[PRECISION + 1] + 1 * pcsnum.number[PRECISION];
    StackInit(int, 1);
    while (integerPart != 0) // �����������̳���
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
    // С������
    pcsnum.number[PRECISION] = 0;            // ��ո�λ�����ں���С�����ֵ�ת��
    for (int i = PRECISION - 1; i >= 0; i--) // ��������Ƶ�iλ
    {
        for (int j = 0; j < PRECISION; j++) // ʮ��������С�����ֳ�2����λ��õĽ�λ��Ϊ�����Ƶĵ�i������
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
    PreciseNumber10 sum, coefficient,t; // �ܺ͡�ϵ������ʱ��
    int index;//ָ��
    PreciseNumberInit10(&sum);

    
    char a;             // ���ڽ����ַ�
    StackInit(char, 1); // ���ڴ��ַ���ջ
    while (1)
    {
        // ����ϵ����������
        PreciseNumberInit10(&coefficient); // ˢ��ϵ��Ϊ0
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
            printf("����Ƿ�\n");
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
                printf("����Ƿ�\n");
                exit(-1);
            }
        }
        int i = coefficient.precison - 4;
        while (i < coefficient.precison && StackGetLength(1) != 0) // С����ǰ��ʮλδ������ջ�л���ʣ�������
        {
            StackPop(a, 1);                   // ��a����������ջ���ַ�
            coefficient.number[i] = atoi(&a); // ���ַ�תΪ���ֲ�д��߾�����
            i++;
        }
        // ����ϵ��С������
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
                break; // ������һ�׶�
            else
            {
                printf("����Ƿ�\n");
                exit(-1);
            }
        }
        // ����ָ������
        a = getchar();
        if (a != 'x')//���Ϸ���
        {
            printf("����Ƿ�\n");
            exit(-1);
        }
        a = getchar();
        if (a != '^')//���Ϸ���
        {
            printf("����Ƿ�\n");
            exit(-1);
        }
        a = getchar();
        if(isdigit(a))
        {
            index = atoi(&a);
        }
        else
        {
            printf("����Ƿ�\n");
            exit(-1);
        }
        //�����ܺ�
        PreciseNumberInit10(&t);
            t.number[PRECISION] = 1;
        for(int i = 0;i<index;i++)//x^index
        {
            PreciseNumberMul10(&t,t,x);
        }
        PreciseNumberMul10(&t,t,coefficient);
        PreciseNumberAdd10(&sum,sum,t);
    }
    //��ӡ���
    PreciseNumberPrint10(&sum);
}