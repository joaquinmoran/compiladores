#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "ast.h"
#include "symTable.h"
#include "interCodeGen.h"

int MAX_NODES = 100;
int i = 1;
struct listNode *instrListHead = NULL;


__attribute__((constructor))
void initialize_instrList() {
    instrListHead = (struct listNode *)malloc(sizeof(struct listNode));
    if(instrListHead  == NULL){
        fprintf(stderr, "Error: can not assing memory. \n");
        exit(EXIT_FAILURE);
    }
    instrListHead ->next = NULL;
}

struct listNode *newListNode(char *instr){
    struct listNode *newNode = (struct listNode *)malloc(sizeof(struct listNode));

    if(newNode == NULL){
        fprintf(stderr, "Error: can not assing memory.\n");
        exit(EXIT_FAILURE);
    }

    newNode->instr = instr;

    return newNode;
}

void addNodeToList(struct listNode *newNode){
    struct listNode *aux = (struct listNode *)malloc(sizeof(struct listNode));
    struct listNode *aux1 = (struct listNode *)malloc(sizeof(struct listNode));
    if(instrListHead->next == NULL){
        instrListHead->next = newNode;
        newNode->next = NULL;
    }else{
        aux = instrListHead->next;
        while(aux != NULL) {
            aux1 = aux;
            aux = aux->next;
        }
        if(aux == NULL){
            aux1->next = newNode;
            newNode->next = NULL;
        }
    }
    printList();
} 

void printList(){
    struct listNode *aux = (struct listNode *)malloc(sizeof(struct listNode));
    if(instrListHead->next == NULL){
        printf("EMPTY TABLE");
        return;
    }
    aux = instrListHead->next;
    while(aux != NULL){
        printf("List Node: %s\n", aux->instr);
        aux = aux->next;
    }


}

void declClassNode(struct tree *declNode){
    char *name = declNode->left->info.name;
    int val = declNode->right->info.value;
    char result[50];

    sprintf(result, "T%d := %d\n", i, val);
    struct listNode *node1 = newListNode(result);
    printf("%s",node1->instr);
    addNodeToList(node1);
    sprintf(result, "%s := T%d\n", name, i);
    struct listNode *node2 = newListNode(result);
    printf("%s",node2->instr);
    addNodeToList(node2);
    i++;
}


void breadthFirstTraversal(struct tree *root){
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
            declClassNode(currentNode);
        }
        if(currentNode->left != NULL){
            queue[++back] = currentNode->left;
        }
        if(currentNode->right != NULL){
            queue[++back] = currentNode->right;
        }
    }
}


