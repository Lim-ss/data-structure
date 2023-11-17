#include <stdio.h>
#include <string.h>
#include "sstring.h"
int main()
{
    /*
    ����strlen�Ĺ��ܣ����Ϊ������\0
    char str[10] = {'a','b','c','\0'};
    int length = strlen(str);
    printf("%d",length);
    */

   //��ʼ��
    string str1,str2;
    StringInit(&str1);
    StringInit(&str2);

    //����ƴ��
    printf("\n����ƴ��:\n");
    StringInput(&str1,"abcd");//��ʱstr1Ϊabcd
    StringPrint(&str1);
    StringInput(&str1,"89naab");//��ʱstr1Ϊabcd89naab
    StringPrint(&str1);

    //�����󳤶�
    printf("\n�����󳤶�:\n");
    printf("str1����:%d\n",StringGetLength(str1));//��ʱstr1����Ϊ10

    //�������Ӵ�
    printf("\n�������Ӵ�:\n");
    StringGetSubstring(&str2,&str1,2,4);//��ʱstr2Ϊcd89
    StringPrint(&str2);
    StringGetSubstring(&str2,&str1,5,5);//��ʱstr2Ϊcd899naab
    StringPrint(&str2);

    //������մ�
    printf("\n������մ�:\n");
    StringClear(&str2);
    StringPrint(&str2);
    printf("str2����:%d\n",StringGetLength(str2));//��ʱstr1����Ϊ0

    //����KMP��next�㷨
    printf("\n����KMP��nextval�㷨:\n");
    //char p[20] = "abcabaa";
    char p[20] = "abcaabbabcab";
    int next[20];
    KMPnextval(p,next);
    for(int i = 0;i < 12;i++)
    {
        printf("nextval[%d]=%d\n",i,next[i]);
    }

    //����KMP�㷨
    printf("\n����KMP�㷨:\n");
    StringInput(&str2,"acabaabaabcacaabc");//��ʱstr2Ϊacabaabaabcacaabc
    int position = StringPatternMatching(&str2,"abaabcac");
    printf("position = %d\n",position);

    //�����滻�㷨
    printf("\n�����滻�㷨:\n");
    StringClear(&str2);
    StringInput(&str2,"abaabababa");
    StringReplace(&str2,"aba","ba");
    StringPrint(&str2);
    
}