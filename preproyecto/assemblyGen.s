    .text
    .globl  main
    .type	main, @function
main:
    pushq    %rbp
    movq	    %rsp, %rbp
    subq	    $24, %rsp
    movq    $5, -8(%rbp)
    movq    $2, -16(%rbp)
    movq    $1, -24(%rbp)
    movq    $0, -32(%rbp)
    movq    -32(%rbp), %rax
    imulq    $1, %rax
    movq    %rax, -40(%rbp)
    movq    -40(%rbp), %rax
    movq    %rax, -24(%rbp)
    movq    $4, %rax
    imulq    $4, %rax
    movq    %rax, -48(%rbp)
    movq    -48(%rbp), %rax
    movq    %rax, -16(%rbp)
    movq    -8(%rbp), %rax
    imulq    $2, %rax
    movq    %rax, -56(%rbp)
    movq    -16(%rbp), %rax
    imulq    $10, %rax
    movq    %rax, -64(%rbp)
    movq    -64(%rbp), %rax
    movq    %rax, -8(%rbp)
    movq    $1, %rax
    imulq    $1, %rax
    movq    %rax, -72(%rbp)
    movq    -72(%rbp), %rax
    movq    %rax, -24(%rbp)
    movq    -24(%rbp), %rax
    imulq    -32(%rbp), %rax
    movq    %rax, -80(%rbp)
    movq    $0, %rdi
    call    printBool
    movq    -8(%rbp), %rax
    imulq    $4, %rax
    movq    %rax, -88(%rbp)
    movq    $640, %rdi
    call    printInt
    movq    $4, %rdi
    call    printInt
    movq    -8(%rbp), %rdi
    call    printInt
    movq    -24(%rbp), %rdi
    call    printBool
    movq    $0, %rdi
    call    printBool
    leave
    ret
 
    popq	   %rbp
 
    ret
 
    .size	main, .-main
   .section	.note.GNU-stack,"",@progbits
