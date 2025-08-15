#include "keyboard.h"
#include "status.h"
#include "kernel.h"

static struct keyboard* keyboard_list_head = 0;
static struct keyboard* keyboard_list_last = 0;

void keyboard_init(){
    keyboard_insert(classic_init());
}

int keyboard_insert(struct keyboard* keyboard){
    int res = 0;
    if(keyboard->init == 0){
        res = -EINVARG;
        goto out;
    }

    if(keyboard_list_last){
        keyboard_list_last->next = keyboard;
        keyboard_list_last = keyboard;
    }else{
        keyboard_list_head = keyboard;
        keyboard_list_last = keyboard;
    }

    res = keyboard->init();
out:
    return res;
}

static int keyboard_get_tail_index(struct process* process){
    return process->keyboard.tail % sizeof(process->keyboard.buffer);
}

static int keyboard_get_head_index(struct process* process){
    return process->keyboard.head % sizeof(process->keyboard.buffer);
}

void keyboard_backspace(struct process* process){
    process->keyboard.tail -= 1;
    int real_index = keyboard_get_tail_index(process);
    process->keyboard.buffer[real_index] = 0x00;
}

void keyboard_push(const char ch){
    struct process* process = process_current();
    if(!process){
        return;
    }

    if(ch == 0){
        return;
    }
    
    int real_index = keyboard_get_tail_index(process);
    process->keyboard.buffer[real_index] = ch;
    process->keyboard.tail++;

    return;
}

char keyboard_pop(){
    if(!task_current()){
        return 0;
    }

    struct process* process = task_current()->process;
    int real_index = keyboard_get_head_index(process);
    char ch = process->keyboard.buffer[real_index];
    if(ch == 0x00){
        return 0;
    }

    process->keyboard.buffer[real_index] = 0;
    process->keyboard.head++;
    return ch;
}

void keyboard_set_capslock(struct keyboard* keyboard, KEYBOARD_CAPS_LOCK_STATE state){
    keyboard->capslock_state = state;
}

KEYBOARD_CAPS_LOCK_STATE keyboard_get_capslock(struct keyboard* keyboard){
    return keyboard->capslock_state;
}