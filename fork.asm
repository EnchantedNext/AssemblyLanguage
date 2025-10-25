.intel_syntax noprefix
.global _start

_start:
    // write
    mov rax, 1
    mov rdi, 1
    lea rsi, [msg]
    mov rdx, 19
    syscall
    // get pid
    mov rax, 39
    syscall
    mov [pid], rax

    // write pid to stdout
    mov rdi, rax
    call stdout_int

    // write newline
    mov rax, 1
    mov rdi, 1
    lea rsi, [nl]
    mov rdx, 1
    syscall

    // fork process
    mov rax, 57
    syscall
    // check if we are in child process
    cmp rax, 0
    je child

    // store child pid in buffer
    mov [c_pid_buf], rax
    // write child pid context msg
    mov rax, 1
    mov rdi, 1
    lea rsi, [c_msg]
    mov rdx, 20
    syscall
    // write child pid to stdout
    mov rdi, [c_pid_buf]
    call stdout_int

    // write newline
    mov rax, 1
    mov rdi, 1
    lea rsi, [nl]
    mov rdx, 1
    syscall

    // exit
    mov rax, 60
    mov rdi, 127
    syscall

child:
    mov rax, 60
    mov rdi, 0
    syscall

stdout_int:
    push    rbp
    mov     rbp, rsp

    mov     rax, rdi
    lea     rdi, [buf + 19]
    mov     rcx, 0

.convert_loop:
    xor     rdx, rdx
    mov     rbx, 10
    div     rbx
    add     dl, '0'
    dec     rdi
    mov     [rdi], dl
    inc     rcx
    test    rax, rax
    jnz     .convert_loop

    mov     rsi, rdi
    mov     rdi, 1
    mov     rdx, rcx
    mov     rax, 1
    syscall

    pop     rbp
    ret


msg:
    .asciz "Main process, pid: "

c_msg:
    .asciz "Child process, pid: "

nl:
    .asciz "\n"

.bss                ;
.lcomm pid, 8       ;
.lcomm buf, 20      ;
.lcomm c_pid_buf, 8 ;
