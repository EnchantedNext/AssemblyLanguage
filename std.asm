.intel_syntax noprefix
.global _start

_start:
    // write prompt
    mov rax, 1
    mov rdi, 1
    lea rsi, [prompt]
    mov rdx, 19
    syscall

    // read stdin
    mov rax, 0
    mov rdi, 0
    lea rsi, [name]
    mov rdx, 9
    syscall
    mov [bytes], rax
    mov rax, [bytes]
    dec rax
    mov [bytes], rax

    // write "Hello, "
    mov rax, 1
    mov rdi, 1
    lea rsi, [msg]
    mov rdx, 7
    syscall

    // write name
    mov rax, 1
    mov rdi, 1
    lea rsi, [name]
    mov rdx, [bytes]
    syscall

    // write excl. point
    mov rax, 1
    mov rdi, 1
    lea rsi, [excl]
    mov rdx, 1
    syscall

    // exit
    mov rax, 60
    mov rdi, 127
    syscall

msg:
    .asciz "Hello, "

prompt:
    .asciz "What's your name: "

excl:
    .asciz "!"

.bss                ;
.lcomm name, 9      ;
.lcomm bytes, 8     ;
