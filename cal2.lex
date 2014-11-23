%{
#include <stdlib.h>
#include "calc3.h"
#include "cal2.tab.h"
void yyerror(char *);
%}
comments \/{2}(.)*\n
%%
{comments} {}
":=" return ASIGN;
"program example()"   ;
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
.    yyerror("Unknown character");
%%
int yywrap(void){
return 1;
}