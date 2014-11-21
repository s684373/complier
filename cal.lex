%{
#include <stdlib.h>
#include "calc3.h"
#include "cal.tab.h"
void yyerror(char *);
%}
%%
"var" return VAR;
"is" return IS;
"while"	return WHILE;
"if" return IF;
"else" return ELSE;
"print" return PRINT;
[a-z]+ {
yylval.sIndex = strdup(yytext);
return VARIABLE;	
}
[0-9]+ {
yylval.iValue = atoi(yytext);
return INTEGER;
}
[-()<>=+*/;{}.] {return *yytext;}
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