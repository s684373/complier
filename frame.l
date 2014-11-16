%{
#include <stdio.h>
#include <string.h>
extern char* yylval;
%}
symbol [+\=\-\*\/\%]
char [A-za-z\_]
number [0-9]
numbers ([0-9])+
delim [" "\n\t]
whitespace {delim}+
variable [char]+[number]*[char]*[number]*
type int|double
end ;
%%
{type} {printf("type\n");}
{variable} {printf("variable\n");}
{end} {printf("end\n");}
{whitespace} {}
{numbers} {}
{symbol} {}
%%
void main()
{
yylex(); 
}
int yywrap()
{
    return 1;
}