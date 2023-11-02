flex analyzers/lexOfGrammaticExt.l
bison -d analyzers/sintaxOfGrammaticExt.y
gcc -w utils/ast.c utils/symTable.c utils/interCodeGen.c utils/assemblyGen.c analyzers/lex.yy.c analyzers/sintaxOfGrammaticExt.tab.c
mv sintaxOfGrammaticExt.tab.c analyzers/
mv sintaxOfGrammaticExt.tab.h analyzers/
mv lex.yy.c analyzers/
./a.out examples/example.txt
gcc assemblyGen.s utils/lib.c
./a.out
