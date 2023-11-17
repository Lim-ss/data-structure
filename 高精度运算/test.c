#include<stdio.h>
#include "high_precision.h"
int main()
{
    PreciseNumber2 a;
    PreciseNumber2 b;
    PreciseNumber2 c;
    PreciseNumber10 d1,d2,d3;
    PreciseNumberInit2(&a);
    PreciseNumberInit2(&b);
    PreciseNumberInit2(&c);
    PreciseNumberInit10(&d1);
    PreciseNumberInit10(&d2);
    PreciseNumberInit10(&d3);
    //PreciseNumberInput(&a);
    //PreciseNumberPrint(&a);
    //PreciseNumberInput(&b);
    //PreciseNumberPrint(&b);
    //PreciseNumberAdd(&c,&a,&b);
    //PreciseNumberMul(&c,&a,&b);
    //乘法测试
   // PreciseNumberInput10(&d1);
    //PreciseNumberInput10(&d2);
    //PreciseNumberMul10(&d3,d1,d2);
    //PreciseNumberPrint10(&d3);
    //PreciseNumberInput10(&d3);
    //进制转换
    //PreciseNumber10toN(d3,18);
    //PreciseNumber10to2(&a,d);
    //PreciseNumberPrint2(&a);
    
    //多项式测试
    PreciseNumberInput10(&d1);
    PreciseNumberPolynomial(d1);
    return 0;

}