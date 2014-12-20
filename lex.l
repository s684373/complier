%{
#include "main.h"		
#include <vector>
#include  "yacc.tab.h"	
extern "C"				
{						
	int yywrap(void);
	int yylex(void);	//这个是lex生成的词法分析函数，yacc的yyparse()里会调用它，如果这里不声明，生成的yacc.tab.c在编译时会找不到该函数
}
%}

comments \/{2}(.)*\n
%option yylineno
%%
{comments} {}
":=" return ASIGN;
"program" return PROGRAM;
"class" return CLASS;
"type" return TYPE;
"extends" return EXTENDS;
"array" return ARRAY;
"of"    return OF;
"var" return VAR;
"is" return IS;
"while"	return WHILE;
"begin" return BEGINNING;
"if" return IF;
"then" return THEN;
"elif" return ELIF;
"else" return ELSE;
"print" return PRINT;
"return" return RETURN;
"function" return FUNCTION;
"repeat" return REPEAT;
"until"  return UNTIL;
"foreach" return FOREACH;
"in"    return IN;
"end"  return END;
"do"   return DO;
"and"   return AND;
"or"    return OR;
[a-z\.]+ {
yylval.sIndex = strdup(yytext);
return VARIABLE;	
}
[0-9]+ {
yylval.iValue = atoi(yytext);
return INTEGER;
}
[-()<>+*/%;{}\[\].,] {return *yytext;}
">=" return GE;
"<=" return LE;
"==" return EQ;
"!=" return NE;

[\t \n]+   ;

%%
//.    yyerror("Unknown character");
//第3段：C函数定义段
int yywrap(void)
{
	vector<int> a;
	a.push_back(2);
	a.push_back(3);
	for(int i = 0 ; i < a.size(); i++)
	cout<< a[i];
	puts("-----the file is end");
	return 1;								//返回1表示读取全部结束。如果要接着读其它文件，可以这里fopen该文件，文件指针赋给yyin，并返回0
}
