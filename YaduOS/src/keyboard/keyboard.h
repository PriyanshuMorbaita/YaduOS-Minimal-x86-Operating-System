#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "task/task.h"
#include "task/process.h"
#include "classic.h"

#define KEYBOARD_CAPS_LOCK_OFF 0
#define KEYBOARD_CAPS_LOCK_ON 1

typedef int KEYBOARD_CAPS_LOCK_STATE;

typedef int (*KEYBOARD_INIT_FUNCTION)();

struct keyboard{
    KEYBOARD_INIT_FUNCTION init;
    char name[20];
    KEYBOARD_CAPS_LOCK_STATE capslock_state;
    struct keyboard* next;
};

void keyboard_init();
char keyboard_pop();
int keyboard_insert(struct keyboard* keyboard);
void keyboard_push(const char ch);
void keyboard_backspace(struct process* process);
void keyboard_set_capslock(struct keyboard* keyboard, KEYBOARD_CAPS_LOCK_STATE state);
KEYBOARD_CAPS_LOCK_STATE keyboard_get_capslock(struct keyboard* keyboard);
#endif