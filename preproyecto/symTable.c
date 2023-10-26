#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "symTable.h"

int error_flag = 0;
int offset = -8;

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
        printf("EL NAME DE NEW NODE ES: %s\n",newNode->info.name);
        while(aux != NULL) {
            if(strcmp(aux->info.name, newNode->info.name) == 0){
                printf("Redeclared variable. \n");
                printf("EL NAME DE LO QUE ESTA EN LA LISTA ES: %s\n", aux->info.name);
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
        printf("Table symbol: %s %s == %d \n", aux->info.type, aux->info.name, aux->info.value);
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

int getOffsetByName(char *name){
    struct node *node = getNodeByName(name);
    return node->info.offset;
} 

struct node *newTableNode(char *n, char *f, char *t, char *p, int v){
    struct node *sym = (struct node *)malloc(sizeof(struct node));

    if (sym == NULL) {
        fprintf(stderr, "Error: can not assing memory.\n");
        exit(EXIT_FAILURE);
    }

    sym->info.name = malloc(strlen(n) + 1);
    sym->info.flag = malloc(strlen(f) + 1);
    sym->info.type = malloc(strlen(t) + 1);
    if(sym->info.name == NULL || sym->info.flag == NULL ||
        sym->info.type == NULL){
            fprintf(stderr, "Error: can not assing memory.\n");
            exit(EXIT_FAILURE);
    }
    strcpy(sym->info.name, n);
    strcpy(sym->info.flag, f);
    strcpy(sym->info.type, t);
    
    if(p != NULL){
        sym->info.param = malloc(strlen(p) + 1);
        strcpy(sym->info.param, p);
    }
    sym->info.value = v;
    sym->info.offset = offset;
    offset = offset - 8;

    return sym;
}