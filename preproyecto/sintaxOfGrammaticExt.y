%{

#include <stdlib.h>
#include <stdio.h>

%}

%token<i> DIGIT
%token<s> LETTER
%token TMAS
%token TPROD

%type<i> expr
%type<i> VALOR
    
%left '+' TMENOS
%left '*'