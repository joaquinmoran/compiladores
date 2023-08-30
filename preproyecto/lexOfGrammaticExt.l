%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
%}

%option noyywrap
%option yylineno

letter [a-zA-Z]      
digit [0-9]  

%%

{digit}+        { 
                  printf("INT : %d\n",atoi(yytext)); 
                  return INT;
                }
                
int                             {printf("%s\n",yytext);
                                return INTEGER;}     
                                
bool                           {return BOOLEAN;}

return                        {return RETURN;}

{letter}({letter}|{digit})*      { printf("ID : %s\n", atoi(yytext));
                                    return ID;}

"-"                             {printf("%s\n",yytext);
                                  return TMENOS;}

":="                            {printf("%s\n",yytext);
                                    return TEQ;}

[True | False]                   {printf("BOOL : %s\n", atoi(yytext))
                                    return BOOL;}


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

}