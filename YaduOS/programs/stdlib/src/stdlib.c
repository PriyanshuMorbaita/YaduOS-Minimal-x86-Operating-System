#include "stdlib.h"
#include "peachos.h"

char* itoa(int num)
{
    static char text[12];
    int loc = 11;
    text[11] = 0;
    char neg = 1;
    if (num >= 0)
    {
        neg = 0;
        num = -num;
    }

    while(num)
    {
        text[--loc] = '0' - (num % 10);
        num /= 10;
    }

    if (loc == 11)
        text[--loc] = '0';
    
    if (neg)
        text[--loc] = '-';

    return &text[loc];
}

void* malloc(size_t size){
    return peachos_malloc(size);
}

void free(void* ptr){
    return peachos_free(ptr);
}