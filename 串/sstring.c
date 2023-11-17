#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sstring.h"
#define INIT_VOLUME 50 // 初始串容量

void StringInit(string *pstring)
{
    pstring->phead = (char *)malloc(sizeof(char) * INIT_VOLUME); // 默认初始分配50字节内存
    if (pstring->phead == NULL)                                  // 分配失败
    {
        printf("malloc failure\n");
        exit(-1);
    }
    pstring->length = 0;
    pstring->volume = INIT_VOLUME;
}

void StringInput(string *pstring, char *pstr_input)
{
    /*往串结构string末尾拼接str字符串*/
    int length_input = strlen(pstr_input);                    // 不包括\0
    if (pstring->length + length_input + 1 > pstring->volume) // 拼接后长度超过容量，需重新分配
    {
        pstring->phead = (char *)realloc(pstring->phead, sizeof(char) * (pstring->length + length_input + 1));
        if (pstring->phead == NULL) // 检查分配是否成功
        {
            printf("realloc failure\n");
            exit(-1);
        }
        pstring->volume = pstring->length + length_input + 1;
    }
    for (int i = 0; i < length_input; i++) // 拼接
    {
        *(pstring->phead + pstring->length + i) = *(pstr_input + i);
    }
    *(pstring->phead + pstring->length + length_input) = '\0';
    pstring->length += length_input;
}

void StringPrint(string *pstring)
{
    printf("%s", pstring->phead);
    printf("\n");
}

void StringGetSubstring(string *pstring1, string *pstring2, int startposition, int sublength)
{
    /*
        将string2中从指定位置抽取指定长度字串，拼接在string1尾部
        当string1与string2为同一个时，极端情况下会出问题（字串取到最后一个字符），应避免使用
    */
    if (startposition >= 0 && sublength > 0 && (startposition + sublength) <= pstring2->length) // 判断操作合法性
    {
        char temp = *(pstring2->phead + startposition + sublength); // 暂存目标子串后的第一个字符，以便换成\0后能够还原
        *(pstring2->phead + startposition + sublength) = '\0';      // 将字串后面截断，方便调用StringInput函数
        StringInput(pstring1, pstring2->phead + startposition);
        *(pstring2->phead + startposition + sublength) = temp; // 还原string2
    }
    else
    {
        printf("get substr failure\n");
    }
    return;
}

void StringClear(string *pstring)
{
    /*
        清空串
    */
    pstring->length = 0;
    *(pstring->phead) = '\0';
    return;
}

int StringPatternMatching(string *pstring, char *pstr_input)
{
    /*
        返回的匹配位置从0开始       
    */
    int i=0,j=0;//分别为主串和模式串的位置
    int length1 = pstring->length;//主串长度
    int length2 = strlen(pstr_input);//模式串长度
    int * nextval = (int *)malloc(sizeof(int)*length2);
    if(nextval == NULL)
    {
        printf("nextval malloc failure\n");
        exit(-1);
    }
    KMPnextval(pstr_input,nextval);
    while(i < length1)
    {
        //printf("匹配过程测试: i = %d,j = %d\n",i,j);
        if(*(pstring->phead + i) == pstr_input[j])
        {
            i++;
            j++;
        }
        else
        {
            if(nextval[j] == -1)
            {
                i++;
                j = 0;
            }
            else
            {
                j = nextval[j];
            }
        }
        if(j == length2)//说明整个模式串匹配成功
        {
            return (i - length2);
        }
    }
    //循环结束仍未退出函数，说明匹配失败
    return -1;
}

void KMPnextval(char *str, int *nextval)
{
    /*
        求模式串的next数组，传入参数时请保证next数组大于等于str的长度
    */
    int length = strlen(str); // 不包括\0
    int L;                    // 正在操作的子串的长度（目标位置之前的字符数）
    nextval[0] = -1;
    int i,j,k;
    for (i = 1; i < length; i++) // 外层每层对应一个next数组的元素，跳过第0个从第1个开始求
    {
        L = i;
        nextval[i] = 0;
        for (j = 0; j < L - 1; j++) // 中层每层循环对应一对头尾子串的比较（从最长串开始比较）
        {
            for (k = 0; k < L - j - 1; k++) // 内层每层循环对应一个字符的比较
            {
                //printf("test,str[k]=%c,str[k+j+1]=%c\n",str[k],str[k + j + 1]);
                if(str[k] != str[k + j + 1])
                break;//如果有一个字母符不相等，退出内层循环
            }
            if(k == L - j - 1)//完整完成了内存循环，成功两子串成功匹配
            {
                //printf("进入了if分支,k=%d,L=%d,j=%d\n",k,L,j);
                nextval[i] = L - 1 - j;
                break;//已经找到最长的匹配的字串,确定了next[i]了，退出中层循环
            }
        }
    }
    //到这里nextval里面的值就已经是next了
    for(i = 1;i < length;i++)
    {
        if(str[i] == str[nextval[i]])
        {
            nextval[i] = nextval[nextval[i]];
        }
    }
}

void StringReplace(string *pstring, char *str_tobe_replace,char* str_to_replace)
{
    string newstring,newtail,string_tobe_replace;//newtail为递归时，替换掉第一个匹配串后，末尾还应该接上的新串
    StringInit(&newstring);
    StringInit(&newtail);
    StringInit(&string_tobe_replace);
    StringInput(&string_tobe_replace,str_tobe_replace);
    int length_of_str_tobe_replace = strlen(str_tobe_replace);
    int position;
    position = StringPatternMatching(pstring,str_tobe_replace);
    printf("目前的主串为：");
    printf("成功匹配的位置=%d\n",position);
    StringPrint(pstring);
    if(position == -1)
    {
        //没有匹配段，直接返回
        return;
    }
    else
    {
        /*
        StringGetSubstring(&newstring,pstring,0,position);
        StringInput(&newstring,str_to_replace);
        StringInput(&newstring,pstring->phead + position + length_of_str_to_replace);
        StringClear(pstring);
        *pstring = newstring;
        StringReplace(pstring,str_tobe_replace,str_to_replace);
        */
        StringGetSubstring(&newstring,pstring,0,position);
        StringInput(&newstring,str_to_replace);
        StringInput(&newtail,pstring->phead + position + length_of_str_tobe_replace);//newtail现在仍然是旧的tail
        StringReplace(&newtail,str_tobe_replace,str_to_replace);//将旧尾巴递归替换为新尾巴
        StringInput(&newstring,newtail.phead);//接上新尾巴
        StringClear(pstring);
        *pstring = newstring;
    }
    return;
}