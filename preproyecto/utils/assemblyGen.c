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

void tempMeth(){
    sprintf(temp, "T%d", tempN);
    struct node *tempNode = getNodeByName(temp);
    fprintf(assemblyFile, "    movq    %%eax, %d(%%rbp)\n", tempNode->info.offset);
    lastTemp = tempN;
    tempN++;
}

void movqMeth(struct node *node){
    fprintf(assemblyFile, "    movq    $%d, %d(%%rbp)\n", node->info.value, node->info.offset);
    fflush(assemblyFile);
}

void addqMethForTwoID(struct node *leftOp, struct node *rightOp ){
    fprintf(assemblyFile, "    movq    %d(%%rbp), %%eax\n", leftOp->info.offset);
    fprintf(assemblyFile, "    addq    %d(%%rbp), %%eax\n", rightOp->info.offset);
    tempMeth();
    fflush(assemblyFile);
}

void addqMethForOneID(struct node *op, int value){
    fprintf(assemblyFile, "    movq    %d(%%rbp), %%eax\n", op->info.offset);
    fprintf(assemblyFile, "    addq    $%d, %%eax\n", value);
    tempMeth();
    fflush(assemblyFile);
}

void addqMethForConst(int valL, int valR){
    fprintf(assemblyFile, "    movq    $%d, %%eax\n", valL);
    fprintf(assemblyFile, "    addq    $%d, %%eax\n", valR);
    tempMeth();
    // // fflush(assemblyFile);
}

void mulqMethForTwoID(struct node *leftOp, struct node *rightOp ){
    fprintf(assemblyFile, "    movq    %d(%%rbp), %%eax\n", leftOp->info.offset);
    fprintf(assemblyFile, "    imulq    %d(%%rbp), %%eax\n", rightOp->info.offset);
    tempMeth();
    fflush(assemblyFile);
}

void mulqMethForOneID(struct node *op, int value){
    fprintf(assemblyFile, "    movq    %d(%%rbp), %%eax\n", op->info.offset);
    fprintf(assemblyFile, "    imulq    $%d, %%eax\n", value);
    tempMeth();
    fflush(assemblyFile);
}

void mulqMethForConst(int valL, int valR){
    fprintf(assemblyFile, "    movq    $%d, %%eax\n", valL);
    fprintf(assemblyFile, "    imulq    $%d, %%eax\n", valR);
    tempMeth();
    fflush(assemblyFile);
}

void subqMethForTwoID(struct node *leftOp, struct node *rightOp ){
    fprintf(assemblyFile, "    movq    %d(%%rbp), %%eax\n", leftOp->info.offset);
    fprintf(assemblyFile, "    subq    %d(%%rbp), %%eax\n", rightOp->info.offset);
    tempMeth();
    fflush(assemblyFile);
}

void subqMethForOneID(struct node *op, int value){
    fprintf(assemblyFile, "    movq    %d(%%rbp), %%eax\n", op->info.offset);
    fprintf(assemblyFile, "    subq    $%d, %%eax\n", value);
    tempMeth();
    fflush(assemblyFile);
}

