#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void* memset(void *ptr, int c, size_t size);
int memcmp(char*,char*,size_t);
void* memcpy(void* dest, void* src, int len);

#endif