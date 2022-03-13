	.file	"hello_world.c"
	.intel_syntax noprefix

	.section	.rodata
.LC0:
	.string	"Hello World!"

	.text
	.globl	main
	.type	main, @function
main:
	push	rbp
	mov	rbp, rsp
	mov	rax, QWORD PTR stdout[rip]
	mov	rcx, rax
	mov	edx, 12
	mov	esi, 1
	mov	edi, OFFSET FLAT:.LC0
	call	fwrite
	mov	eax, 0
	pop	rbp
	ret
	.size	main, .-main

	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
