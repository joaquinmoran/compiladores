#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "ast.h"
#include "symTable.h"
#include "interCodeGen.h"

int MAX_NODES = 100;
int i;
struct listNode *instrListHead = NULL;
bool listInitialized = false;
char result[50];


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
        i=1;
    }
}
struct listNode *newListNode(char *instr){
    struct listNode *newNode = (struct listNode *)malloc(sizeof(struct listNode));

    if(newNode == NULL){
        fprintf(stderr, "Error: can not assing memory.\n");
        exit(EXIT_FAILURE);
    }

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
    
}

void printList(){
    struct listNode *currentNode = instrListHead->next; // Ignora el primer nodo que es el nodo de inicialización
    while(currentNode != NULL){
        printf("List Node: %s\n", currentNode->instr);
        currentNode = currentNode->next; // Avanza al siguiente nodo
    }
}

void declClassNode(struct tree *declNode){
    char *name = declNode->left->info.name;
    int val = declNode->right->info.value;
   

    sprintf(result, "T%d := %d\n", i, val);
    struct listNode *instrDeclNode1 = newListNode(result);
    addNodeToList(instrDeclNode1);
    
    sprintf(result, "%s := T%d\n", name, i);
    struct listNode *instrDeclNode2 = newListNode(result);
    addNodeToList(instrDeclNode2);
    i++;
}

char *exprClass(struct tree *exprNode){
    char *name = exprNode->left->info.name;
    struct listNode *instrExprNode;
    char retStm[10];
    char *op = exprNode->info.name;

    struct tree *right = exprNode;
    if(strcmp(right->left->info.type, "ID") == 0){
        if(strcmp(right->right->info.type, "ID") == 0){
            char *nameLO = right->left->info.name;
            char *nameRO = right->right->info.name;
            sprintf(result,"T%d := %s %s %s\n", i, nameLO, op, nameRO);
            instrExprNode = newListNode(result);
            addNodeToList(instrExprNode);
            sprintf(retStm,"T%d",i);  
            i++;
        }else{
            char *nameLO = right->left->info.name;
            int val = right->right->info.value;
            sprintf(result,"T%d := %s %s %d\n", i, nameLO, op, val);
            instrExprNode = newListNode(result);
            addNodeToList(instrExprNode);
            sprintf(retStm, "T%d",i);
            i++;
        }
    }else{
        if(strcmp(right->right->info.type, "ID") == 0){
            char *nameRO = right->right->info.name;
            int val = right->left->info.value;
            sprintf(result, "T%d := %d %s %s\n", i, val, op, nameRO);
            instrExprNode = newListNode(result);
            addNodeToList(instrExprNode);
            sprintf(retStm,"T%d",i);
            i++;
        }else{
            int valR = right->right->info.value;
            int valL = right->left->info.value;
            sprintf(result, "T%d := %d %s %d\n", i, valL, op, valR);
            instrExprNode = newListNode(result);
            addNodeToList(instrExprNode);
            sprintf(retStm, "T%d",i);
            i++;
        }
    }
    return strdup(retStm);

}

