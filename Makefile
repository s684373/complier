flex lex.l
bison -d yacc.y
g++ lex.yy.c yacc.tab.h yacc.tab.c main.h