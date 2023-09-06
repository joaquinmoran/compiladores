#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "ast.h"



struct tree *newTree(struct treeNode info, struct tree *leftChild, struct tree *rightChild){

    struct tree *root = (struct tree *)malloc(sizeof(struct tree));

    printf("\n2");
    if(root == NULL) {
        printf("Error: null pointer");
    }else {
        printf("\n21");
        if((leftChild != NULL) && (rightChild != NULL)){
            printf("\n213");
            root->left = leftChild;
            root->right = rightChild;
        } else {
            printf("Null pointer error");
        }
        root->info = info;
    }
    printf("\n2134");
    printf(root->left->info.name);
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
    node->info.value = val;

    return node; 
}

