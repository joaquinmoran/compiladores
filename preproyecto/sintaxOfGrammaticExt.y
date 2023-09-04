%{

#include <stdlib.h>
#include <stdio.h>

%}

%union { int i; char *s; }

%token<i> INT
%token<s> ID
%token<i> BOOL
%token TMENOS
%token TEQ
%token<i> INTEGER
%token<i> BOOLEAN 
%token<s> RETURN

%type<i> expr
%type<i> VALOR
%type<i> prog
%type<i> decl
%type<s> VAR
%type<i> TYPE
%type<i> ret
%type<s> R

    
%left '+' TMENOS
%left '*'

%%

source: prog     {printf("%s%d\n" , "Result: ", $1);}
      ;


prog: decl ';' 
    | ret ';' 
    | expr ';' prog
    | decl ';' prog
    | ret expr ';' prog
    ;


expr: VALOR         {$$= $1;
                        printf("%s%d\n","Integer constant:", $1);}

    // | TF            {$$ = $1;
    //                 printf("%s\n", "Boolean constant:",$1);}

    | expr '+' expr  {$$ = $1 + $3;}

    | expr '*' expr {$$ = $1 * $3;}

    | '(' expr ')'  {$$ = $2;}
    
    | VAR TEQ expr {$$ = $1 == $3;} 

    // | TF          {$$ = $1;
    //                 printf("%s%d\n", "Boolean constant:",$1);}
    ;


decl: TYPE VAR TEQ VALOR   {$$ = $4;}
  

TYPE: INTEGER       {$$ = $1;}

    | BOOLEAN       {$$ = $1;}
    ;

VAR: ID    {$$ = $1;}
    ;

VALOR: INT     {$$ = $1;
                printf("%s%d\n", "Integer constant:",$1);
                }

    | BOOL      {$$ = $1;
                printf("%s%d\n", "Boolean constant", $1);}
    ;

// TF: BOOL       {$$ = $1;
//                     printf("%s%d\n", "Boolean constant", $1)}
//     ;

ret: R expr  {$$ = $2;}
    ;

R: RETURN   
    ; 

%%

int main() {
    yyparse(); // Invocar al analizador sintáctico generado por Bison
    return 0;
}





