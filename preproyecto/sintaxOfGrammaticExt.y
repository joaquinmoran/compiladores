%{

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


struct nodes {
    Tag = {"Var" , "Val", "Decl" , "Const"};
    char *name;
    bool type;
    int val;
}

struct treeNode {
    treeNode *left;
    treeNode *right;
    info nodes;
}


%}

%union { int i; char *s; bool b;}

%token<i> INT
%token<s> ID
%token<b> BOOL
%token TMENOS
%token TEQ
%token<s> INTEGER
%token<b> BOOLEAN 
%token<s> RETURN

%type<i> expr
%type<i> IVALOR
%type<i> prog
%type<s> TYPE
%type<s> VAR
%type<i> decl
 


    
%left '+' TMENOS
%left '*'

%%




prog: expr ';'  {printf("%s%d\n" , "Result: ", $1);} 

    | decl ';'  {printf("%s%d\n" , "Asignacion := ",$1);}

    | expr ';' prog {printf("%s%d\n" , "Result: ", $1);} 

    | decl ';' prog {printf("%s%d\n" , "Asignacion := ", $1);} 


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


decl: TYPE VAR TEQ IVALOR   {$$ = $4; var = $4;}

    | VAR TEQ expr {$$ = $3; var = $3;} 
  

TYPE: INTEGER       {$$ = $1;}

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

// ret: R expr  {$$ = $2;}
//     ;

// R: RETURN   
//     ; 

%%





