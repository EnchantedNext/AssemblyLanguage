.intel_syntax noprefix

.equ SOCK_STREAM, 1
.equ AF_INET, 2
.equ SOCK_FAMILY, AF_INET
.equ SOCK_TYPE, SOCK_STREAM
.equ INADDR_ANY, 0
.equ PORT_NET, 0xC211
.equ ADDR_LEN, 16
.equ SYS_EXIT, 60
.equ SYS_SOCKET, 41
.equ SYS_BIND, 49
.equ SYS_WRITE, 1

.section .text
.global _start
_start:
    sub rsp, 8
    call start_socket
    add rsp, 8

    // exit
    mov rax, SYS_EXIT
    mov rdi, 0
    syscall

start_socket:
    // create socket
    mov rax, SYS_SOCKET
    mov rdi, SOCK_FAMILY
    mov rsi, SOCK_TYPE
    mov rdx, 0
    syscall

    cmp rax, 0
    jl error_exit

    mov qword ptr [sock_desc], rax

    // bind socket
    mov rax, SYS_BIND
    mov rdi, qword ptr [sock_desc]
    lea rsi, [rip + sockaddr_in_struct]
    mov rdx, ADDR_LEN
    syscall

    cmp rax, 0
    jl error_bind_failure

    // write success msg
    mov rax, SYS_WRITE
    mov rdi, 1
    lea rsi, [bind_msg]
    mov rdx, 43
    syscall

    ret

error_bind_failure:
    mov qword ptr [error_code_temp], rax

    mov rax, 3
    mov rdi, qword ptr [sock_desc]
    syscall

    mov rax, qword ptr [error_code_temp]
    jmp error_exit

error_exit:
    neg rax
    mov qword ptr [sock_err_c], rax

    mov rax, SYS_WRITE
    mov rdi, 1
    lea rsi, [socket_create_fail_msg]
    mov rdx, 22
    syscall

    // exit
    mov rax, SYS_EXIT
    mov rdi, qword ptr [sock_err_c]
    syscall

.section .data
sockaddr_in_struct:
    .word AF_INET
    .word PORT_NET
    .long INADDR_ANY
    .quad 0x0

bind_msg:
    .asciz "Socket successfully binded to 0.0.0.0:4554"

child_msg:
    .asciz "Hello from child thread!"

socket_create_fail_msg:
    .asciz "Error creating socket!"

.section .bss
.lcomm child_stack, 8192
.lcomm sock_desc, 8
.lcomm sock_err_c, 8
.lcomm error_code_temp, 8
