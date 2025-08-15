[BITS 32]

section .asm

global print:function 
global peachos_getkey:function 
global peachos_malloc:function
global peachos_free:function
global peachos_putchar:function
global peachos_process_load_start:function
global peachos_process_get_arguments:function
global peachos_system:function
global peachos_exit:function

peachos_exit:
    push ebp
    mov ebp, esp
    mov eax, 0
    int 0x80
    pop ebp
    ret

print:
    push ebp
    mov ebp, esp
    push dword[ebp+8]
    mov eax,1
    int 0x80
    add esp,4
    pop ebp
    ret

peachos_getkey:
    push ebp
    mov ebp,esp
    mov eax,2
    int 0x80
    pop ebp
    ret

peachos_putchar:
    push ebp
    mov ebp,esp
    mov eax,3
    push dword[ebp+8]
    int 0x80
    add esp,4
    pop ebp
    ret

peachos_malloc:
    push ebp
    mov ebp, esp
    mov eax,4
    push dword[ebp+8]
    int 0x80
    add esp,4
    pop ebp
    ret

peachos_free:
    push ebp
    mov ebp, esp
    mov eax, 5
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret

peachos_process_load_start:
    push ebp
    mov ebp, esp
    mov eax, 6
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret


peachos_system:
    push ebp
    mov ebp, esp
    mov eax, 7
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret

peachos_process_get_arguments:
    push ebp
    mov ebp, esp
    mov eax, 8
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret
