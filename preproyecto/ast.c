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

struct treeNode *newNode(char *t, char *n, int val){
    struct treeNode *node = (struct treeNode *)malloc(sizeof(struct treeNode)); 

    if(node == NULL){
        return NULL;
    }

    node->type = t;
    node->name = n;
    node->value = val;

    return node;
    
}