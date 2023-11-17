#ifndef SSTRING_H
#define SSTRING_H
#include <stdio.h>

typedef struct string
{
    int length;//当前已存字符数量(不包括\0）
    int volume;//最大字符容量(\0也占容量)
    char * phead;//指向字符串的起始位置
}string;

void StringInit(string * pstring);
void StringInput(string * pstring,char * pstr_input);
void StringPrint(string * pstring);
void StringGetSubstring(string * pstring1,string * pstring2,int startposition,int sublength);
void StringClear(string * pstring);
void KMPnextval(char *str, int *nextval);
int StringPatternMatching(string *pstring, char *pstr_input);
void StringReplace(string *pstring, char *str_tobe_replace,char* str_to_replace);
#define StringGetLength(string) (string.length)

#endif