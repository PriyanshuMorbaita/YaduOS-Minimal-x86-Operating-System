#ifndef KERNEL_H
#define KERNEL_H
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 20

#define PEACHOS_MAX_PATH 108

void print(const char *str);
void kernel_main();
void kernel_page();
void print_int(int num);
void print_hex(uint32_t num);
void kernel_registers();
void panic(const char* msg);
void terminal_writechar(char c, char color);

#define ERROR(value) (void*)(value)
#define ERROR_I(value) (int)(value)
#define ISERR(value) ((int)value<0)

#endif