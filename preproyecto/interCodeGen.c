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

    if(exprNode == NULL){
        return;
    }

    if(strcmp(exprNode->info.name, "SUM") == 0){
    // T2 := SUM T1 3

    }

    if(strcmp(exprNode->info.name, "PROD") == 0){
        if(strcmp(exprNode->left->info.type, "ID") == 0){
            if(strcmp(exprNode->right->info.type, "ID") == 0){
                char *nameLO = exprNode->left->info.name;
                char *nameRO = exprNode->right->info.name;
                fprintf(file, "T%d := %s * %s\n", i, nameLO, nameRO);
                fflush(file);
                i++;
            }else{
                char *nameLO = exprNode->left->info.name;
                int val = exprNode->right->info.value;
                fprintf(file, "T%d := %s * %d\n", i, nameLO, val);
                fflush(file);
                i++;
            }
        }else{
            if(strcmp(exprNode->right->info.type, "ID") == 0){
                 char *nameRO = exprNode->right->info.name;
                    int val = exprNode->left->info.value;
                    fprintf(file, "T%d := %d * %s\n", i, val, nameRO);
                    fflush(file);
                    i++;
                }else{
                    int valR = exprNode->right->info.value;
                    int valL = exprNode->left->info.value;
                    fprintf(file, "T%d := %d * %d\n", i, valL, valR);
                    fflush(file);
                    i++;
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
        if(strcmp(currentNode->info.type, "DECL") == 0){
            declClass(currentNode);
        }
        if(strcmp(currentNode->info.type, "EXPR") == 0){
            exprClass(currentNode);
        }
        printf("TYPE: %s, VALUE: %d NAME: %s \n", currentNode->info.type, currentNode->info.value, currentNode->info.name);

        if(currentNode->left != NULL){
            queue[++back] = currentNode->left;
        }
        if(currentNode->right != NULL){
            queue[++back] = currentNode->right;
        }
    }

    fclose(file);
}