void assigClass(struct tree *assigNode){
    char *tValorLeft;
    char *tValorRight;
    bool hasLeftExpr = false;
    bool hasRightExpr = false;

    struct listNode *instrAssigNode1;
    struct listNode *instrAssigNode2;

    if(assigNode == NULL){
        return;
    }

    char *op = assigNode->right->info.name;
    char *name = assigNode->left->info.name; // variable assignment ID (example, x := 2* 2)

    if(strcmp(assigNode->info.name, "ASSIG->EXPR") == 0){
        struct tree *rightPart = assigNode->right;
        if(strcmp(rightPart->left->info.type, "EXPR") == 0){
            tValorLeft = exprClass(assigNode);
            hasLeftExpr = true;
        }
        if(strcmp(rightPart->right->info.type, "EXPR") == 0){
            tValorRight = exprClass(assigNode);
            hasRightExpr = true;
        }
        if(strcmp(rightPart->left->info.type, "ID") == 0){
            if(strcmp(rightPart->right->info.type, "ID") == 0){
                char *nameLO = rightPart->left->info.name;
                char *nameRO = rightPart->right->info.name;    
                if(hasLeftExpr && hasRightExpr){
                    sprintf(result, "T%d := %s %s %s\n", i, tValorLeft, op, tValorRight);
                    instrAssigNode1 = newListNode(result);
                    addNodeToList(instrAssigNode1);
                
                    sprintf(result, "%s := T%d\n", name, i);
                    instrAssigNode2 = newListNode(result);
                    addNodeToList(instrAssigNode2);     
                }else{
                    sprintf(result, "T%d := %s %s %s\n", i, nameLO, op, nameRO);
                    instrAssigNode1 = newListNode(result);
                    addNodeToList(instrAssigNode1);
                
                    sprintf(result, "%s := T%d\n", name, i);
                    instrAssigNode2 = newListNode(result);
                    addNodeToList(instrAssigNode2);
                }
                i++;
            }else{
                char *nameLO = rightPart->left->info.name;
                int val = rightPart->right->info.value;
                if(hasLeftExpr){
                    sprintf(result, "T%d := %s %s %d\n", i, tValorLeft, op, val);
                    instrAssigNode1 = newListNode(result);
                    addNodeToList(instrAssigNode1);

                    sprintf(result, "%s := T%d\n", name, i);
                    instrAssigNode2 = newListNode(result);
                    addNodeToList(instrAssigNode2);
                }else{
                    sprintf(result, "T%d := %s %s %d\n", i, nameLO, op, val);
                    instrAssigNode1 = newListNode(result);
                    addNodeToList(instrAssigNode1);

                    sprintf(result, "%s := T%d\n", name, i);
                    instrAssigNode2 = newListNode(result);
                    addNodeToList(instrAssigNode2);
                }
                i++;
            }
        }else{
             if(strcmp(rightPart->right->info.type, "ID") == 0){
                    char *nameRO = rightPart->right->info.name;
                    int val = rightPart->left->info.value;
                    if(hasRightExpr){
                        sprintf(result, "T%d := %d %s %s\n", i, val, op, tValorRight);
                        instrAssigNode1 = newListNode(result);
                        addNodeToList(instrAssigNode1);

                        sprintf(result, "%s := T%d\n", name, i); 
                        instrAssigNode2 = newListNode(result);
                        addNodeToList(instrAssigNode2);
                    }else{
                        sprintf(result, "T%d := %d %s %s\n", i, val, op, nameRO);
                        instrAssigNode1 = newListNode(result);
                        addNodeToList(instrAssigNode1);

                        sprintf(result, "%s := T%d\n", name, i);
                        instrAssigNode2 = newListNode(result);
                        addNodeToList(instrAssigNode2);
                    }
                    i++;
             }else{
                int valR = rightPart->right->info.value;
                int valL = rightPart->left->info.value;
                if(hasRightExpr){
                    sprintf(result, "T%d := %d %s %s\n", i, valL, op, tValorRight);
                    instrAssigNode1 = newListNode(result);
                    addNodeToList(instrAssigNode1);

                    sprintf(result, "%s := T%d\n", name, i);
                    instrAssigNode2 = newListNode(result);
                    addNodeToList(instrAssigNode2);
                }else{
                    if(hasLeftExpr){
                        sprintf(result,  "T%d := %s %s %d\n", i, tValorLeft, op,valR);
                        instrAssigNode1 = newListNode(result);
                        addNodeToList(instrAssigNode1); 

                        sprintf(result, "%s := T%d\n", name, i);
                        instrAssigNode2 = newListNode(result);
                        addNodeToList(instrAssigNode2);
                    }else{
                        sprintf(result, "T%d := %d %s %d\n", i, valL, op, valR);
                        instrAssigNode1 = newListNode(result);
                        addNodeToList(instrAssigNode1); 

                        sprintf(result, "%s := T%d\n", name, i);
                        instrAssigNode2 = newListNode(result);
                        addNodeToList(instrAssigNode2);
                    }
                }
                i++;
             }
        }
        
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
    printList();
}


