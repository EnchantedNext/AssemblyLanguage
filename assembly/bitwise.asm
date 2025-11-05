.intel_syntax noprefix
.global _start

_start:
	// write first prompt
	mov rax, 1
	mov rdi, 1
	lea rsi, [f_prompt]
	mov rdx, 21
	syscall

	// read first operand
	mov rax, 0
	mov rdi, 0
	lea rsi, [f_input]
	mov rdx, 8
	syscall

	cmp BYTE PTR [f_input], '0'
	je  continue

	cmp BYTE PTR [f_input], '1'
	je  continue

	jmp not_valid_input

continue:
	// write second propmt
	mov rax, 1
	mov rdi, 1
	lea rsi, [s_prompt]
	mov rdx, 22
	syscall

	// read second operand
	mov rax, 0
	mov rdi, 0
	lea rsi, [s_input]
	mov rdx, 8
	syscall

	cmp BYTE PTR [s_input], '0'
	je  continue_1

	cmp BYTE PTR [s_input], '1'
	je  continue_1

	jmp not_valid_input

continue_1:
	// convert inputs to binary
	lea  rsi, [f_input]
	call ascii_to_int
	mov  [f_op], rax

	lea  rsi, [s_input]
	call ascii_to_int
	mov  [s_op], rax

	// xor inputs
	mov rdi, [f_op]
	mov rsi, [s_op]
	xor rdi, rsi
	mov [result], rdi

	// write result
	mov rax, 1
	mov rdi, 1
	lea rsi, [msg]
	mov rdx, 8
	syscall

	mov  rdi, [result]
	call stdout_int

	// exit
	mov rax, 60
	mov rdi, 0
	syscall

not_valid_input:
	mov rax, 1
	mov rdi, 1
	lea rsi, [invalid_input]
	mov rdx, 16
	syscall

	mov rax, 60
	mov rdi, -127
	syscall

ascii_to_int:
	xor rax, rax
	xor rcx, rcx

	mov bl, byte ptr [rsi]
	cmp bl, '0'
	jl  .invalid_input_strict
	cmp bl, '1'
	jg  .invalid_input_strict

	sub bl, '0'

	inc rsi
	mov al, byte ptr [rsi]

	cmp al, 0x0A
	je  .check_for_null

	cmp al, 0x00
	je  .valid_input

	jmp .invalid_input_strict

.check_for_null:
	inc rsi
	mov al, byte ptr [rsi]
	cmp al, 0x00
	jne .invalid_input_strict

.valid_input:
	movzx eax, bl
	jmp   .done

.invalid_input_strict:
	mov rax, 0
	ret

.done:
	ret

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

msg:
	.asciz "Result: "

f_prompt:
	.asciz "Enter first operand: "

s_prompt:
	.asciz "Enter second operand: "

nl:
	.asciz "\n"

invalid_input:
	.asciz "Should be 0 or 1"

	.bss
	.lcomm result, 8
	.lcomm buf, 20
	.lcomm f_input, 8
	.lcomm s_input, 8
	.lcomm f_op, 8
	.lcomm s_op, 8
