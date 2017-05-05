	.file	"exam.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"\n The sum with Newton's Method is: %llu  \n"
	.align 8
.LC2:
	.string	"\n Time spent for the program: %f secs \n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB3:
	.section	.text.startup,"ax",@progbits
.LHOTB3:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	call	clock
	movl	$.LC0, %esi
	movq	%rax, %rbx
	movl	$1, %edi
	movabsq	$500000000500000000, %rdx
	xorl	%eax, %eax
	call	__printf_chk
	call	clock
	pxor	%xmm0, %xmm0
	subq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	movl	$.LC2, %esi
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	movl	$1, %eax
	divsd	.LC1(%rip), %xmm0
	jmp	__printf_chk
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE3:
	.section	.text.startup
.LHOTE3:
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	1093567616
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
