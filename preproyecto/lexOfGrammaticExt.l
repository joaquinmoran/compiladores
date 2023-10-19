%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sintaxOfGrammaticExt.tab.h"
#include "ast.h"
#include "interCodeGen.h"

%}

%option noyywrap
%option yylineno

letter [a-zA-Z]*
digit [0-9]  

%%

{digit}+                  {yylval.i = atoi(yytext);
                            printf("INT : %d\n",atoi(yytext)); 
                            return INT;}
                
int                          {return INTEGER;}

bool                         {printf("%s\n",yytext);
                                return BOOLEAN;}

                                
return                      {printf("%s\n",yytext);
                                return RETURN;} 

True                         {printf("%s\n",yytext);
                                return TBOOL;} 

False                       {printf("%s\n",yytext);
                                return FBOOL;} 

{letter}({letter}|{digit})*        {yylval.s =(char *) malloc(sizeof(yytext)*yyleng);
                                    strcpy(yylval.s,yytext);
                                    printf("ID : %s\n", yytext);
                                    return ID;}
        

"-"                             {printf("%s\n",yytext);
                                  return TMENOS;}

":="                            {printf("%s\n",yytext);
                                    return TEQ;}


[+*;()]                          {printf("%s\n",yytext);
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
        //printNode(ast);
        breadthFirstTraversal(ast);
       
    }else{
        fprintf(stderr, "Error: el árbol está vacío o no se generó correctamente.\n");
        return 1;
    }

    return 0;

}