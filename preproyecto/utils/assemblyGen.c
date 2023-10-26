#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>

#include "ast.h"
#include "symTable.h"
#include "interCodeGen.h"


extern struct listNode *instrListHead;
FILE *assemblyFile;


void listTraverse(){
    struct listNode *currentNode = instrListHead;
    assemblyFile = fopen("assemblyGen.s","w");
    if(assemblyFile == NULL){
        fprintf(stderr, "Cant open file.\n");
        return; 
    }
    fprintf(assemblyFile, "    .text\n");
    fprintf(assemblyFile, "    .globl  main\n");
    fprintf(assemblyFile, "    .type	main, @function\n");
    fprintf(assemblyFile, "main:\n");
    fprintf(assemblyFile, "    pushq    %rbp\n");
    fprintf(assemblyFile, "    movq	    %rsp, %rbp\n");
    fprintf(assemblyFile, "    subq	    $24, %rsp\n");
    fflush(assemblyFile);
    while(currentNode->next != NULL){
        currentNode = currentNode->next;
        if(strcmp(currentNode->instr,"DECL") == 0){
            struct node *node = getNodeByName(currentNode->left.name);
            fprintf(assemblyFile, "    movq    $%d, %d(%rbp)\n", currentNode->right.value ,node->info.offset);
            fprintf(assemblyFile, "    movq    %d(%rbp), %rax\n", node->info.offset);
            fflush(assemblyFile);
        }
    }
    fprintf(assemblyFile," \n");
    fprintf(assemblyFile, "    popq	   %rbp\n");
    fprintf(assemblyFile," \n");
    fprintf(assemblyFile, "    ret\n");
    fprintf(assemblyFile," \n");
    fprintf(assemblyFile, "    .size	main, .-main\n");
    fprintf(assemblyFile, "    .section	.note.GNU-stack,"",@progbits\n");
    fflush(assemblyFile);

}
