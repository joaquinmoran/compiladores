#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "symTable.h"

int error_flag = 0;

struct node *head = NULL;


__attribute__((constructor))
void initialize_list() {
    head = (struct node *)malloc(sizeof(struct node));
    if(head == NULL){
        fprintf(stderr, "Error: can not assing memory. \n");
        exit(EXIT_FAILURE);
    }
    head->next = NULL;
}



void addNodeToTable(struct node *newNode){
    struct node *aux = (struct node *)malloc(sizeof(struct node));
    struct node *aux1 = (struct node *)malloc(sizeof(struct node));
    if(head->next == NULL) {
        head->next = newNode;
        newNode->next = NULL;        
    }else{
        aux = head->next;
        while(aux != NULL) {
            if(strcmp(aux->info.name, newNode->info.name) == 0){
                printf("Redeclared variable. \n");
                error_flag = 1;
                break;
            }
            aux1 = aux;
            aux = aux->next;
        }
        if(aux == NULL){
            aux1->next = newNode;
            newNode->next = NULL;
            aux = newNode;
        }
    }
    printTable();
    
}

void printTable(){
    struct node *aux = (struct node *)malloc(sizeof(struct node));
    if(head->next == NULL){
        printf("EMPTY TABLE");
        return;
    }
    aux = head->next;
    while(aux != NULL){
        printf("Table symbol: %s = %s = %d \n", aux->info.type, aux->info.name, aux->info.value);
        aux = aux->next;
    }


}

bool setValueByName(int value, char *name){
    if(head->next != NULL){
        if(strcmp(head->next->info.name, name) == 0){
            printf("Old value: %d\n", head->next->info.value);
            head->next->info.value = value;
            printf("New value: %d\n", head->next->info.value);
            return true;
        }    
        struct node *aux = (struct node *)malloc(sizeof(struct node));
        aux = head->next;
        while(aux != NULL) {
            if(strcmp(aux->info.name,name) == 0){
                printf("Old value: %d\n", aux->info.value);
                aux->info.value = value;
                printf("New value: %d\n", aux->info.value);
                return true;
            }
            aux = aux->next;
        }
    }
    return false;
}

int getValueByName(char *name){
    if(head->next != NULL){
        if(strcmp(head->next->info.name, name) == 0){
            return head->next->info.value;
        }
        struct node *aux = (struct node *)malloc(sizeof(struct node));
        aux = head->next;
        while(aux != NULL){
            if(strcmp(aux->info.name, name) == 0){
                return aux->info.value;
            }
            aux = aux->next;
        }
    }
    error_flag = 1;
    return -9999; 
}

struct node *getNodeByName(char *name){
    if(head->next != NULL){
        if(strcmp(head->next->info.name, name) == 0){
            return head->next;
        }
        struct node *aux = (struct node *)malloc(sizeof(struct node));
        aux = head->next;
        while(aux != NULL){
            if(strcmp(aux->info.name, name) == 0){
                return aux;
            }
            aux = aux->next;
        }
    }
    error_flag = 1;
    return NULL; 
}

struct node *newTableNode(char *n, char *f, char *t, char *p, int v){
    struct node *sym = (struct node *)malloc(sizeof(struct node));

    if (sym == NULL) {
        fprintf(stderr, "Error: can not assing memory.\n");
        exit(EXIT_FAILURE);
    }

    sym->info.name = n;
    sym->info.flag = f;
    sym->info.type = t;
    sym->info.param = p;
    sym->info.value = v;

    return sym;
}