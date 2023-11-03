    .text
    .globl  main
    .type	main, @function
main:
    pushq    %rbp
    movq	    %rsp, %rbp
    subq	    $24, %rsp
    movq    $5, -8(%rbp)
    movq    $3, -16(%rbp)
    movq    $1, -24(%rbp)
    movq    -8(%rbp), %rax
    addq    -8(%rbp), %rax
    movq    %rax, -32(%rbp)
    movq    -32(%rbp), %rax
    movq    %rax, -8(%rbp)
    movq    -16(%rbp), %rax
    imulq    -16(%rbp), %rax
    movq    %rax, -40(%rbp)
    movq    -40(%rbp), %rax
    movq    %rax, -16(%rbp)
    movq    -16(%rbp), %rax
    imulq    -16(%rbp), %rax
    movq    %rax, -48(%rbp)
    movq    -8(%rbp), %rax
    addq    -8(%rbp), %rax
    movq    %rax, -56(%rbp)
    movq    $81, %rax
    addq    $20, %rax
    movq    %rax, -64(%rbp)
    movq    -64(%rbp), %rax
    movq    %rax, -8(%rbp)
    movq    -16(%rbp), %rax
    imulq    $4, %rax
    movq    %rax, -72(%rbp)
    movq    -72(%rbp), %rax
    movq    %rax, -8(%rbp)
    movq    -8(%rbp), %rdi
    call    printInt
    movq    -24(%rbp), %rax
    imulq    -24(%rbp), %rax
    movq    %rax, -80(%rbp)
    movq    $1, %rdi
    call    printInt
    leave
    ret
 
    popq	   %rbp
 
    ret
 
    .size	main, .-main
   .section	.note.GNU-stack,"",@progbits
