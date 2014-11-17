%{
#include <stdlib.h>
#include "calc3.h"
#include "cal.tab.h"
void yyerror(char *);
%}
%%
[a-z] {
yylval.sIndex = *yytext - 'a';
return VARIABLE;	
}
[0-9]+ {
yylval.iValue = atoi(yytext);
return INTEGER;
}
[-()<>==+*/;{}.] {
return *yytext;	
}
">=" return GE;
"<=" return LE;
"==" return EQ;
"!=" return NE;
"while"	return WHILE;
"if" return IF;
"else" return ELSE;
"print" return PRINT;
[\t\n]+ ;
.    yyerror("Unknown character");
%%
int yywrap(void){
return 1;
}