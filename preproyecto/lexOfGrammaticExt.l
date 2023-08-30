%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
%}

%option noyywrap
%option yylineno

LETTER [a-zA-Z]      
DIGIT [0-9]  

%%

{DIGIT}+        { 
                  printf("INT : %d\n",atoi(yytext)); 
                  return INT;
                }

{LETTER}({LETTER}|{DIGIT})*     {
                                yylval.s=(char *) malloc(sizeof(yytext)*yyleng);
                                strcpy(yylval.s,yytext);
                                printf("ID :%d\n",atoi(yytext));
                                return ID;}

"-"                             {printf("%s\n",yytext);
                                  return TMENOS;}


[+*;()]                          {  printf("%s\n",yytext);
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

}