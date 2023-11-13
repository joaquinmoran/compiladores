#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>

#include "ast.h"
#include "symTable.h"
#include "interCodeGen.h"


extern struct listNode *instrListHead;
FILE *assemblyFile;
int tempN = 0;
char temp[10];
int lastTemp;

extern bool isBoolExpr;

void tempMeth(){
    sprintf(temp, "T%d", tempN);
    struct node *tempNode = getNodeByName(temp);
    fprintf(assemblyFile, "    movq    %%rax, %d(%%rbp)\n", tempNode->info.offset);
    lastTemp = tempN;
    tempN++;
}

void movqMeth(struct node *node){
    fprintf(assemblyFile, "    movq    $%d, %d(%%rbp)\n", node->info.value, node->info.offset);
}

void addqMethForTwoID(struct node *leftOp, struct node *rightOp ){
    fprintf(assemblyFile, "    movq    %d(%%rbp), %%rax\n", leftOp->info.offset);
    fprintf(assemblyFile, "    addq    %d(%%rbp), %%rax\n", rightOp->info.offset);
    tempMeth();
}

void addqMethForOneID(struct node *op, int value){
    fprintf(assemblyFile, "    movq    %d(%%rbp), %%rax\n", op->info.offset);
    fprintf(assemblyFile, "    addq    $%d, %%rax\n", value);
    tempMeth();
}

void addqMethForConst(int valL, int valR){
    fprintf(assemblyFile, "    movq    $%d, %%rax\n", valL);
    fprintf(assemblyFile, "    addq    $%d, %%rax\n", valR);
    tempMeth();
}

void mulqMethForTwoID(struct node *leftOp, struct node *rightOp ){
    fprintf(assemblyFile, "    movq    %d(%%rbp), %%rax\n", leftOp->info.offset);
    fprintf(assemblyFile, "    imulq    %d(%%rbp), %%rax\n", rightOp->info.offset);
    tempMeth();
}

void mulqMethForOneID(struct node *op, int value){
    fprintf(assemblyFile, "    movq    %d(%%rbp), %%rax\n", op->info.offset);
    fprintf(assemblyFile, "    imulq    $%d, %%rax\n", value);
    tempMeth();
}

void mulqMethForConst(int valL, int valR){
    fprintf(assemblyFile, "    movq    $%d, %%rax\n", valL);
    fprintf(assemblyFile, "    imulq    $%d, %%rax\n", valR);
    tempMeth();
}

void subqMethForTwoID(struct node *leftOp, struct node *rightOp ){
    fprintf(assemblyFile, "    movq    %d(%%rbp), %%rax\n", leftOp->info.offset);
    fprintf(assemblyFile, "    subq    %d(%%rbp), %%rax\n", rightOp->info.offset);
    tempMeth();
}

void subqMethForOneID(struct node *op, int value){
    fprintf(assemblyFile, "    movq    %d(%%rbp), %%rax\n", op->info.offset);
    fprintf(assemblyFile, "    subq    $%d, %%rax\n", value);
    tempMeth();
}

