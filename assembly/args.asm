.intel_syntax noprefix

.equ SYS_WRITE, 1
.equ SYS_EXIT, 60

.section .text

.global _start

_start:
	// load argc and print it
	mov  rdi, [rsp]
	call stdout_int

	// print new line
	mov rax, SYS_WRITE
	mov rdi, 1
	lea rsi, [nl]
	mov rdx, 1
	syscall

	// exit
	mov rax, SYS_EXIT
	mov rdi, 0
	syscall

stdout_int:
	push rbp
	mov  rbp, rsp

	mov rax, rdi
	lea rdi, [buf + 19]
	mov rcx, 0

.convert_loop:
	xor  rdx, rdx
	mov  rbx, 10
	div  rbx
	add  dl, '0'
	dec  rdi
	mov  [rdi], dl
	inc  rcx
	test rax, rax
	jnz  .convert_loop

	mov rsi, rdi
	mov rdi, 1
	mov rdx, rcx
	mov rax, 1
	syscall

	pop rbp
	ret

.section .data

nl:
	.asciz "\n"

	.section .bss
	.lcomm   buf, 20
