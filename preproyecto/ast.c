#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "ast.h"



struct tree *newTree(struct treeNode info, struct tree *leftChild, struct tree *rightChild){

    struct tree *root = (struct tree *)malloc(sizeof(struct tree));

    if(root == NULL) {
        printf("Error: null pointer");
    }else {
        if((leftChild != NULL) && (rightChild != NULL)){
            root->left = leftChild;
            root->right = rightChild;
        } else {
            printf("Null pointer error");
        }
        root->info = info;
    }
    return root;
}

struct tree *newNode(char *t, char *n, int val){
    struct tree *node = (struct tree *)malloc(sizeof(struct tree)); 

    if(node == NULL){
        return NULL;
    }

    if(t != NULL && n != NULL){
        node->info.type = strdup(t);
        node->info.name = strdup(n);
    } else {
        printf("Null argument error");
    }
    if(val != NULL) {
        node->info.value = val;
    }


    return node; 
}

void printNode(struct tree *tree){
    if(tree != NULL){
        printf("Root info: ");
        printf("Type: %s\n", tree->info.type);
        printf("Name: %s\n", tree->info.name);
        printf("Value: %d\n", tree->info.value);
    }
    printf("\n");

    if(tree->left != NULL){
        printf("Left child info: ");
        printf("Type: %s\n", tree->left->info.type);
        printf("Name: %s\n", tree->left->info.name);
        printf("Value: %d\n", tree->left->info.value);
    }
    printf("\n");

    if(tree->right != NULL){
        printf("Right child info: ");
        printf("Type: %s\n", tree->right->info.type);
        printf("Name: %s\n", tree->right->info.name);
        printf("Value: %d\n", tree->right->info.value);
    }
}