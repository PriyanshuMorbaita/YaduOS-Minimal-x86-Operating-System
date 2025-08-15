#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

size_t strlen(const char*);
bool isdigit(char c);
int toNumericDigit(char);
void* strcpy(char* dest, const char* src);
size_t strnlen(const char*,size_t);
int strcmp(const char* str1, const char* str2);
int strncmp(const char* st1, const char* str2, size_t len);
char tolower(char ch);
int istrcmp(const char* str1, const char* str2);
int istrncmp(const char* str1, const char* str2, size_t len);
int strnlen_terminator(const char* str, int max, char terminator);
void* strncpy(char* dest, const char* src, size_t maxlen);

#endif