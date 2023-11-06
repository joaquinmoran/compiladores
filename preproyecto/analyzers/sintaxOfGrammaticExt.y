%{

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../utils/ast.h"
#include "../utils/symTable.h"
#include "../utils/interCodeGen.h"

extern int yylineno;

extern int error_flag;

extern struct tree *ast = NULL;

extern bool isBoolExpr = false;

struct tree *checkTypeForSum(struct tree*lc, struct tree *rc){
    if(strcmp(lc->info.type,"ID") == 0){
        struct node *leftOp = getNodeByName(lc->info.name);
        if(strcmp(rc->info.type,"ID") == 0){
            struct node *rightOp = getNodeByName(rc->info.name);
            if(strcmp(leftOp->info.type, rightOp->info.type) == 0){
                if(strcmp(leftOp->info.type,"BOOLEAN") == 0){
                    isBoolExpr = true;
                }
                return newTree( newNode("EXPR", "SUM", (lc->info.value + rc->info.value))->info, lc, rc);
            }
        }else{
            if(strcmp(leftOp->info.type, rc->info.type) == 0){
                if(strcmp(leftOp->info.type,"BOOLEAN") == 0){
                    isBoolExpr = true;
                }
                return newTree( newNode("EXPR", "SUM", (lc->info.value + rc->info.value))->info, lc, rc);
            }
        }
    }else{
        if(strcmp(rc->info.type,"ID") == 0){
            struct node *rightOp = getNodeByName(rc->info.name);
            if(strcmp(lc->info.type, rightOp->info.type) == 0){
                if(strcmp(lc->info.type,"BOOLEAN") == 0){
                    isBoolExpr = true;
                }
                return newTree( newNode("EXPR", "SUM", (lc->info.value + rc->info.value))->info, lc, rc);
            }
        }else{
            if(strcmp(lc->info.type,rc->info.type) == 0){
                if(strcmp(lc->info.type,"BOOLEAN") == 0){
                    isBoolExpr = true;
                }
                return newTree( newNode("EXPR", "SUM", (lc->info.value + rc->info.value))->info, lc, rc);
            }
        }
    }
    return NULL;
}

struct tree *checkTypeForProd(struct tree*lc, struct tree *rc){
    if(strcmp(lc->info.type,"ID") == 0){
        struct node *leftOp = getNodeByName(lc->info.name);
        if(strcmp(rc->info.type,"ID") == 0){
            struct node *rightOp = getNodeByName(rc->info.name);
            if(strcmp(leftOp->info.type, rightOp->info.type) == 0){
                if(strcmp(leftOp->info.type,"BOOLEAN") == 0){
                    isBoolExpr = true;
                }
                return newTree( newNode("EXPR", "PROD", (lc->info.value * rc->info.value))->info, lc, rc);
            }
        }else{
            if(strcmp(leftOp->info.type, rc->info.type) == 0){
                if(strcmp(leftOp->info.type,"BOOLEAN") == 0){
                    isBoolExpr = true;
                }
                return newTree( newNode("EXPR", "PROD", (lc->info.value * rc->info.value))->info, lc, rc);
            }
        }
    }else{
        if(strcmp(rc->info.type,"ID") == 0){
            struct node *rightOp = getNodeByName(rc->info.name);
            if(strcmp(lc->info.type, rightOp->info.type) == 0){
                if(strcmp(lc->info.type,"BOOLEAN") == 0){
                    isBoolExpr = true;
                }
                return newTree( newNode("EXPR", "PROD", (lc->info.value * rc->info.value))->info, lc, rc);
            }
        }else{
            if(strcmp(lc->info.type,rc->info.type) == 0){
                if(strcmp(lc->info.type,"BOOLEAN") == 0){
                    isBoolExpr = true;
                }
                return newTree( newNode("EXPR", "PROD", (lc->info.value * rc->info.value))->info, lc, rc);
            }
        }
    }
    return NULL;
}

struct tree *checkTypeForSubt(struct tree*lc, struct tree *rc){
    if(strcmp(lc->info.type,"ID") == 0){
        struct node *leftOp = getNodeByName(lc->info.name);
        if(strcmp(rc->info.type,"ID") == 0){
            struct node *rightOp = getNodeByName(rc->info.name);
            if(strcmp(leftOp->info.type, rightOp->info.type) == 0){
                if(strcmp(leftOp->info.type,"BOOLEAN") == 0){
                    isBoolExpr = true;
                }
                return newTree( newNode("EXPR", "SUBT", (lc->info.value - rc->info.value))->info, lc, rc);
            }
        }else{
            if(strcmp(leftOp->info.type, rc->info.type) == 0){
                if(strcmp(leftOp->info.type,"BOOLEAN") == 0){
                    isBoolExpr = true;
                }
                return newTree( newNode("EXPR", "SUBT", (lc->info.value - rc->info.value))->info, lc, rc);
            }
        }
    }else{
        if(strcmp(rc->info.type,"ID") == 0){
            struct node *rightOp = getNodeByName(rc->info.name);
            if(strcmp(lc->info.type, rightOp->info.type) == 0){
                if(strcmp(lc->info.type,"BOOLEAN") == 0){
                    isBoolExpr = true;
                }
                return newTree( newNode("EXPR", "SUBT", (lc->info.value - rc->info.value))->info, lc, rc);
            }
        }else{
            if(strcmp(lc->info.type,rc->info.type) == 0){
                if(strcmp(lc->info.type,"BOOLEAN") == 0){
                    isBoolExpr = true;
                }
                return newTree( newNode("EXPR", "SUBT", (lc->info.value - rc->info.value))->info, lc, rc);
            }
        }
    }
    return NULL;
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
                        // if(strcmp(retTree->info.type, "BOOLEAN") == 0){
                        //     if(retTree->info.value != 0){
                        //         printf("True\n");
                        //     }else{
                        //         printf("False\n");
                        //     }
                        // }else {
                        //     printf("Result: %d\n", retTree->info.value);
                        // }
                        ast = retTree;
                        $$ = retTree;
                    }

    | ret ';' prog   { 
                        struct tree *lc = $1;
                        struct tree *rc = $3;
                        struct tree *retAssigTree;
                        // if(strcmp(lc->info.type, "BOOLEAN") == 0){
                        //         if(lc->info.value != 0){

                        //         }
                        //         //     printf("True\n");
                        //         // }else{
                        //         //     printf("False\n");
                        //         // }
                        //     }else {
                        //             printf("Result: %d\n", lc->info.value);
                        //     }
                                
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
                        
                        struct tree *lc = $1;
                        struct tree *rc = $3;
                        struct tree *genTree = checkTypeForSum(lc, rc);
                        if(genTree == NULL){
                            printf("ERROR(incompatible types in line %d).\n", yylineno);
                            printf("Aborting compilation...\n");
                            exit(EXIT_FAILURE);                        
                        }else {
                            $$ = genTree;
                        }

                     }

    | expr '*' expr {
                        
                        struct tree *lc = $1;
                        struct tree *rc = $3; 
                        struct tree *genTree = checkTypeForProd(lc, rc);
                        if(genTree == NULL){
                            printf("ERROR(incompatible types in line %d).\n", yylineno);
                            printf("Aborting compilation...\n");
                            exit(EXIT_FAILURE);
                        }else {
                            $$ = genTree;
                        }
                    }

    | '(' expr ')'  {$$ = $2;}


    | expr TMENOS expr {
                            
                            struct tree *lc = $1;
                            struct tree *rc = $3;
                            struct tree *genTree = checkTypeForSubt(lc, rc);
                            if(genTree == NULL){
                                printf("ERROR(incompatible types in line %d).\n", yylineno);
                                printf("Aborting compilation...\n");
                                exit(EXIT_FAILURE);
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
                        struct tree *intValueTree = newNode("INTEGER", "IVALUE", $1);
                        $$  = intValueTree;
                    }

        | TBOOL     {   
                        struct tree *tBoolValueTree = newNode("BOOLEAN", "TVALUE", 1);
                        $$  = tBoolValueTree;
                    }

        | FBOOL     {   
                        struct tree *fBoolValueTree = newNode("BOOLEAN", "FVALUE", 0);
                        $$  = fBoolValueTree;
                    }
     ;


ret: RETURN expr   {    
                        struct tree *lc = $2;
                        struct tree *retTree;
                        if(strcmp(lc->info.type,"EXPR") == 0){
                            if(isBoolExpr){
                                retTree = newTree(newNode("BOOLEXPR", "RETURNBOOL", lc->info.value)->info, lc, NULL);
                                isBoolExpr = false;
                            }else{
                                retTree = newTree(newNode("INTEXPR", "RETURNINT", lc->info.value)->info, lc, NULL);
                            }
                        }else{
                            if(strcmp(lc->info.type, "ID") == 0){
                                struct node *node = getNodeByName(lc->info.name);
                                if(strcmp(node->info.type, "BOOLEAN") == 0){
                                    retTree = newTree(newNode("BOOLEAN", "RETURN", lc->info.value)->info, lc, NULL);   
                                }else {
                                    retTree = newTree(newNode("INTEGER", "RETURN", lc->info.value)->info, lc, NULL);   
                                }
                            }else{
                                if(strcmp(lc->info.type, "BOOLEAN") == 0){
                                    retTree = newTree(newNode("BOOLEAN", "RETURN", lc->info.value)->info, lc, NULL);   
                                }else{
                                    retTree = newTree(newNode("INTEGER", "RETURN", lc->info.value)->info, lc, NULL);   
                                }
                            }
                        }
                        $$ = retTree;
                    
                        
                    }

    ;

%%