%{

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "ast.h"
#include "symTable.h"
#include "interCodeGen.h"

extern int yylineno;
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






%}
%union { int i; char *s; struct tree *t}


%token<i> INT
%token<s> ID
%token<s> TBOOL
%token<s> FBOOL
%token TMENOS
%token TEQ
%token<s> INTEGER
%token<s> BOOLEAN
%token<t> RETURN

%type<t> expr
%type<t> IVALOR
%type<t> prog
%type<t> TYPE
%type<t> VAR
%type<t> decl
%type<t> assig
%type<t> ret;


%left '+' TMENOS
%left '*'

%%



prog:  decl ';'      {
                        struct tree *declTree = $1;
                        $$ = declTree;
                    }

    | assig ';'     {
                        struct tree *assigTree = $1;
                        // breadthFirstTraversal(assigTree);
                        $$ = assigTree;
                     }


    | decl ';' prog     {
                            struct tree *lc = $1;
                            struct tree *rc = $3;
                            struct tree *declProgTree;
                            if(lc == NULL && rc == NULL) {
                                printf("NULL POINTER ERROR \n");
                            }else {
                                declProgTree = newTree( newNode("PROG", "DECL->PROG",-1)->info, lc,rc);
                            }
                            breadthFirstTraversal(declProgTree);
                            $$ = declProgTree;
                        }

    | assig ';' prog {
                        struct tree *lc = $1;
                        struct tree *rc = $3;
                        struct tree *assigProgTree;
                        if(lc == NULL && rc == NULL) {
                            printf("NULL POINTER ERROR \n");
                        }else {
                            assigProgTree = newTree( newNode("PROG", "ASSIG->PROG",-1)->info, lc,rc);
                        }
                        $$ = assigProgTree;
                     }
    | ret ';'       {
                        struct tree *retTree = $1;
                        if(strcmp(retTree->info.type, "BOOLEAN") == 0){
                            if(retTree->info.value != 0){
                                printf("True\n");
                            }else{
                                printf("False\n");
                            }
                        }else {
                            return("Result: %d\n", retTree->info.value);
                        }
                        $$ = retTree;
                    }

    | ret ';' prog   { 
                        struct tree *lc = $1;
                        struct tree *rc = $3;
                        struct tree *retAssigTree;
                        if(strcmp(lc->info.type, "BOOLEAN") == 0){
                                if(lc->info.value != 0){
                                    printf("True\n");
                                }else{
                                    printf("False\n");
                                }
                            }else {
                                    printf("Result: %d\n", lc->info.value);
                            }
                                
                        if(lc == NULL && rc == NULL){
                            printf("NULL POINTER ERROR");
                        } else {
                            retAssigTree = newTree(newNode("PROG", "RET->PROG",-1)->info, lc, rc);
                            
                        }
                        if(retAssigTree != NULL){
                            $$ = retAssigTree;
                        }else {
                            printf("NULL POINTER ERROR");
                        }
                        
                     }

    ;


