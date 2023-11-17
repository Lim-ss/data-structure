#include <stdio.h>
#include <string.h>
#include "sstring.h"
int main()
{
    /*
    测试strlen的功能，结果为不包括\0
    char str[10] = {'a','b','c','\0'};
    int length = strlen(str);
    printf("%d",length);
    */

   //初始化
    string str1,str2;
    StringInit(&str1);
    StringInit(&str2);

    //测试拼接
    printf("\n测试拼接:\n");
    StringInput(&str1,"abcd");//此时str1为abcd
    StringPrint(&str1);
    StringInput(&str1,"89naab");//此时str1为abcd89naab
    StringPrint(&str1);

    //测试求长度
    printf("\n测试求长度:\n");
    printf("str1长度:%d\n",StringGetLength(str1));//此时str1长度为10

    //测试求子串
    printf("\n测试求子串:\n");
    StringGetSubstring(&str2,&str1,2,4);//此时str2为cd89
    StringPrint(&str2);
    StringGetSubstring(&str2,&str1,5,5);//此时str2为cd899naab
    StringPrint(&str2);

    //测试清空串
    printf("\n测试清空串:\n");
    StringClear(&str2);
    StringPrint(&str2);
    printf("str2长度:%d\n",StringGetLength(str2));//此时str1长度为0

    //测试KMP的next算法
    printf("\n测试KMP的nextval算法:\n");
    //char p[20] = "abcabaa";
    char p[20] = "abcaabbabcab";
    int next[20];
    KMPnextval(p,next);
    for(int i = 0;i < 12;i++)
    {
        printf("nextval[%d]=%d\n",i,next[i]);
    }

    //测试KMP算法
    printf("\n测试KMP算法:\n");
    StringInput(&str2,"acabaabaabcacaabc");//此时str2为acabaabaabcacaabc
    int position = StringPatternMatching(&str2,"abaabcac");
    printf("position = %d\n",position);

    //测试替换算法
    printf("\n测试替换算法:\n");
    StringClear(&str2);
    StringInput(&str2,"abaabababa");
    StringReplace(&str2,"aba","ba");
    StringPrint(&str2);
    
}