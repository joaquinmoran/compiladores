%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sintaxOfGrammaticExt.tab.h"
#include "../utils/ast.h"
#include "../utils/interCodeGen.h"
#include "../utils/assemblyGen.h"

%}

%option noyywrap
%option yylineno

letter [a-zA-Z]*
digit [0-9]  

%%

{digit}+                  {yylval.i = atoi(yytext);
                            
                            return INT;}
                
int                          {return INTEGER;}

bool                         {
                                return BOOLEAN;}

                                
return                      {
                                return RETURN;} 

True                         {
                                return TBOOL;} 

False                       {;
                                return FBOOL;} 

{letter}({letter}|{digit})*        {yylval.s =(char *) malloc(sizeof(yytext)*yyleng);
                                    strcpy(yylval.s,yytext);
                                    
                                    return ID;}
        

"-"                             {
                                  return TMENOS;}

":="                            {
                                    return TEQ;}


[+*;()]                          {
                                  return *yytext;}

.|\n                          ; /* ignore all the rest */

%%

void yyerror(){
	printf("%s%d\n","-> ERROR Sintactico en la linea: ",yylineno);
}

int main(int argc,char *argv[]){
	++argv,--argc;
	if (argc > 0)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;

	yyparse();

    if(ast != NULL){
        breadthFirstTraversal(ast);
       
    }else{
        fprintf(stderr, "Error: el árbol está vacío o no se generó correctamente.\n");
        return 1;
    }
    
    listTraverse();

    return 0;

}