#include "string.h"

size_t strlen(const char* str){
    size_t size = 0;
    while(str[size]){
        ++size;
    }
    return size;
}

size_t strnlen(const char* s, size_t maxlen) {
    size_t len = 0;
    while (len < maxlen && s[len] != '\0') {
        len++;
    }
    return len;
}

bool isdigit(char c){
    return c >= 48 && c <= 57;
}

int toNumericDigit(char c){
    return c - 48;
}

void* strcpy(char* dest, const char* src){
    char* res = dest;
    while(*src != 0){
        *dest = *src;
        src +=  1;
        dest += 1;
    }
    *dest = 0x00;
    return res;
}

void* strncpy(char* dest, const char* src, size_t maxlen) {
    if (maxlen == 0) return dest;

    size_t i = 0;
    for (; i < maxlen - 1 && src[i]; ++i)
        dest[i] = src[i];

    dest[i] = '\0';

    return dest;
}

char tolower(char ch){
    if(ch >= 65 && ch <= 90){
        ch += 32;
    }
    return ch;
}

int strcmp(const char* str1, const char* str2){
    while(*str1 && (*str1 == *str2)){
        str1++;
        str2++;
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
}

int istrcmp(const char* str1, const char* str2){
    while(*str1 && *str2 && ((*str1 == *str2) || (tolower(*str1) == tolower(*str2)))){
        str1++;
        str2++;
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
}

int strncmp(const char* str1, const char* str2, size_t len){
    unsigned char u1, u2;
    while(len --> 0){
        u1 = (unsigned char)*str1++;
        u2 = (unsigned char)*str2++;

        if(u1 != u2){
            return u1 - u2;
        }

        if(u1 == '\0'){
            return 0;
        }
    }
    return 0;
}

int istrncmp(const char* str1, const char* str2, size_t len){
    unsigned char u1, u2;
    while(len --> 0){
        u1 = (unsigned char)*str1++;
        u2 = (unsigned char)*str2++;

        if(u1 != u2 && tolower(u1) != tolower(u2)){
            return (unsigned char)tolower(u1) - (unsigned char)tolower(u2);
        }

        if(u1 == '\0'){
            return 0;
        }
    }
    return 0;
}

int strnlen_terminator(const char* str, int max, char terminator){
    int i; 
    for(i=0; i<max; i++){
        if(str[i] == '\0' || str[i] == terminator){
            break;
        }
    }
    return i;
}


char* sp = 0;
char* strtok(char* str, const char* delimiters)
{
    int i = 0;
    int len = strlen(delimiters);
    if (!str && !sp)
        return 0;
    
    if (str && !sp)
    {
        sp = str;
    }

    char* p_start = sp;
    while(1)
    {
        for (i = 0; i < len; i++)
        {
            if(*p_start == delimiters[i])
            {
                p_start++;
                break;
            }
        }

        if (i == len)
        {
            sp = p_start;
            break;
        }
    }

    if (*sp == '\0')
    {
        sp = 0;
        return sp;
    }

    while(*sp != '\0')
    {
        for (i = 0; i < len; i++)
        {
            if (*sp == delimiters[i])
            {
                *sp = '\0';
                break;
            }
        }

        sp++;
        if (i < len)
            break;
    }

    return p_start;
}