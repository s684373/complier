%{
/*本lex的生成文件是lex.yy.c
lex文件由3段组成，用2个%%行把这3段隔开。
第1段是声明段，包括：
1-C代码部分：include头文件、函数、类型等声明，这些声明会原样拷到生成的.c文件中。
2-状态声明，如%x COMMENT。
3-正则式定义，如digit ([0-9])。
第2段是规则段，是lex文件的主体，包括每个规则(如identifier)是如何匹配的，以及匹配后要执行的C代码动作。
第3段是C函数定义段，如yywrap()的定义，这些C代码会原样拷到生成的.c文件中。该段内容可以为空*/

//第1段：声明段
#include "main.h"		//lex和yacc要共用的头文件，里面包含了一些头文件，重定义了YYSTYPE
#include <vector>
#include  "yacc.tab.h"	//用yacc编译yacc.y后生成的C头文件，内含%token、YYSTYPE、yylval等定义(都是C宏)，供lex.yy.c和yacc.tab.c使用
extern "C"				//为了能够在C++程序里面调用C函数，必须把每一个需要使用的C函数，其声明都包括在extern "C"{}块里面，这样C++链接时才能成功链接它们。extern "C"用来在C++环境下设置C链接类型。
{						//yacc.y中也有类似的这段extern "C"，可以把它们合并成一段，放到共同的头文件main.h中
	int yywrap(void);
	int yylex(void);	//这个是lex生成的词法分析函数，yacc的yyparse()里会调用它，如果这里不声明，生成的yacc.tab.c在编译时会找不到该函数
}
%}

%option yylineno

comments \/{2}(.)*\n
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
	return 1;								//返回1表示读取全部结束。如果要接着读其它文件，可以这里fopen该文件，文件指针赋给yyin，并返回0
}
