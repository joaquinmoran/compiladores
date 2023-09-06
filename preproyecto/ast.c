#include <stdio.h>
#include <stdlib.h>
#include "ast.h"



struct tree *newTree(struct treeNode info, struct tree *leftChild, struct tree *rightChild){

    struct tree *root = (struct tree *)malloc(sizeof(struct tree));

    if(root == NULL) {
        return NULL;
    }

    root->left = leftChild;
    root->right = rightChild;
    root->info = info;

    return root;
}

struct tree *newNode(char *t, char *n, int val){
    struct tree *node = (struct tree *)malloc(sizeof(struct tree)); 

    if(node == NULL){
        return NULL;
    }

    node->left = NULL;
    node->right = NULL;

    node->info.type = strdup(t);
    node->info.name = strdup(n);
    node->info.value = val;

    return node;
    
}