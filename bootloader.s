BITS 64
section .text
    global bootloader

bootloader:
    ; Write message to console
    mov eax, 4          ; sys_write system call number
    mov ebx, 1          ; stdout file descriptor
    mov ecx, message    ; address of message string
    mov edx, 13         ; length of message
    int 0x80           ; invoke Linux system call
    ; Return from function
    ret

section .data
    message db "....WOODY....", 13