flex analyzers/lexOfGrammaticExt.l
bison -d analyzers/sintaxOfGrammaticExt.y
gcc -w utils/ast.c utils/symTable.c utils/interCodeGen.c utils/assemblyGen.c analyzers/lex.yy.c analyzers/sintaxOfGrammaticExt.tab.c
./a.out examples/example.txt