void subqMethForConst(int valL, int valR){
    fprintf(assemblyFile, "    movq    $%d, %%eax\n", valL);
    fprintf(assemblyFile, "    subq    $%d, %%eax\n", valR);
    tempMeth();
    // // fflush(assemblyFile);
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
            // printf("RIGHT: %s\n",currentNode->right.name);
            // printf("LEFT: %s\n",currentNode->left.type);
            if(strcmp(currentNode->left.type,"ID") == 0){
                struct node *leftNode = getNodeByName(currentNode->left.name);
                movqMeth(leftNode);
                if(strcmp(currentNode->right.type,"ID") == 0){
                    struct node *rightNode = getNodeByName(currentNode->right.name);
                    movqMeth(rightNode);
                    addqMethForTwoID(leftNode, rightNode);
                }else{
                    if(strcmp(currentNode->right.type,"EXPR") == 0){
                        int rightExprRes = currentNode->right.value;
                        addqMethForOneID(leftNode, rightExprRes);       
                    }
                    addqMethForOneID(leftNode, currentNode->right.value);
                }
            }else{
                if(strcmp(currentNode->left.type,"EXPR") == 0){
                    int leftExprRes = currentNode->left.value;
                    //busco el valor Tx de la tabla para el resultado de la expresion dentro expresion?
                    if(strcmp(currentNode->right.type,"ID") == 0){
                        struct node *rightNode = getNodeByName(currentNode->right.name);
                        addqMethForOneID(rightNode, leftExprRes);
                    }else{
                        printf("%s\n", currentNode->right.type);
                        printf("%d\n", leftExprRes);
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
                movqMeth(leftNode);
                if(strcmp(currentNode->right.type,"ID") == 0){
                    struct node *rightNode = getNodeByName(currentNode->right.name);
                    movqMeth(rightNode);
                    mulqMethForTwoID(leftNode, rightNode);
                }else{
                    if(strcmp(currentNode->right.type,"EXPR") == 0){
                        int rightExprRes = currentNode->right.value;
                        mulqMethForOneID(leftNode, rightExprRes);
                    }
                    mulqMethForOneID(leftNode, currentNode->right.value);
                }
            }else{
                if(strcmp(currentNode->left.type,"EXPR") == 0){
                    int leftExprRes = currentNode->left.value;
                    //busco el valor Tx de la tabla para el resultado de la expresion dentro expresion?
                    if(strcmp(currentNode->right.type,"ID") == 0){
                        struct node *rightNode = getNodeByName(currentNode->right.name);
                        mulqMethForOneID(rightNode, leftExprRes);
                    }else{
                        printf("%s\n", currentNode->right.type);
                        printf("%d\n", leftExprRes);
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
                movqMeth(leftNode);
                if(strcmp(currentNode->right.type,"ID") == 0){
                    struct node *rightNode = getNodeByName(currentNode->right.name);
                    movqMeth(rightNode);
                    subqMethForTwoID(leftNode, rightNode);
                }else{
                    if(strcmp(currentNode->right.type,"EXPR") == 0){
                        int rightExprRes = currentNode->right.value;
                        subqMethForOneID(leftNode, rightExprRes);
                    }
                    subqMethForOneID(leftNode, currentNode->right.value);
                }
            }else{
                if(strcmp(currentNode->left.type,"EXPR") == 0){
                    int leftExprRes = currentNode->left.value;
                    //busco el valor Tx de la tabla para el resultado de la expresion dentro expresion?
                    if(strcmp(currentNode->right.type,"ID") == 0){
                        struct node *rightNode = getNodeByName(currentNode->right.name);
                        subqMethForOneID(rightNode, leftExprRes);
                    }else{
                        printf("%s\n", currentNode->right.type);
                        printf("%d\n", leftExprRes);
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
            sprintf(temp, "T%d", lastTemp);
            struct node *tempNode = getNodeByName(temp);
            fprintf(assemblyFile, "    movq    %d(%%rbp), %%eax\n", tempNode->info.offset);
            fprintf(assemblyFile, "    movq    %%eax, %d(%%rbp)\n", leftNode->info.offset);
            fflush(assemblyFile);
            bool modified = setValueByName(tempNode->info.value, leftNode->info.name);
            printTable();
        }  


    }
    //printTable();
    fprintf(assemblyFile," \n");
    fprintf(assemblyFile, "    popq	   %%rbp\n");
    fprintf(assemblyFile," \n");
    fprintf(assemblyFile, "    ret\n");
    fprintf(assemblyFile," \n");
    fprintf(assemblyFile, "    .size	main, .-main\n");
    fprintf(assemblyFile, "    .section	.note.GNU-stack,"",@progbits\n");
    fflush(assemblyFile);
    fclose(assemblyFile);

}
