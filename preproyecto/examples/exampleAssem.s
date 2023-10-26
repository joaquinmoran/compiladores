	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$24, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$2, -8(%rbp)
	movl	$2, -4(%rbp)
	sall	-8(%rbp)
	sall	-4(%rbp)
	movl	-8(%rbp), %eax
	imull	%eax, %eax
	addl	%eax, %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	
	popq	%rbp

	ret


	.size	main, .-main
	.section	.note.GNU-stack,"",@progbits
	