expr: IVALOR            {
                            struct tree *iVal = $1;
                            $$ = iVal;
                        }

    | VAR               {
                            struct tree *iVar = $1;
                            int val = getValueByName(iVar->info.name);
                            if(error_flag){
                                printf("ERROR(undeclared variable in line %d).\n", yylineno);
                                printf("Aborting compilation...\n");
                                exit(EXIT_FAILURE);
                            }
                            iVar->info.value = val;
                            $$ = iVar;
                        }

    | expr '+' expr  {  
                        struct tree *genTree;
                        struct tree *lc = newNode("LO", "LEFTOPERATOR", $1->info.value);
                        struct tree *rc = newNode("RO", "RIGHTOPERATOR", $3->info.value);
                        genTree = newTree( newNode("EXPR", "SUM", (lc->info.value + rc->info.value))->info, lc, rc);
                        if(genTree == NULL){
                            printf("NULL POINTER ERROR \n");
                        }else {
                            $$ = genTree;
                        }

                     }

    | expr '*' expr {
                        struct tree *genTree;
                        struct tree *lc = newNode("LO", "LEFTOPERATOR", $1->info.value);
                        struct tree *rc = newNode("RO", "RIGHTOPERATOR", $3->info.value);  
                        genTree = newTree( newNode("EXPR", "PROD", (lc->info.value * rc->info.value))->info, lc, rc);
                        if(genTree == NULL){
                            printf("NULL POINTER ERROR \n");
                        }else {
                            $$ = genTree;
                        }
                    }

    | '(' expr ')'  {$$ = $2;}


    | expr TMENOS expr {
                            struct tree *genTree;
                            struct tree *lc = newNode("LO", "LEFTOPERATOR", $1->info.value);
                            struct tree *rc = newNode("RO", "RIGHTOPERATOR", $3->info.value);
                            genTree = newTree( newNode("EXPR", "SUBT", (lc->info.value - rc->info.value))->info, lc, rc);
                            if(genTree == NULL){
                                printf("NULL POINTER ERROR \n");
                            }else {
                                $$ = genTree;
                            }
                        }

    ;

decl: TYPE VAR TEQ expr
                            {
                                struct tree *i = $1;
                                struct tree *lc = $2;
                                struct tree *rc = $4;
                                if(i->info.type != NULL && lc->info.name != NULL){
                                    struct node *sym = newTableNode(lc->info.name, "VARIABLE", i->info.type, NULL, rc->info.value);
                                    addNodeToTable(sym);
                                    if(error_flag){
                                        printf("ERROR(redeclared variable in line %d). \n", yylineno);
                                        printf("Aborting compilation...\n");
                                        exit(EXIT_FAILURE);
                                    }
                                }else{
                                     printf("NULL POINTER ERROR");
                                }
                                struct tree *genTree = newTree( newNode("DECL",i->info.type,-1)->info, lc, rc);
                                $$ = genTree;
                             }


    ;

assig: VAR TEQ expr     {
                            struct tree *lc = $1;
                            struct tree *rc = $3;
                            struct tree *genTree;
                            if(lc == NULL && rc == NULL){
                                printf("NULL POINTER ERROR \n");
                            }else {
                                genTree = newTree( newNode("ASSIG", "ASSIG-EXPR", rc->info.value)->info, lc, rc);
                                bool var = setValueByName(rc->info.value, lc->info.name);
                                if(var != true){
                                    printf("ERROR(undeclared variable in line %d).\n", yylineno);
                                    printf("Aborting compilation...\n");
                                    exit(EXIT_FAILURE);
                                }
                            }
                            if(genTree == NULL){
                                printf("NULL POINTER ERROR \n");
                            }else {
                                $$ = genTree;
                            }
                        }

    
    ;


TYPE: INTEGER       {$$ = newNode("INTEGER","NULL", -1);}

    | BOOLEAN       {$$ = newNode("BOOLEAN","NULL",-1);}
    ;

VAR: ID             {  $$ = newNode("ID",$1,-1);}
    ;

IVALOR: INT         {
                        struct tree *intValueTree = newNode("INT", "IVALUE", $1);
                        $$  = intValueTree;
                    }

        | TBOOL     {   
                        struct tree *tBoolValueTree = newNode("TBOOL", "TVALUE", 1);
                        $$  = tBoolValueTree;
                    }

        | FBOOL     {   
                        struct tree *fBoolValueTree = newNode("FBOOL", "FVALUE", 0);
                        $$  = fBoolValueTree;
                    }
     ;


ret: RETURN expr   {   
                        struct node *node = getNodeByName($2->info.name);
                        struct tree *retTree;
                        if(strcmp(node->info.type, "BOOLEAN")==0){
                           retTree = newNode("BOOLEAN", "RETUN-EXPR", $2->info.value);   
                        }else {
                            retTree = newNode("INTEGER", "RETUN-EXPR", $2->info.value);   
                        }

                        if(retTree != NULL){
                            $$ = retTree;
                        }else {
                            printf("NULL RETURN");
                        }
                    }

    ;

%%


