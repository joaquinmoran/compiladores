#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "ast.h"



struct tree *newTree(struct treeNode info, struct tree *leftChild, struct tree *rightChild){

    struct tree *root = (struct tree *)malloc(sizeof(struct tree));

    

    if(root == NULL) {
        printf("Error: null pointer");
    }else {
        root->left = leftChild;
        root->right = rightChild;
        root->info = info;
    }
    return root;
}

struct tree *newNode(char * eType, char *t, char *n, int val){
    struct tree *node = (struct tree *)malloc(sizeof(struct tree)); 

    
    if(node == NULL){
        return NULL;
    }

    node->info.exprType = malloc(strlen(eType) + 1);
    node->info.type = malloc(strlen(t) + 1);
    node->info.name = malloc(strlen(n) + 1);
    if(node->info.name == NULL || node->info.exprType == NULL ||
        node->info.type == NULL){
            fprintf(stderr, "Error: can not assing memory.\n");
            exit(EXIT_FAILURE);
    }
    strcpy(node->info.name, n);
    strcpy(node->info.type, t);
    strcpy(node->info.exprType, eType);
   
    node->info.value = val;


    return node; 
}


void inOrderPrint(struct tree *tree){
    if(tree == NULL){
        return;
    }
    inOrderPrint(tree->left);

    printf("Es: %s\n",tree->info.type);

    inOrderPrint(tree->right);
}


void printNode(struct tree *tree){
    if(tree != NULL){
        printf("Root info: ");
        printf("Type: %s\n", tree->info.type);
        printf("Name: %s\n", tree->info.name);
        printf("Value: %d\n", tree->info.value);
    }
    printf("SE MOSTRO LA RAIZ\n");

    if(tree->left != NULL){
        printf("Left child info: ");
        printf("Type: %s\n", tree->left->info.type);
        printf("Name: %s\n", tree->left->info.name);
        printf("Value: %d\n", tree->left->info.value);
    }
    printf("HIJO IZQUIERDO DE TAL RAIZ\n");

    if(tree->right != NULL){
        printf("Right child info: ");
        printf("Type: %s\n", tree->right->info.type);
        printf("Name: %s\n", tree->right->info.name);
        printf("Value: %d\n", tree->right->info.value);
    }
    printf("HIJO DERECHA DE TAL RAIZ\n");

}