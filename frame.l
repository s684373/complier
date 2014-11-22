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
relation ==|<|<=|>=|!=|and|or|xor|>|<
op \+|\-|\*|\/|\%
boolean yes|no
assign :=
semicolon ;
comma ,
lbrackets \(
rbrackets \)
point \.
array {identifier}(\[{identifier}|{integerdigit}\])+
text \"(.)*\"
%%
{comments} {}
{whitespace} {printf("%s",strdup(yytext));}
{assign} {printf("ASSIGN ");}
{lbrackets} {printf("LBRACKETS ");}
{rbrackets} {printf("RBRACKETS ");}
{semicolon} {printf("SEMICOLON ");}
{point} {printf("POINT ");}
{comma} {printf("COMMA ");}
{relation} {printf("RELATION(%s)",strdup(yytext));}
{op} {printf("OP(%s)",strdup(yytext));}
"boolean" {printf("BOOLEAN");}
"char" {printf("CHAR");}
"class" {printf("CLASS");}
"do" {printf("DO");}
"else" {printf("ELSE");}
"for" {printf("FOR");}
"if" {printf("IF");}
"integer" {printf("INTEGER");}
"return" {printf("RETURN");}
"while" {printf("WHILE");}
"print" {printf("PRINT");}
"program" {printf("PROGRAM");}
"function" {printf("FUNCTION");}
"var" {printf("VAR");}
"is" {printf("IS");}
"begin" {printf("BEGIN");}
"then" {printf("THEN");}
"end" {printf("END");}
"elif" {printf("ELIF");}
"type" {printf("TYPE");}
"repeat" {printf("REPEAT");}
"until" {printf("UNTIL");}
"foreach" {printf("FOREACH");}
"in" {printf("IN");}
{classextent} {printf("CLASSEXTENT");}
{arraytype} {printf("ARRAYTYPE");}
{array} {printf("ARRAY(%s) ",strdup(yytext));}
{boolean} {printf("BOOLEANDIGIT(%s) ",strdup(yytext));}
{integerdigit} {
			printf("INTEGERDIGIT(%s) ",strdup(yytext));}
{positiveinteger} {
			printf("POSITIVEINTEGER(%s) ",strdup(yytext));}
{identifier} {printf("IDENTIFIER(%s) ",strdup(yytext));}
{text} {printf("TEXT(%s) ",strdup(yytext));}
.	{printf("cannot be parsed ");}
%%
void main()
{
yylex(); 
}
int yywrap()
{
    return 1;
}