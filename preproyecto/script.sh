flex lexOfGrammaticExt.l
bison -d sintaxOfGrammaticExt.y
gcc -w ast.c interCodeGen.c lex.yy.c sintaxOfGrammaticExt.tab.c
./a.out example.txt
