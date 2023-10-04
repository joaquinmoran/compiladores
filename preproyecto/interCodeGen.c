#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "ast.h"
#include "symTable.h"


struct tree *expressionClass(struct tree *exprNode){
    int i = 1;
    FILE *file = fopen("intermediate_code_generated.txt", "w");
    if(file == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    printf("Name: %s\n", exprNode->info.name);
    if(exprNode == NULL){
        printf("NULL ERROR");
        exit(EXIT_FAILURE);
    }
    if((strcmp(exprNode->info.type, "ID") == 0) || (strcmp(exprNode->info.type, "INT") == 0)){
        return exprNode;
    }
    if(strcmp(exprNode->info.name,"ASSIG-EXPR") == 0){
        struct tree *leftOp = expressionClass(exprNode->left);
        struct tree *rightOp = expressionClass(exprNode->right);
        if(strcmp(exprNode->info.name,"SUM") == 0){
            int valLeft = getValueByName(leftOp->info.name);
            int valRight = getValueByName(rightOp->info.name);
            int temp = exprNode->info.value;
            fprintf(file, "T%d := %d + %d", i, valLeft, valRight);
            fflush(file);
            i++;
            fclose(file);
            struct tree *resProd = newNode("EXPR", "SUM", valLeft * valRight);
            return resProd;
        }
    }
    // if(strcmp(exprNode->info.name,"PROD") == 0){
    //     struct tree *leftOp = expressionClass(exprNode->left);
    //     struct tree *rightOp = expressionClass(exprNode->right);
    //     int valLeft = getValueByName(leftOp->info.name);
    //     int valRight = getValueByName(rightOp->info.name);
    //     int temp = exprNode->info.value;
    //     fprintf(file, "T%d := %d * %d", i, valLeft, valRight);
    //     i++;
    //     fclose(file);
    //     struct tree *resProd = newNode("EXPR", "PROD", valLeft * valRight);
    //     return resProd;
    // }
    // if(strcmp(exprNode->info.name,"SUBT") == 0){
    //     struct tree *leftOp = expressionClass(exprNode->left);
    //     struct tree *rightOp = expressionClass(exprNode->right);
    //     int valLeft = getValueByName(leftOp->info.name);
    //     int valRight = getValueByName(rightOp->info.name);
    //     int temp = exprNode->info.value;
    //     fprintf(file, "T%d := %d - %d", i, valLeft, valRight);
    //     i++;
    //     fclose(file);
    //     struct tree *resSubt = newNode("EXPR", "SUBT", valLeft - valRight);
    //     return resSubt;
    // }
    
    fclose(file);
}

void assignmentClass(struct  tree *assigNode){

}


void traverseAST(struct tree *node) {
    if(node == NULL){
        return;
    }
    printf("%s", node->info.type);
    if(strcmp(node->info.type, "ASSIG") == 0){
        struct tree *c = expressionClass(node);
    }
    // if(strcmp(node->info.type, "ASSIG") == 0){
    //     assignmentClass(node);
    // }

    // if(node->left != NULL && node->right != NULL){
    //     traverseAST(node->left);
    //     traverseAST(node->right);
    // }
}


