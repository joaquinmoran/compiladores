%{

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "ast.h"

%}

%union { int i; char *s; bool b;}

%token<i> INT
%token<s> ID
%token<b> BOOL
%token TMENOS
%token TEQ
%token<s> INTEGER
%token<b> BOOLEAN 
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

    | decl ';'  {printf("%s%d\n" , "Asignacion := ",$1);}

    | expr ';' prog {printf("%s%d\n" , "Result: ", $1);} 

    | decl ';' prog {printf("%s%d\n" , "Asignacion := ", $1);} 

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

    | VAR  {$$ = var;}

    
    ;


decl: TYPE VAR TEQ IVALOR   {
                             $$ = newTree(info,)}

    | VAR TEQ expr {$$ = $3; var = $3;} 
  

TYPE: INTEGER       {$$ = newNode("INTEGER",NULL, NULL)}

    | BOOLEAN       {$$ = $1;}
    ;

VAR: ID    {$$ = $1;}
    ;

IVALOR: INT     {$$ = $1;}

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





