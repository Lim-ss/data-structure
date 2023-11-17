#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sstring.h"
#define INIT_VOLUME 50 // ��ʼ������

void StringInit(string *pstring)
{
    pstring->phead = (char *)malloc(sizeof(char) * INIT_VOLUME); // Ĭ�ϳ�ʼ����50�ֽ��ڴ�
    if (pstring->phead == NULL)                                  // ����ʧ��
    {
        printf("malloc failure\n");
        exit(-1);
    }
    pstring->length = 0;
    pstring->volume = INIT_VOLUME;
}

void StringInput(string *pstring, char *pstr_input)
{
    /*�����ṹstringĩβƴ��str�ַ���*/
    int length_input = strlen(pstr_input);                    // ������\0
    if (pstring->length + length_input + 1 > pstring->volume) // ƴ�Ӻ󳤶ȳ��������������·���
    {
        pstring->phead = (char *)realloc(pstring->phead, sizeof(char) * (pstring->length + length_input + 1));
        if (pstring->phead == NULL) // �������Ƿ�ɹ�
        {
            printf("realloc failure\n");
            exit(-1);
        }
        pstring->volume = pstring->length + length_input + 1;
    }
    for (int i = 0; i < length_input; i++) // ƴ��
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
        ��string2�д�ָ��λ�ó�ȡָ�������ִ���ƴ����string1β��
        ��string1��string2Ϊͬһ��ʱ����������»�����⣨�ִ�ȡ�����һ���ַ�����Ӧ����ʹ��
    */
    if (startposition >= 0 && sublength > 0 && (startposition + sublength) <= pstring2->length) // �жϲ����Ϸ���
    {
        char temp = *(pstring2->phead + startposition + sublength); // �ݴ�Ŀ���Ӵ���ĵ�һ���ַ����Ա㻻��\0���ܹ���ԭ
        *(pstring2->phead + startposition + sublength) = '\0';      // ���ִ�����ضϣ��������StringInput����
        StringInput(pstring1, pstring2->phead + startposition);
        *(pstring2->phead + startposition + sublength) = temp; // ��ԭstring2
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
        ��մ�
    */
    pstring->length = 0;
    *(pstring->phead) = '\0';
    return;
}

int StringPatternMatching(string *pstring, char *pstr_input)
{
    /*
        ���ص�ƥ��λ�ô�0��ʼ       
    */
    int i=0,j=0;//�ֱ�Ϊ������ģʽ����λ��
    int length1 = pstring->length;//��������
    int length2 = strlen(pstr_input);//ģʽ������
    int * nextval = (int *)malloc(sizeof(int)*length2);
    if(nextval == NULL)
    {
        printf("nextval malloc failure\n");
        exit(-1);
    }
    KMPnextval(pstr_input,nextval);
    while(i < length1)
    {
        //printf("ƥ����̲���: i = %d,j = %d\n",i,j);
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
        if(j == length2)//˵������ģʽ��ƥ��ɹ�
        {
            return (i - length2);
        }
    }
    //ѭ��������δ�˳�������˵��ƥ��ʧ��
    return -1;
}

void KMPnextval(char *str, int *nextval)
{
    /*
        ��ģʽ����next���飬�������ʱ�뱣֤next������ڵ���str�ĳ���
    */
    int length = strlen(str); // ������\0
    int L;                    // ���ڲ������Ӵ��ĳ��ȣ�Ŀ��λ��֮ǰ���ַ�����
    nextval[0] = -1;
    int i,j,k;
    for (i = 1; i < length; i++) // ���ÿ���Ӧһ��next�����Ԫ�أ�������0���ӵ�1����ʼ��
    {
        L = i;
        nextval[i] = 0;
        for (j = 0; j < L - 1; j++) // �в�ÿ��ѭ����Ӧһ��ͷβ�Ӵ��ıȽϣ��������ʼ�Ƚϣ�
        {
            for (k = 0; k < L - j - 1; k++) // �ڲ�ÿ��ѭ����Ӧһ���ַ��ıȽ�
            {
                //printf("test,str[k]=%c,str[k+j+1]=%c\n",str[k],str[k + j + 1]);
                if(str[k] != str[k + j + 1])
                break;//�����һ����ĸ������ȣ��˳��ڲ�ѭ��
            }
            if(k == L - j - 1)//����������ڴ�ѭ�����ɹ����Ӵ��ɹ�ƥ��
            {
                //printf("������if��֧,k=%d,L=%d,j=%d\n",k,L,j);
                nextval[i] = L - 1 - j;
                break;//�Ѿ��ҵ����ƥ����ִ�,ȷ����next[i]�ˣ��˳��в�ѭ��
            }
        }
    }
    //������nextval�����ֵ���Ѿ���next��
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
    string newstring,newtail,string_tobe_replace;//newtailΪ�ݹ�ʱ���滻����һ��ƥ�䴮��ĩβ��Ӧ�ý��ϵ��´�
    StringInit(&newstring);
    StringInit(&newtail);
    StringInit(&string_tobe_replace);
    StringInput(&string_tobe_replace,str_tobe_replace);
    int length_of_str_tobe_replace = strlen(str_tobe_replace);
    int position;
    position = StringPatternMatching(pstring,str_tobe_replace);
    printf("Ŀǰ������Ϊ��");
    printf("�ɹ�ƥ���λ��=%d\n",position);
    StringPrint(pstring);
    if(position == -1)
    {
        //û��ƥ��Σ�ֱ�ӷ���
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
        StringInput(&newtail,pstring->phead + position + length_of_str_tobe_replace);//newtail������Ȼ�Ǿɵ�tail
        StringReplace(&newtail,str_tobe_replace,str_to_replace);//����β�͵ݹ��滻Ϊ��β��
        StringInput(&newstring,newtail.phead);//������β��
        StringClear(pstring);
        *pstring = newstring;
    }
    return;
}