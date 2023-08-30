%{

#include <stdlib.h>
#include <stdio.h>

%}

%union { int i; char *s; }

%token<i> INT
%token<s> ID
%token<s> BOOL
%token TMENOS
%token TEQ
%token<s> INTEGER
%token<s> BOOLEAN 
%token<s> RETURN

%type<i> expr
%type<i> VALOR
%type<s> TF
%type<i> prog
%type<s> decl
%type<i> var
%type<s> TYPE
%type<s> ret

    
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
                        printf("%s%d\n","Integer constant:", $1);
                    }

    | expr '+' expr  {$$ = $1 + $3;}

    | expr '*' expr {$$ = $1 * $3;}

    | '(' expr ')'  {$$ = $2;}
    
    | var TEQ expr {$$ = $1 == $3;} 

    | TF          {$$ = $1;
                        printf("%s%d\n", "Boolean constant:",$1);}
    ;


decl: TYPE var TEQ expr   {$$ = $4;}
  

TYPE: INTEGER       {$$ = $1;}
    | BOOLEAN       {$$ = $1;}
    ;

var: ID          {$$ = $1;}
    ;

VALOR: INT     {$$ = $1;
                printf("%s%d\n", "Integer constant:",$1);
                }
    ;

TF: BOOL       {$$ = $1;
                    printf("%s%d\n", "Boolean constant", $1)}
    ;

ret: RETURN expr  {$$ = $2;}
    ;

%%

int main() {
    yyparse(); // Invocar al analizador sintáctico generado por Bison
    return 0;
}





