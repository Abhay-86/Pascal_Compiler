# file header
	.file	"testing/if.p"
	.intel_syntax noprefix


# create io format strings
	.section	.rodata
.LC0: # reading
	.string "%lld"
.LC1: # writing
	.string "%lld\n"
	.text



# main header
	.globl	main
	.type	main, @function
main:
	push	rbp
	mov		rbp, rsp

# set up stack frame
	push	0
	push	rbp
	sub		rsp, 16
	# end function header

# main code

# evaluate expression
	mov		r15, 5

# assignment
	mov		QWORD PTR [rbp-24], r15

# call 'read' using fscanf
	mov		rax, QWORD PTR fs:40
	xor		eax, eax
	mov		rax, QWORD PTR stdin[rip]
	lea		rdx, QWORD PTR [rbp-32]
	mov		esi, OFFSET FLAT:.LC0
	mov		rdi, rax
	mov		eax, 0
	call	__isoc99_fscanf


# start if
	mov		r15, QWORD PTR [rbp-32]
	cmp		r15, QWORD PTR [rbp-24]
	setg	r15b
	movzx	r15, r15b
	cmp		r15, 0
	je		.L1
	# end conditional

# evaluate expression
	mov		r15, 0

# assignment
	mov		QWORD PTR [rbp-32], r15
.L1:

# end if

# call 'write' using fprintf
	mov		rdx, QWORD PTR [rbp-32]
	mov		rax, QWORD PTR stderr[rip]
	mov		esi, OFFSET FLAT:.LC1
	mov		rdi, rax
	mov		eax, 0
	call	fprintf


# main footer
	mov		eax, 0
	leave
	ret

	.size	main, .-main



# file footer
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"

	.section	.note.GNU-stack,"",@progbits
