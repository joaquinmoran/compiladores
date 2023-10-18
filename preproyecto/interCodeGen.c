#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "ast.h"
#include "symTable.h"
#include "interCodeGen.h"

int MAX_NODES = 100;
struct listNode *instrListHead = NULL;
bool listInitialized = false;



__attribute__((constructor))
void initialize_instrList() {
    if(!listInitialized){
        instrListHead = (struct listNode *)malloc(sizeof(struct listNode));
        if(instrListHead  == NULL){
            fprintf(stderr, "Error: can not assing memory. \n");
            exit(EXIT_FAILURE);
        }
        instrListHead->next = NULL;
        listInitialized = true
    }
}
struct listNode *newListNode(struct treeNode *left,struct treeNode *right, struct treeNode *info,char *instr){
    struct listNode *newNode = (struct listNode *)malloc(sizeof(struct listNode));

    if(newNode == NULL){
        fprintf(stderr, "Error: can not assing memory.\n");
        exit(EXIT_FAILURE);
    }

    newNode->left = left;
    newNode->right = right;
    newNode->info = info;
    

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
    printf("Se agrego: %s", newNode->instr); 
}

void printList(){
    struct listNode *currentNode = instrListHead->next; // Ignora el primer nodo que es el nodo de inicialización
    while(currentNode != NULL){
        printf("List Node: %s\n", currentNode->instr);
        currentNode = currentNode->next; // Avanza al siguiente nodo
    }
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
            declClassNode(currentNode);
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






