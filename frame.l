%{
int wordCount = 0;
%}
symbol [+\=\-\*\/\%]
chars [A-za-z\_\']
numbers ([0-9])+
delim [" "\n\t]
whitespace {delim}+
words {chars}+
%%
{words} { wordCount++;}
{whitespace} {mian)}
{numbers} {}
{symbol} {}
%%
void main()
{
yylex(); 
printf(" No of words:%d\n", wordCount);
}
int yywrap()
{
    return 1;
}