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

    | decl ';'  {$$ = $1;}

    | expr ';' prog {printf("%s%d\n" , "Result: ", $1);} 

    | decl ';' prog {printf("hola1");
                    struct tree *node= newNode(NULL, ";", NULL);
                    struct tree *lc = $1; 
                    struct tree *rc = $3;  
                    $$ = newTree(node->info, lc, rc);} 

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
                            {printf("hola");
                                struct tree *i = $1;
                             struct tree *node = newNode(i->info.type, "DECL",NULL);
                             struct tree *lc = $2; 
                             struct tree *rc = $4;
                             $$ = newTree(node->info, lc, rc);}

    ;
  

TYPE: INTEGER       {printf("hola1");$$ = newNode("INTEGER",NULL, NULL);}

    | BOOLEAN       {$$ = newNode("BOOLEAN",NULL,NULL);}
    ;

VAR: ID    { printf("%s\n, hola");
                $$ = newNode("ID",$1,NULL);}
    ;

IVALOR: INT     {$$ = newNode("INTVAL",NULL,$1);}

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





