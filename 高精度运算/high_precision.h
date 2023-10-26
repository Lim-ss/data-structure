#ifndef  HIGH_PRECISION
#define HIGH_PRECISION
#include<stdio.h>
#define PRECISION 200

typedef struct PreciseNumber2
{
    int number[PRECISION + 10];//数组从前往后分别存储低位到高位，其中，小数点前的共10位排在末尾
    int signbit;//符号位，0代表正值，1代表负值
    int precison;//有几位二进制数,和宏里面那个PRECISION不是同一个值
}PreciseNumber2;

typedef struct PreciseNumber10
{
    int number[PRECISION + 4];//数组从前往后分别存储低位到高位，其中，小数点前的共10位排在末尾
    int signbit;//符号位，0代表正值，1代表负值
    int precison;//有几位二进制数,和宏里面那个PRECISION不是同一个值
}PreciseNumber10;

void PreciseNumberInit2(PreciseNumber2 * pcsnum);
void PreciseNumberInit10(PreciseNumber10 * pcsnum);
void PreciseNumberPrint2(PreciseNumber2 *pcsnum);
void PreciseNumberPrint10(PreciseNumber10 *pcsnum);
void PreciseNumberInput2(PreciseNumber2 *pcsnum);
void PreciseNumberInput10(PreciseNumber10 *pcsnum);
void PreciseNumberAdd2(PreciseNumber2 * pcsnum1,PreciseNumber2 * pcsnum2,PreciseNumber2 * pcsnum3);
void PreciseNumberAdd10(PreciseNumber10 * pcsnum1,PreciseNumber10 pcsnum2,PreciseNumber10 pcsnum3);
void PreciseNumberSub10(PreciseNumber10 * pcsnum1,PreciseNumber10 pcsnum2,PreciseNumber10 pcsnum3);
void PreciseNumberMul2(PreciseNumber2 * pcsnum1,PreciseNumber2 * pcsnum2,PreciseNumber2 * pcsnum3);
void PreciseNumberMul10(PreciseNumber10 * pcsnum1,PreciseNumber10 pcsnum2,PreciseNumber10 pcsnum3);
void PreciseNumber10to2(PreciseNumber2 *pcsnum1, PreciseNumber10 pcsnum2);
void PreciseNumber10toN(PreciseNumber10 pcsnum2,int N);
void PreciseNumberPolynomial(PreciseNumber10 x);
#endif