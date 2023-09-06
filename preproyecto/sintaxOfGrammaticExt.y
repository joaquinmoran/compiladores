%{

#include <stdlib.h>
#include <stdio.h>

#include "ast.h"

%}

%union { int i; char *s;}

%token<i> INT
%token<s> ID
%token<s> BOOL
%token TMENOS
%token TEQ
%token<s> INTEGER
%token<s> BOOLEAN 
%token<i> RETURN

%type<i> expr
%type<i> IVALOR
%type<i> prog
%type<s> TYPE
%type<s> VAR
%type<i> decl
%type<i> ret
 


    
%left '+' TMENOS
%left '*'

%%




prog: expr ';'   {printf("%s%d\n" , "Result: ", $1);} 

    | decl ';'  {   struct tree *declTree = $1;
                    // printf(declTree->info.type);
                    // si dejo el print ese obtengo violacion de segmento nose porque
                    // si hago printf en la prodccion decl puede ver bien toda la info del arbol
                    // pero aca no 
                    $$ = declTree;
                }

    | expr ';' prog {printf("%s%d\n" , "Result: ", $1);} 

    | decl ';' prog { printf("sda");} 

    | ret ';' {printf("%s%s\n", "Return ", $1);}

    ;


expr: IVALOR         {$$ = $1;
                        printf("%s%d\n","Integer constant:", $1);}

    // | TF            {$$ = $1;
    //                 printf("%s\n", "Boolean constant:",$1);}

    | expr '+' expr  {$$ = $1 + $3;}

    | expr '*' expr {$$ = $1 * $3;}

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
  

TYPE: INTEGER       {$$ = newNode("INTEGER","NULL", -1);}

    | BOOLEAN       {$$ = newNode("BOOLEAN","NULL",-1);}
    ;

VAR: ID    {
                $$ = newNode("ID",$1,-1);}
    ;

IVALOR: INT     {$$ = newNode("INTVAL","NULL",$1);}

// BVALOR: BOOL    {$$ = $1;
//                  printf("%s%d\n", "Boolean constant:",$1);
//                 }

// // TF: BOOL       {$$ = $1;
// //                     printf("%s%d\n", "Boolean constant", $1)}
// //     ;

ret: R expr  {$$ = $2;}
    ;

R: RETURN   
    ; 

%%





