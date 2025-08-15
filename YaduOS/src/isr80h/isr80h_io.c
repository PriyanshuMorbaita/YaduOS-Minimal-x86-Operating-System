#include "isr80h_io.h"
#include "kernel.h"
#include "task/task.h"
#include "keyboard/keyboard.h"

void* isr80h_command1_print(struct interrupt_frame* frame){
    void* user_space_msg_buffer = task_get_stack_item(task_current(),0);
    char buf[1024];
    copy_string_from_task(task_current(),user_space_msg_buffer,buf,sizeof(buf));
    print(buf);
    return 0;
}

void* isr80h_command2_getkey(struct interrupt_frame* frame){
    char ch = keyboard_pop();
    return (void*)((int)ch);
}

void* isr80h_command3_putchar(struct interrupt_frame* frame){
    char ch = (char)(int) task_get_stack_item(task_current(),0);
    terminal_writechar(ch,COLOR_WHITE);
    return 0;
}