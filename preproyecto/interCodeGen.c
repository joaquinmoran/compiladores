#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "ast.h"
#include "symTable.h"
#include "interCodeGen.h"

int MAX_NODES = 100;
struct listNode *instrListHead = NULL;
bool listInitialized = false;
struct treeNode nullNode = {NULL,NULL,-1}; // porque al poner solo NULL no lo acepta



__attribute__((constructor))
void initialize_instrList() {
    if(!listInitialized){
        instrListHead = (struct listNode *)malloc(sizeof(struct listNode));
        if(instrListHead  == NULL){
            fprintf(stderr, "Error: can not assing memory. \n");
            exit(EXIT_FAILURE);
        }
        instrListHead->next = NULL;
        listInitialized = true;
    }
}
struct listNode *newListNode(struct treeNode left,struct treeNode right, struct treeNode info,char *instr){
    struct listNode *newNode = (struct listNode *)malloc(sizeof(struct listNode));

    if(newNode == NULL){
        fprintf(stderr, "Error: can not assing memory.\n");
        exit(EXIT_FAILURE);
    }

    newNode->left = left;
    newNode->right = right;
    newNode->result = info;
    
    newNode->instr = malloc(strlen(instr) + 1); // Asignar memoria para la cadena
    if(newNode->instr == NULL){
        fprintf(stderr, "Error: can not assing memory.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->instr, instr); // Copiar la cadena

    return newNode;
}

void addNodeToList(struct listNode *newNode){
    struct listNode *aux = instrListHead;
    while(aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = newNode;
    newNode->next = NULL;
    printf("%s\n", newNode->instr); 
}

struct treeNode exprClass(struct tree *exprNode){

    if(exprNode == NULL){
        return;
    }

    struct treeNode leftChild = {NULL, NULL, -1};
    struct treeNode rightChild = {NULL, NULL, -1};
    if(exprNode->left != NULL && strcmp(exprNode->left->info.type,"EXPR") == 0){
            leftChild = exprClass(exprNode->left);
        
    }
    if(exprNode->right != NULL && strcmp(exprNode->left->info.type, "EXPR") == 0){
            rightChild = exprClass(exprNode->right);
    }


    if(leftChild.type == NULL && leftChild.name == NULL && leftChild.value == -1){
        if(exprNode->left != NULL){
            leftChild = exprNode->left->info;
        }
    }
    if(rightChild.type == NULL && rightChild.name == NULL && rightChild.value == -1){
        if(exprNode->right != NULL){
            rightChild = exprNode->right->info;
        }
    }
    
    struct listNode *instr = newListNode(leftChild,rightChild, exprNode->info, exprNode->info.name);
    addNodeToList(instr);
    return instr->result;

}

void declClass(struct tree *declNode){
    struct listNode *newNode;

    newNode = newListNode(declNode->left->info, declNode->right->info, nullNode, declNode->info.type);
    addNodeToList(newNode);
}


void assigClass(struct tree *assigNode){
    struct treeNode leftChild = assigNode->left->info;
    struct treeNode rightChild = exprClass(assigNode->right);
    struct listNode *instr = newListNode(leftChild, rightChild, nullNode, assigNode->info.type);
    addNodeToList(instr);
}



void breadthFirstTraversal(struct tree *root){

    if(root == NULL){
        return;
    }
    initialize_instrList();

    struct tree *queue[MAX_NODES];
    int front = -1;
    int back = -1;
    queue[++back] = root;

    while(front != back) {
        struct tree *currentNode = queue[++front];
        if(strcmp(currentNode->info.type, "DECL") == 0){
            declClass(currentNode);
        }

        if(strcmp(currentNode->info.type, "ASSIG") == 0){
            assigClass(currentNode);
        }
        if(currentNode->left != NULL){
            queue[++back] = currentNode->left;
        }
        if(currentNode->right != NULL){
            queue[++back] = currentNode->right;
        }
    
    }
}