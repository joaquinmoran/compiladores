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

    if(strcmp(exprNode->info.name,"IVALUE") != 0){
        if(strcmp(exprNode->info.type, "ID") != 0){
            struct listNode *instr = newListNode(leftChild,rightChild, exprNode->info, exprNode->info.name);
            addNodeToList(instr);
            return instr->result;
        }
    }

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

void retClass(struct tree *retNode){
    if(strcmp(retNode->left->info.type,"ID") == 0 || strcmp(retNode->info.name,"IVALUE") == 0){
        struct listNode *instr = newListNode(retNode->left->info, nullNode, nullNode, retNode->info.name);
        addNodeToList(instr);
    }else{
        struct treeNode leftChild = exprClass(retNode->left);
        printf("RETURN LEFT IS: %d\n",leftChild.value);
        struct listNode *instr = newListNode(leftChild, nullNode, nullNode, retNode->info.name);
        addNodeToList(instr);
    }
}

void printListOfInstr(){
    struct listNode *currentNode = instrListHead;

    while(currentNode != NULL){
        printf("Instruction is: %s\n", currentNode->instr);
        if(currentNode->left.type != NULL && currentNode->left.name != NULL && currentNode->left.value != -999 ){
            printf("Left is: %s\n", currentNode->left.type);
            printf("Left is: %s\n", currentNode->left.name);
            printf("Left is: %d\n", currentNode->left.value);
        }
        if(currentNode->right.type != NULL && currentNode->right.name != NULL && currentNode->right.value != -999){
            printf("Right is: %s\n", currentNode->right.type);
            printf("Right is: %s\n", currentNode->right.name);
            printf("Right is: %d\n", currentNode->right.value);
        }
        if(currentNode->result.type != NULL && currentNode->result.name != NULL && currentNode->result.value != -999){
            printf("Result is: %s\n", currentNode->result.type);
            printf("Result is: %s\n", currentNode->result.name);
            printf("Result is: %d\n", currentNode->result.value);
        }
        currentNode = currentNode->next;    
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
            declClass(currentNode);
        }

        if(strcmp(currentNode->info.type, "ASSIG") == 0){
            assigClass(currentNode);
        }
        if(strcmp(currentNode->info.name,"RETURN") == 0){
            retClass(currentNode);
        }
        if(currentNode->left != NULL){
            queue[++back] = currentNode->left;
        }
        if(currentNode->right != NULL){
            queue[++back] = currentNode->right;
        }
    }
    printListOfInstr();
}