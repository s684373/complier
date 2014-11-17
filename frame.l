%{
#include <stdio.h>
#include <string.h>
extern char* yylval;
%}
char [A-za-z\_]
symbol [,\@]
digit [0-9]
nonzerodigit [1-9]
digits ([0-9])+
delim [" "\n\t]
whitespace {delim}+
identifier ({char})+({digit})*({char})*({digit})*
keywords boolean|char|class|do|else|class" "extends|for|if|integer|return|while|print|program|function|var|is|begin|then|end|elif|type|array" "of|repeat|until|foreach|in
sign +|-
signinteger {sign}digits
number signinteger
comments \/{2}(.)*\n
relation ==|<|<=|>=|!=|and|or|xor
op +|-|*|/|%
boolean yes|no
assign =
semicolon ;
lbrackets \(
rbrackets \)
array {identifier}(\[{identifier}|{digits}\])+
%%
{comments} {}
{assign} {printf("=");}
{lbrackets} {printf("(");}
{rbrackets} {printf(")");}
{array} {printf("identifier(a)");}
{relation} {printf("%s",strdup(yytext));}
{boolean} {printf("%s",strdup(yytext));}
{keywords} {printf("%s",strdup(yytext));}
{identifier} {printf("identifier");}
{digits} {printf("digits");}
{whitespace} {printf("%s",strdup(yytext));}
%%
void main()
{
yylex(); 
}
int yywrap()
{
    return 1;
}