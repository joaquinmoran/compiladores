flex lexOfGrammaticExt.l
bison -d sintaxOfGrammaticExt.y
gcc -w ast.c symTable.c interCodeGen.c assemblyGen.c lex.yy.c sintaxOfGrammaticExt.tab.c
./a.out example.txt
