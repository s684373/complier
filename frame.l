%{
#define YYSTYPE char*
#include <stdio.h>
#include <string.h>
extern char* yylval;
%}
char [A-za-z\_]
symbol [\@]
digit [0-9]
nonzerodigit [1-9]
integerdigit ([0-9])+
delim [" "\n\t]
whitespace {delim}+
identifier ({char})+({digit})*({char})*({digit})*
classextent class" "extends
arraytype array" "of
positiveinteger \(-{integerdigit}\)
comments \/{2}(.)*\n
relation ==|<|<=|>=|!=|and|or|xor
op +|-|*|/|%
boolean yes|no
assign =
semicolon ;
comma ,
lbrackets \(
rbrackets \)
array {identifier}(\[{identifier}|{digits}\])+
text \"(.)*\"
%%
{comments} {}
{assign} {return ASSIGN};
{lbrackets} {return LBRACKETS;}
{rbrackets} {return RBRACKETS;}
{semicolon} {return SEMICOLON;}
{comma} {return COMMA;}
{relation} {yylval = strdup(yytext);
				return RELATION;}
{op} {yylval = strdup(yytext);
				return OP;}
"boolean" {return BOOLEAN;}
"char" {return CHAR;}
"class" {return CLASS;}
"do" {return DO;}
"else" {return ELSE;}
"for" {return FOR;}
"if" {return IF;}
"integer" {return INTEGER;}
"return" {return RETURN;}
"while" {return WHILE;}
"print" {return PRINT;}
"program" {return PROGRAM;}
"function" {return FUNCTION;}
"var" {return VAR;}
"is" {return IS;}
"begin" {return BEGIN;}
"then" {return THEN;}
"end" {return END;}
"elif" {return ELIF;}
"type" {return TYPE;}
"repeat" {return REPEAT;}
"until" {return UNTIL;}
"foreach" {return FOREACH;}
"in" {return IN;}
{classextent} {return CLASSEXTENT;}
{arraytype} {return ARRAYTYPE;}
{array} {yylval = strdup(yytext);
				return ARRAY;}
{boolean} {yylval = strdup(yytext);
				return BOOLEANDIGIT;}
{digits} {yylval = strdup(yytext)
			return INTEGERDIGIT;}
{positiveinteger} {yylval = strdup(yytext)
			return POSITIVEINTEGER;}
{identifier} {yylval = strdup(yytext);
				return IDENTIFIER;}
{text} {yylval = strdup(yytext);
				return TEXT;}
{whitespace} {}
%%
void main()
{
yylex(); 
}
int yywrap()
{
    return 1;
}