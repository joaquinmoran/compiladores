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
   
    node->info.value = val;
    


    return node; 
}

// void generateDotFile(FILE *dotFile, struct tree *node, int i) {
//     if (node == NULL) {
//         return;
//     }

//     fprintf(dotFile, "%d [label=\"%s, %s, %d\"];\n", i, node->info.type, node->info.name, node->info.value);

//     if (node->left != NULL) {
//         fprintf(dotFile, "%d -> %s;\n", i, node->left->info.name);
//         generateDotFile(dotFile, node->left, i++);
//     }

//     if (node->right != NULL) {
//         fprintf(dotFile, "%d -> %s;\n", i, node->right->info.name);
//         generateDotFile(dotFile, node->right, i++);
//     }
// }

// void saveDotFile(struct tree *root) {
//     FILE *dotFile = fopen("tree.dot", "w");
//     int i = 0;
//     if (dotFile == NULL) {
//         printf("Error: No se pudo abrir el archivo .dot");
//         return;
//     }

//     fprintf(dotFile, "digraph Tree {\n");
//     generateDotFile(dotFile, root, i);
//     fprintf(dotFile, "}\n");
//     fclose(dotFile);
// }


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