#include "memory.h"

void* memset(void* ptr, int c, size_t size){
    char* c_ptr = (char*)ptr;
    for(int i=0; i<size; i++){
        c_ptr[i] = c;
    }
    return ptr;
}

int memcmp(char* s1,char* s2, size_t count){
    unsigned char* c1 = (unsigned char*) s1;
    unsigned char* c2 = (unsigned char*) s2;
    
    while(count-- > 0){
        if(*c1 != *c2){
            return *c1 - *c2;
        }
        c1++;
        c2++;
    }

    return 0;
}

void* memcpy(void* dest, void* src, int len)
{
    char *d = dest;
    char *s = src;
    while(len--)
    {
        *d++ = *s++;
    }
    return dest;
}