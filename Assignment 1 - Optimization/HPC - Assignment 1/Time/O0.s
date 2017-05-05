	.file	"exam.c"
	.section	.rodata
	.align 8
.LC0:
	.string	"\n The sum with Newton's Method is: %llu  \n"
	.align 8
.LC2:
	.string	"\n Time spent for the program: %f secs \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	call	clock
	movq	%rax, -40(%rbp)
	movq	$0, -32(%rbp)
	movq	$1000000000, -24(%rbp)
	movq	-24(%rbp), %rax
	addq	$1, %rax
	imulq	-24(%rbp), %rax
	shrq	%rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	call	clock
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	subq	-40(%rbp), %rax
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	movsd	.LC1(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	movl	$.LC2, %edi
	movl	$1, %eax
	call	printf
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC1:
	.long	0
	.long	1093567616
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
