#include "io/io.h"
#include "kernel.h"
#include <stdint.h>
#include <stddef.h>
#include "config.h"
#include "status.h"
#include "gdt/gdt.h"
#include "fs/file.h"
#include "idt/idt.h"
#include "task/tss.h"
#include "disk/disk.h"
#include "task/task.h"
#include "fs/pparser.h"
#include "task/process.h"
#include "string/string.h"
#include "memory/memory.h"
#include "isr80h/isr80h.h"
#include "memory/heap/kheap.h"
#include "disk/diskstreamer.h"
#include "keyboard/keyboard.h"
#include "memory/paging/paging.h"

#define WHITE_COLOR 15

uint16_t *video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;
struct paging_4gb_chunk* kernel_chunk = 0;

uint16_t terminal_make_char(char c, char color){
    return (color << 8 ) | c;
}

void terminal_putchar(int x, int y, char c, char color){
    video_mem[y * VGA_WIDTH + x] = terminal_make_char(c,color);
}

void terminal_backspace(){
    if(terminal_row == 0 && terminal_col == 0){
        return ;
    }

    if(terminal_col == 0){
        terminal_row -= 1;
        terminal_col = VGA_WIDTH;
    }

    terminal_col -= 1;
    terminal_writechar(' ',WHITE_COLOR);
    terminal_col -=1;
}

void terminal_writechar(char c, char color){
    if (c == '\n'){
        ++terminal_row;
        terminal_col = 0;
        return ;
    }

    if(c == 0x08){
        terminal_backspace();
        return;
    }
    terminal_putchar(terminal_col, terminal_row, c, color);
    ++terminal_col;

    if(terminal_col >= VGA_WIDTH){
        terminal_col = 0;
        ++terminal_row;
    }
}

void terminal_initialize(){
    terminal_row = 0;
    terminal_col = 0;
    video_mem = (uint16_t*) (0xB8000);
    for (int i=0; i< VGA_HEIGHT; i++){
        for (int j=0; j<VGA_WIDTH; j++){
            terminal_putchar(j,i,' ',0);
        }
    }
}

void print(const char *str){
    size_t strLen = strlen(str);

    for(int i=0; i< strLen; i++){
        terminal_writechar(str[i],WHITE_COLOR);
    }
}

void print_int(int num) {
    if (num == 0) {
        terminal_writechar('0', WHITE_COLOR);
        return;
    }
    
    if (num < 0) {
        terminal_writechar('-', WHITE_COLOR);
        num = -num;
    }
    char buffer[12]; 
    int i = 0;
    
    while (num > 0) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }
    
    for (int j = i - 1; j >= 0; j--) {
        terminal_writechar(buffer[j], WHITE_COLOR);
    }
}

void print_hex(uint32_t num) {
    terminal_writechar('0', WHITE_COLOR);
    terminal_writechar('x', WHITE_COLOR);
    
    if (num == 0) {
        terminal_writechar('0', WHITE_COLOR);
        return;
    }
    
    char hex_chars[] = "0123456789ABCDEF";
    char buffer[9]; 
    int i = 0;
    
    while (num > 0) {
        buffer[i++] = hex_chars[num % 16];
        num /= 16;
    }
    
    for (int j = i - 1; j >= 0; j--) {
        terminal_writechar(buffer[j], WHITE_COLOR);
    }
}

void panic(const char* msg){
    print(msg);
    while(1){}
}

void kernel_page(){
    kernel_registers();
    paging_switch(kernel_chunk);
}

struct TSS tss;
struct gdt gdt_real[PEACHOS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[PEACHOS_TOTAL_GDT_SEGMENTS] = {
    {.base = 0x00, .limit = 0x00, .type = 0x00},                
    {.base = 0x00, .limit = 0xffffffff, .type = 0x9a},           
    {.base = 0x00, .limit = 0xffffffff, .type = 0x92},            
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf8},              
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf2},             
    {.base = (uint32_t)&tss, .limit=sizeof(tss), .type = 0xE9}      
};

void kernel_main(){
    terminal_initialize();

    memset(gdt_real,0,sizeof(gdt_real));
    gdt_structured_to_gdt(gdt_real,gdt_structured,PEACHOS_TOTAL_GDT_SEGMENTS);

    gdt_load(gdt_real,sizeof(gdt_real)-1);

    kheap_init();
    
    fs_init();
    
    disk_search_and_init();
    
    idt_init();
    
    memset(&tss, 0x00, sizeof(tss));
    tss.esp0 = 0x600000;
    tss.ss0 = KERNEL_DATA_SELECTOR;
    
    tss_load(0x28);

    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    paging_switch(kernel_chunk);
    enable_paging();
    
    isr80h_register_commands();
    keyboard_init();
    
    struct process* process;
    int res = process_load_switch("0:/blank.elf",&process);
    if(res != PEACHOS_ALL_OK){
        panic(
            "Failed to load blank.elf!\n"
        );
    }

    struct command_argument argument;
    strcpy(argument.argument,"Testing!");
    argument.next = 0x00;

    process_inject_arguments(process,&argument);

      res = process_load_switch("0:/blank.elf", &process);
    if (res != PEACHOS_ALL_OK)
    {
        panic("Failed to load blank.elf\n");
    }

    strcpy(argument.argument, "Abc!");
    argument.next = 0x00; 
    process_inject_arguments(process, &argument);

    task_run_first_ever_task();
    while(1){}
}
