%{

#include <stdlib.h>
#include <stdio.h>

#include "ast.h"

%}
%union { int i; char *s; struct tree *t}

%token<i> INT
%token<s> ID
%token<s> BOOL
%token TMENOS
%token TEQ
%token<s> INTEGER
%token<s> BOOLEAN 

%type<i> expr
%type<t> IVALOR
%type<t> prog
%type<t> TYPE
%type<t> VAR
%type<t> decl
%type<t> assig

 


    
%left '+' TMENOS
%left '*'

%%



prog: expr ';'   {printf("%s%d\n" , "Result: ",$1);} 

    | decl ';'  {   struct tree *declTree = $1;
                    $$ = declTree;
                }

    | assig ';' {  struct tree *assigTree = $1;
                    $$ = assigTree;
                    
                }

    | expr ';' prog {$$ = $1;} 

    | decl ';' prog {  struct tree *lc = $1;
                       struct tree *rc = $3;
                       struct tree *declProgTree; 
                       if(lc == NULL && rc == NULL) {
                            printf("NULL POINTER ERROR \n");
                       }else {
                            declProgTree = newTree( newNode("PROG", "DECL->PROG",-1)->info, lc,rc);
                       }
                        $$ = declProgTree;
                        printNode(declProgTree) ;
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
                        printNode(assigProgTree);
                     }


expr: IVALOR        {struct tree *iVal = $1;
                    $$ = iVal->info.value;
                    }

    | expr '+' expr  {$$ = $1 + $3;}

    | expr '*' expr {;
                     struct tree *genTree;
                     struct tree *lc = newNode("LP", "LEFTOPERATOR", $1);
                     struct tree *rc = newNode("RP", "RIGHTOPERATOR", $3);
                     if(lc->info.value == NULL || rc->info.value == NULL) {
                        printf("NULL VALUE ERROR \n"); 
                     }else {
                        genTree = newTree( newNode("EXPR", "PROD", (lc->info.value * rc->info.value))->info, lc, rc);
                     }
                     
                     if(genTree == NULL){
                        printf("NULL POINTER ERROR \n");
                     }else {
                        $$ = genTree->info.value;
                     }

                    }

    | '(' expr ')'  {$$ = $2;}

    | expr TMENOS expr {$$ = $1 - $3;}

    ;


decl: TYPE VAR TEQ IVALOR   
                            {
                             struct tree *i = $1;
                             struct tree *lc = $2; 
                             struct tree *rc = $4;
                             struct tree *genTree = newTree( newNode(i->info.type, "DECL",-1)->info, lc, rc);
                             $$ = genTree;
                             }

    ;

assig: VAR TEQ expr { 
                    struct tree *lc = $1;
                    struct tree *rc = $3;
                    struct tree *genTree;
                    if(lc == NULL && rc == NULL){
                        printf("NULL POINTER ERROR \n");
                    }else {
                        genTree = newTree( newNode("ASSIG", "ExprASSIG", rc)->info, lc, rc);
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

VAR: ID    {  $$ = newNode("ID",$1,-1);}
    ;

IVALOR: INT     {
                struct tree *intValueTree = newNode("IVALOR", "IVALUE", $1);
                $$  = intValueTree;
                }
     ;

%%





