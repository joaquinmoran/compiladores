#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "ast.h"
#include "symTable.h"

int MAX_NODES = 100;
int i = 1;
FILE *file;

void declClass(struct  tree *declNode){

    char *name = declNode->left->info.name;
    int val = declNode->right->info.value;
    fprintf(file, "T%d := %d\n", i, val);
    fprintf(file, "%s := T%d\n", name, i);
    fflush(file);
    i++;

}

char *exprClass(struct tree *exprNode){
    char *name = exprNode->left->info.name;
    char result[10];
    if(strcmp(exprNode->info.name, "PROD") == 0){
        struct tree *right = exprNode;
        if(strcmp(right->left->info.type, "ID") == 0){
            if(strcmp(right->right->info.type, "ID") == 0){
                char *nameLO = right->left->info.name;
                char *nameRO = right->right->info.name;
                fprintf(file, "T%d := %s * %s\n", i, nameLO, nameRO);
                fflush(file);
                sprintf(result, "T%d",i);
                i++;
            }else{
                char *nameLO = right->left->info.name;
                int val = right->right->info.value;
                fprintf(file, "T%d := %s * %d\n", i, nameLO, val);

                fflush(file);
                sprintf(result, "T%d",i);
                i++;
            }
        }else{
            if(strcmp(right->right->info.type, "ID") == 0){
                char *nameRO = right->right->info.name;
                    int val = right->left->info.value;
                    fprintf(file, "T%d := %d * %s\n", i, val, nameRO);
                    fflush(file);
                    sprintf(result, "T%d",i);
                    i++;
                }else{
                    int valR = right->right->info.value;
                    int valL = right->left->info.value;
                    fprintf(file, "T%d := %d * %d\n", i, valL, valR);
                    fflush(file);
                    sprintf(result, "T%d",i);
                    i++;
                }
        }
    }
    return strdup(result);
}

void assigClass(struct tree *exprNode){
    bool leftE = false; // para verificar si 
    bool rightE = false;
    char *t1;
    char *t2;
    if(exprNode == NULL){
        return;
    }
   
    char *name = exprNode->left->info.name;
    if(strcmp(exprNode->info.name, "ASSIG->EXPR") == 0){
        if(strcmp(exprNode->right->info.name, "SUM") == 0){
            struct tree *right = exprNode->right;
            if(strcmp(right->right->info.type, "EXPR") == 0){
                 t2 = exprClass(right->right);
                 rightE = true;
                 fflush(file);
            }
            if(strcmp(right->left->info.type, "EXPR") == 0){
                 t1 = exprClass(right->left);
                 leftE = true;
                 fflush(file);
            }
            if(strcmp(right->left->info.type, "ID") == 0){
                if(strcmp(right->right->info.type, "ID") == 0){
                    char *nameLO = right->left->info.name;
                    char *nameRO = right->right->info.name;
                    if(leftE && rightE){
                        fprintf(file, "T%d := %s + %s\n", i, t1, t2);
                        fprintf(file, "%s := T%d\n", name, i);
                        fflush(file);
                    }else{
                        fprintf(file, "T%d := %s + %s\n", i, nameLO, nameRO);
                        fprintf(file, "%s := T%d\n", name, i);
                        fflush(file);
                    }
                    i++;
                }else{
                    char *nameLO = right->left->info.name;
                    int val = right->right->info.value;
                    if(leftE){
                        fprintf(file, "T%d := %s + %s\n", i, t1, val);
                        fprintf(file, "%s := T%d\n", name, i);
                        fflush(file);
                    }else{
                        fprintf(file, "T%d := %s + %d\n", i, nameLO, val);
                        fprintf(file, "%s := T%d\n", name, i);
                        fflush(file);
                    }
                    i++;
                }
            }else{
                if(strcmp(right->right->info.type, "ID") == 0){
                    char *nameRO = right->right->info.name;
                    int val = right->left->info.value;
                    if(rightE){
                        fprintf(file, "T%d := %s + %s\n", i, val, t2);
                        fprintf(file, "%s := T%d\n", name, i);
                        fflush(file);
                    }else{
                        fprintf(file, "T%d := %d + %s\n", i, val, nameRO);
                        fprintf(file, "%s := T%d\n", name, i);
                        fflush(file);
                    }
                    i++;
                    }else{
                        int valR = right->right->info.value;
                        int valL = right->left->info.value;
                        if(rightE){
                            fprintf(file, "T%d := %d + %s\n", i, valL, t2);
                            fprintf(file, "%s := T%d\n", name, i);
                            fflush(file);
                        }else{
                            if(leftE){
                                fprintf(file, "T%d := %s + %d\n", i, t1, valR);
                                fprintf(file, "%s := T%d\n", name, i);
                                fflush(file);
                            }else{
                                fprintf(file, "T%d := %d + %d\n", i, valL, valR);
                                fprintf(file, "%s := T%d\n", name, i);
                                fflush(file);
                            }
                        }
                        i++;
                    }
            }
        }
        if(strcmp(exprNode->right->info.name, "PROD") == 0){
            struct tree *right = exprNode->right;
            if(strcmp(right->left->info.type, "ID") == 0){
                if(strcmp(right->right->info.type, "ID") == 0){
                    char *nameLO = right->left->info.name;
                    char *nameRO = right->right->info.name;
                    fprintf(file, "T%d := %s * %s\n", i, nameLO, nameRO);
                    fprintf(file, "%s := T%d\n", name, i);
                    fflush(file);
                    i++;
                }else{
                    char *nameLO = right->left->info.name;
                    int val = right->right->info.value;
                    fprintf(file, "T%d := %s * %d\n", i, nameLO, val);
                    fprintf(file, "%s := T%d\n", name, i);
                    fflush(file);
                    i++;
                }
            }else{
                if(strcmp(right->right->info.type, "ID") == 0){
                    char *nameRO = right->right->info.name;
                        int val = right->left->info.value;
                        fprintf(file, "T%d := %d * %s\n", i, val, nameRO);
                        fprintf(file, "%s := T%d\n", name, i);
                        fflush(file);
                        i++;
                    }else{
                        int valR = right->right->info.value;
                        int valL = right->left->info.value;
                        fprintf(file, "T%d := %d * %d\n", i, valL, valR);
                        fprintf(file, "%s := T%d\n", name, i);
                        fflush(file);
                        i++;
                    }
            }
        }
    }
}



void breadthFirstTraversal(struct tree *root){
    file = fopen("intermediate_code_generated.txt", "w");
    if(root == NULL){
        return;
    }

    struct tree *queue[MAX_NODES];
    int front = -1;
    int back = -1;

    queue[++back] = root;

    while(front != back) {
        struct tree *currentNode = queue[++front];
        printf("TYPE: %s\n", currentNode->info.type);
        if(strcmp(currentNode->info.type, "DECL") == 0){
            declClass(currentNode);
        }
        if(strcmp(currentNode->info.type, "ASSIG") == 0){
            assigClass(currentNode);
        }
        printNode(currentNode);

        if(currentNode->left != NULL){
            queue[++back] = currentNode->left;
        }
        if(currentNode->right != NULL){
            queue[++back] = currentNode->right;
        }
    }

    fclose(file);
}

