%{

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "ast.h"
#include "symTable.h"
#include "interCodeGen.h"

extern int yylineno;

extern int error_flag;

extern struct tree *ast = NULL;



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
                        struct tree *declTree = $1;//newTree(newNode("DECL ; EMPTY ", "SIMPLE", -1)->info, $1, NULL);
                        ast = declTree;
                        $$ = declTree;
                    }

    | assig ';'     {
                        struct tree *assigTree = $1;
                        ast = assigTree;
                        $$ = assigTree;
                     }


    | decl ';' prog     {
                            struct tree *lc = $1;
                            struct tree *rc = $3;
                            struct tree *declProgTree;
                            if(lc == NULL && rc == NULL) {
                                printf("NULL POINTER ERROR \n");
                            }else {
                                declProgTree = newTree( newNode("DECL ; PROG", "DECL->PROG",-1)->info, lc,rc);
                            }
                            ast = declProgTree;
                            $$ = declProgTree;
                        }

    | assig ';' prog {
                        struct tree *lc = $1;
                        struct tree *rc = $3;
                        struct tree *assigProgTree;
                        if(lc == NULL && rc == NULL) {
                            printf("NULL POINTER ERROR \n");
                        }else {
                            assigProgTree = newTree( newNode("ASSIG ; PROG", "ASSIG->PROG",-1)->info, lc,rc);
                        }
                        ast = assigProgTree;
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
                            printf("Result: %d\n", retTree->info.value);
                        }
                        ast = retTree;
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
                            retAssigTree = newTree(newNode("RET ; PROG", "RET->PROG",-1)->info, lc, rc);
                            
                        }
                        if(retAssigTree != NULL){
                            $$ = retAssigTree;
                        }else {
                            printf("NULL POINTER ERROR");
                        }
                        ast = retAssigTree;
                        $$ = retAssigTree;
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
                        struct tree *lc = $1;
                        struct tree *rc = $3;
                        genTree = newTree( newNode("EXPR", "SUM", (lc->info.value + rc->info.value))->info, lc, rc);
                        if(genTree == NULL){
                            printf("NULL POINTER ERROR \n");
                        }else {
                            $$ = genTree;
                        }

                     }

    | expr '*' expr {
                        struct tree *genTree;
                        struct tree *lc = $1;
                        struct tree *rc = $3; 
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
                            struct tree *lc = $1;
                            struct tree *rc = $3;
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
                                genTree = newTree( newNode("ASSIG", "ASSIG->EXPR", rc->info.value)->info, lc, rc);
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
                        struct tree *lc = $2;
                        struct node *node = getNodeByName(lc->info.name);
                        struct tree *retTree;
                        if(strcmp(node->info.type, "BOOLEAN")==0){
                           retTree = newTree(newNode("BOOLEAN", "RETURN", lc->info.value)->info, lc, NULL);   
                        }else {
                            retTree = newTree(newNode("INTEGER", "RETURN", $2->info.value)->info, lc, NULL);   
                        }

                        if(retTree != NULL){
                            $$ = retTree;
                        }else {
                            printf("NULL RETURN");
                        }
                    }

    ;

%%