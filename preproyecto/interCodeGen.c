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

void exprClass(struct tree *exprNode){
    char *name = exprNode->left->info.name;
    if(strcmp(exprNode->info.name, "PROD") == 0){
            fprintf(file, "si entro \n");
                fflush(file);
                struct tree *right = exprNode;
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

void assigClass(struct tree *exprNode){

    if(exprNode == NULL){
        return;
    }
   
    char *name = exprNode->left->info.name;
    if(strcmp(exprNode->info.name, "ASSIG->EXPR") == 0){
        if(strcmp(exprNode->right->info.name, "SUM") == 0){
            struct tree *right = exprNode->right;
            if(strcmp(right->right->info.type, "EXPR") == 0){
                fprintf(file, "entree1\n");
                fflush(file);
                assigClass(right->right);
            }
            if(strcmp(right->left->info.type, "EXPR") == 0){
                fprintf(file, "entree2  %s\n ",right->left->info.name);
                fflush(file);
                assigClass(right->left);
            }
            if(strcmp(right->left->info.type, "ID") == 0){
                if(strcmp(right->right->info.type, "ID") == 0){
                    char *nameLO = right->left->info.name;
                    char *nameRO = right->right->info.name;
                    fprintf(file, "T%d := %s + %s\n", i, nameLO, nameRO);
                    fprintf(file, "%s := T%d\n", name, i);
                    fflush(file);
                    i++;
                }else{
                    char *nameLO = right->left->info.name;
                    int val = right->right->info.value;
                    fprintf(file, "T%d := %s + %d\n", i, nameLO, val);
                    fprintf(file, "%s := T%d\n", name, i);
                    fflush(file);
                    i++;
                }
            }else{
                if(strcmp(right->right->info.type, "ID") == 0){
                    char *nameRO = right->right->info.name;
                        int val = right->left->info.value;
                        fprintf(file, "T%d := %d + %s\n", i, val, nameRO);
                        fprintf(file, "%s := T%d\n", name, i);
                        fflush(file);
                        i++;
                    }else{
                        int valR = right->right->info.value;
                        int valL = right->left->info.value;
                        fprintf(file, "T%d := %d + %d\n", i, valL, valR);
                        fprintf(file, "%s := T%d\n", name, i);
                        fflush(file);
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
    }else{
        exprClass(exprNode);
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