void subqMethForConst(int valL, int valR){
    fprintf(assemblyFile, "    movq    $%d, %%rax\n", valL);
    fprintf(assemblyFile, "    subq    $%d, %%rax\n", valR);
    tempMeth();
}


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
    fprintf(assemblyFile, "    pushq    %%rbp\n");
    fprintf(assemblyFile, "    movq	    %%rsp, %%rbp\n");
    fprintf(assemblyFile, "    subq	    $24, %%rsp\n");
    fflush(assemblyFile);
    while(currentNode->next != NULL){
        currentNode = currentNode->next;
        if(strcmp(currentNode->instr,"DECL") == 0){
            struct node *node = getNodeByName(currentNode->left.name);
            fprintf(assemblyFile, "    movq    $%d, %d(%%rbp)\n", currentNode->right.value ,node->info.offset);
            fflush(assemblyFile);
        }

        if(strcmp(currentNode->instr,"SUM") == 0){
            if(strcmp(currentNode->left.type,"ID") == 0){
                struct node *leftNode = getNodeByName(currentNode->left.name);
                if(strcmp(currentNode->right.type,"ID") == 0){
                    struct node *rightNode = getNodeByName(currentNode->right.name);
                    addqMethForTwoID(leftNode, rightNode);
                }else{
                    if(strcmp(currentNode->right.type,"EXPR") == 0){
                        int rightExprRes = currentNode->right.value;
                        addqMethForOneID(leftNode, rightExprRes);       
                    }else{
                        addqMethForOneID(leftNode, currentNode->right.value);
                    }
                }
            }else{
                if(strcmp(currentNode->left.type,"EXPR") == 0){
                    int leftExprRes = currentNode->left.value;
                    if(strcmp(currentNode->right.type,"ID") == 0){
                        struct node *rightNode = getNodeByName(currentNode->right.name);
                        addqMethForOneID(rightNode, leftExprRes);
                    }else{
                        if(strcmp(currentNode->right.type,"EXPR") == 0){
                            int rightExprRes = currentNode->right.value;
                            addqMethForConst(leftExprRes, rightExprRes);
                        }else{
                            addqMethForConst(leftExprRes, currentNode->right.value);
                        }
                    }
                }else{
                    int leftExprRes = currentNode->left.value;
                    if(strcmp(currentNode->right.type,"ID") == 0){
                        struct node *rightNode = getNodeByName(currentNode->right.name);
                        addqMethForOneID(rightNode, leftExprRes);
                    }else{
                        if(strcmp(currentNode->right.type,"EXPR") == 0){
                            int rightExprRes = currentNode->right.value;
                            addqMethForConst(leftExprRes, rightExprRes);
                        }else{
                            addqMethForConst(leftExprRes, currentNode->right.value);
                        }
                    }
                }
            }
        }

        if(strcmp(currentNode->instr,"PROD") == 0){
            if(strcmp(currentNode->left.type,"ID") == 0){
                struct node *leftNode = getNodeByName(currentNode->left.name);
                if(strcmp(currentNode->right.type,"ID") == 0){
                    struct node *rightNode = getNodeByName(currentNode->right.name);
                    mulqMethForTwoID(leftNode, rightNode);
                }else{
                    if(strcmp(currentNode->right.type,"EXPR") == 0){
                        int rightExprRes = currentNode->right.value;
                        mulqMethForOneID(leftNode, rightExprRes);
                    }else{
                        mulqMethForOneID(leftNode, currentNode->right.value);
                    }
                }
            }else{
                if(strcmp(currentNode->left.type,"EXPR") == 0){
                    int leftExprRes = currentNode->left.value;
                    if(strcmp(currentNode->right.type,"ID") == 0){
                        struct node *rightNode = getNodeByName(currentNode->right.name);
                        mulqMethForOneID(rightNode, leftExprRes);
                    }else{
                        if(strcmp(currentNode->right.type,"EXPR") == 0){
                            int rightExprRes = currentNode->right.value;
                            mulqMethForConst(leftExprRes, rightExprRes);
                        }else{
                            mulqMethForConst(leftExprRes, currentNode->right.value);
                        }
                    }
                }else{
                    
                    int leftExprRes = currentNode->left.value;
                    if(strcmp(currentNode->right.type,"ID") == 0){
                        struct node *rightNode = getNodeByName(currentNode->right.name);
                        mulqMethForOneID(rightNode, leftExprRes);
                    }else{
                        if(strcmp(currentNode->right.type,"EXPR") == 0){
                            int rightExprRes = currentNode->right.value;
                            mulqMethForConst(leftExprRes, rightExprRes);
                        }else{
                            mulqMethForConst(leftExprRes, currentNode->right.value);
                        }
                    }
                }
            }
        }

        if(strcmp(currentNode->instr,"SUBT") == 0){
            if(strcmp(currentNode->left.type,"ID") == 0){
                struct node *leftNode = getNodeByName(currentNode->left.name);
                if(strcmp(currentNode->right.type,"ID") == 0){
                    struct node *rightNode = getNodeByName(currentNode->right.name);
                    subqMethForTwoID(leftNode, rightNode);
                }else{
                    if(strcmp(currentNode->right.type,"EXPR") == 0){
                        int rightExprRes = currentNode->right.value;
                        subqMethForOneID(leftNode, rightExprRes);
                    }else{
                        subqMethForOneID(leftNode, currentNode->right.value);
                    }
                }
            }else{
                if(strcmp(currentNode->left.type,"EXPR") == 0){
                    int leftExprRes = currentNode->left.value;
                    if(strcmp(currentNode->right.type,"ID") == 0){
                        struct node *rightNode = getNodeByName(currentNode->right.name);
                        subqMethForOneID(rightNode, leftExprRes);
                    }else{
                        if(strcmp(currentNode->right.type,"EXPR") == 0){
                            int rightExprRes = currentNode->right.value;
                            subqMethForConst(leftExprRes, rightExprRes);
                        }else{
                            subqMethForConst(leftExprRes, currentNode->right.value);
                        }
                    }
                }else{
                    int leftExprRes = currentNode->left.value;
                    if(strcmp(currentNode->right.type,"ID") == 0){
                        struct node *rightNode = getNodeByName(currentNode->right.name);
                        subqMethForOneID(rightNode, leftExprRes);
                    }else{
                        if(strcmp(currentNode->right.type,"EXPR") == 0){
                            int rightExprRes = currentNode->right.value;
                            subqMethForConst(leftExprRes, rightExprRes);
                        }else{
                            subqMethForConst(leftExprRes, currentNode->right.value);
                        }
                    }
                }
            }
        }

        if(strcmp(currentNode->instr,"ASSIG") == 0){
            struct node *leftNode = getNodeByName(currentNode->left.name);
            if(strcmp(currentNode->right.type,"ID") == 0){
                struct node *rightNode = getNodeByName(currentNode->right.name);
                fprintf(assemblyFile, "    movq    %d(%%rbp), %%rax\n", rightNode->info.offset);
                fprintf(assemblyFile, "    movq    %%rax, %d(%%rbp)\n", leftNode->info.offset);
            }
            if(strcmp(currentNode->right.name,"VALUE") == 0){
                fprintf(assemblyFile, "    movq    $%d, %%rax\n", currentNode->right.value);
                fprintf(assemblyFile, "    movq    %%rax, %d(%%rbp)\n", leftNode->info.offset);
            }
            if(strcmp(currentNode->right.type, "EXPR") == 0){
                sprintf(temp, "T%d", lastTemp);
                struct node *tempNode = getNodeByName(temp);
                fprintf(assemblyFile, "    movq    %d(%%rbp), %%rax\n", tempNode->info.offset);
                fprintf(assemblyFile, "    movq    %%rax, %d(%%rbp)\n", leftNode->info.offset);
            }
            
        } 

        if((strcmp(currentNode->instr,"RETURNINT") == 0)){
            if(strcmp(currentNode->left.type, "EXPR") == 0){
                fprintf(assemblyFile, "    movq    $%d, %%rdi\n", currentNode->left.value);
                fprintf(assemblyFile, "    call    printInt\n");
            }else{
                struct node *node = getNodeByName(currentNode->left.name);
                printf(assemblyFile, "    movq    %d(%%rbp), %%rdi\n", node->info.offset);
                fprintf(assemblyFile, "    call    printInt\n");
            }
        }

        if(strcmp(currentNode->instr,"RETURNBOOL") == 0){
            if((strcmp(currentNode->left.type, "EXPR") == 0)){
                fprintf(assemblyFile, "    movq    $%d, %%rdi\n", currentNode->left.value);
                fprintf(assemblyFile, "    call    printBool\n");
            }else{
                struct node *node = getNodeByName(currentNode->left.name);
                fprintf(assemblyFile, "    movq    %d(%%rbp), %%rdi\n", node->info.offset);
                fprintf(assemblyFile, "    call    printBool\n");
            }
        }
        
        if(strcmp(currentNode->instr,"RETURN") == 0){
            if(strcmp(currentNode->left.type,"ID") == 0){
                struct node *node = getNodeByName(currentNode->left.name);
                if(strcmp(node->info.type,"BOOLEAN") == 0){
                    fprintf(assemblyFile, "    movq    %d(%%rbp), %%rdi\n", node->info.offset);
                    fprintf(assemblyFile, "    call    printBool\n");
                }else{
                    fprintf(assemblyFile, "    movq    %d(%%rbp), %%rdi\n", node->info.offset);
                    fprintf(assemblyFile, "    call    printInt\n");
                }
            }else{
                if(strcmp(currentNode->left.type,"BOOLEAN") == 0){
                    fprintf(assemblyFile, "    movq    $%d, %%rdi\n", currentNode->left.value);
                    fprintf(assemblyFile, "    call    printBool\n");
                }else{
                    fprintf(assemblyFile, "    movq    $%d, %%rdi\n", currentNode->left.value);
                    fprintf(assemblyFile, "    call    printInt\n");
                }
            }
        }
                
    }     
    fprintf(assemblyFile, "    leave\n");
    fprintf(assemblyFile, "    ret\n");
    fprintf(assemblyFile," \n");
    fprintf(assemblyFile, "    popq	   %%rbp\n");
    fprintf(assemblyFile," \n");
    fprintf(assemblyFile, "    ret\n");
    fprintf(assemblyFile," \n");
    fprintf(assemblyFile, "    .size	main, .-main\n");
    fprintf(assemblyFile, "   .section	.note.GNU-stack,\"\",@progbits\n");
    fclose(assemblyFile);

}
