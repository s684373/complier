%{
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <map>
#include <stack>
#include <string>
int ex(nodeType *p);
nodeType *opr(int oper,int nops,...);
nodeType *id(char *s);
nodeType *con(int value);
unsigned int BKDRHash(char *str);
void freeNode(nodeType *p);
extern int yylineno;
int symi[1000];
int symb[1000];
extern "C"      
{         
  void yyerror(const char *s);
  extern int yylex(void);
  char *strdup(char *str);
}
%}
%token <iValue>INTEGER
%token <sIndex>VARIABLE
%token ASIGN ARRAYASIGN
%token FUNCTION END ARRAY CALLARRAY TYPE OF RETURN  CLASS EXTENDS CLASSFUN PROGRAM CALLFUNCTION
%token VAR IS BEGINNING
%token WHILE IF PRINT DO ELIF THEN REPEAT UNTIL FOREACH IN ENDIF ENDWHILE ENDFOR XIABIAO
%nonassoc IFX
%nonassoc ELSE
%left OR
%left AND
%left GE LE EQ NE '>' '<'
%left '+' '-' 
%left '*' '/' '%'
%nonassoc UMINUS
%type<nPtr> stmt optparams params expr stmt_list 
%%
program:
  function   {exit(0);}
  ;
function:
  function stmt   {ex($2);freeNode($2);}
  | 
  ;
stmt:
  ';'             {$$ = opr(';',2,NULL,NULL);}
  |expr';'        {$$ = $1}
  |PRINT expr';'      {$$ = opr(PRINT,1,$2);}
  |PROGRAM VARIABLE'('')'stmt_list IS stmt_list BEGINNING stmt_list END {$$ = opr(PROGRAM,4,id($2),$5,$7,$9);}
  |PROGRAM VARIABLE'('')'IS stmt_list BEGINNING stmt_list END {$$ = opr(PROGRAM,3,id($2),$6,$8);}
  |TYPE VARIABLE IS CLASS stmt_list END CLASS';'    {$$ = opr(CLASS,2,id($2),$5);}
  |TYPE VARIABLE IS CLASS EXTENDS VARIABLE stmt_list END CLASS';'    {$$ = opr(EXTENDS,3,id($2),id($6),$7);}
  |FUNCTION VARIABLE'('')'stmt_list IS stmt_list BEGINNING stmt_list END FUNCTION VARIABLE';' {$$ = opr(FUNCTION,6,$2,$5,opr(IS,0),$7,opr(BEGINNING,0),$9);}
  |FUNCTION VARIABLE'('')'IS BEGINNING stmt_list END FUNCTION VARIABLE';' {$$ = opr(FUNCTION,4,$2,opr(IS,0),opr(BEGINNING,0),$7);}
  |FUNCTION VARIABLE'('')'stmt_list IS BEGINNING stmt_list END FUNCTION VARIABLE';' {$$ = opr(FUNCTION,5,$2,$5,opr(IS,0),opr(BEGINNING,0),$8);}
  |FUNCTION VARIABLE'('optparams')'stmt_list IS stmt_list BEGINNING stmt_list END FUNCTION VARIABLE';' {$$ = opr(FUNCTION,7,id($2),$4,$6,opr(IS,0),$8,opr(BEGINNING,0),$10);}
  |FUNCTION VARIABLE'('optparams')'stmt_list IS BEGINNING stmt_list END FUNCTION VARIABLE';' {$$ = opr(FUNCTION,6,id($2),$4,$6,opr(IS,0),opr(BEGINNING,0),$9);}
  |RETURN expr';'   {$$ = opr(RETURN,1,$2);}
  |RETURN ';'   {$$ = opr(RETURN,0);}
  |VAR VARIABLE IS VARIABLE';' {$$ = opr(VAR,2,id($2),id($4));}
  |TYPE VARIABLE IS ARRAY OF expr VARIABLE ';' {$$ = opr(ARRAY,3,id($2),$6,id($7));}
  |VARIABLE ASIGN expr';'   {$$ = opr(ASIGN,2,id($1),$3);}
  |VARIABLE '['expr']' ASIGN expr';'{$$ = opr(ARRAYASIGN,3,id($1),opr(XIABIAO,1,$3),$6);}
  |VARIABLE '['expr']''['expr']' ASIGN expr';'{$$ = opr(ARRAYASIGN,3,id($1),opr(XIABIAO,2,$3,$6),$9);}
  |WHILE expr DO stmt_list  END WHILE {$$ = opr(WHILE,3,$2,$4,opr(ENDWHILE,0));}
  |REPEAT stmt_list UNTIL expr';' {$$ = opr(REPEAT,2,$2,$4)}
  |FOREACH VARIABLE IN VARIABLE DO stmt_list END FOREACH {$$ = opr(FOREACH,4,id($2),id($4),$6,opr(ENDFOR,0));}
  |IF expr THEN stmt_list END IF %prec IFX{$$ = opr(IF,3,$2,$4,opr(ENDIF,0));}
  |IF expr THEN stmt_list ELIF expr THEN stmt_list ELSE stmt_list END IF{$$ = opr(IF,5,$2,$4,opr(ELIF,2,$6,$8),opr(ELSE,1,$10),opr(ENDIF,0));}
  |IF expr THEN stmt_list ELSE stmt_list END IF{$$ = opr(IF,4,$2,$4,opr(ELSE,1,$6),opr(ENDIF,0));}
stmt_list:
  stmt      {$$ = $1}
  |stmt_list stmt {$$ = opr(';',2,$1,$2);}
  ;
expr:
  INTEGER                 {$$ = con($1);}
  |VARIABLE               {$$ = id($1);}
  |VARIABLE'['expr']'     {$$ = opr(CALLARRAY,2,id($1),opr(XIABIAO,1,$3));}
  |VARIABLE'['expr']''['expr']'     {$$ = opr(CALLARRAY,2,id($1),opr(XIABIAO,2,$3,$6));}
  |VARIABLE'('')'         {$$ = opr(CALLFUNCTION,1,id($1));}
  |VARIABLE'('optparams')' {$$ = opr(CALLFUNCTION,2,id($1),$3);}
  |'-'expr %prec UMINUS   {$$ = opr(UMINUS,1,$2);}
  |expr'+'expr            {$$ = opr('+',2,$1,$3);}
  |expr'-'expr            {$$ = opr('-',2,$1,$3);}
  |expr'*'expr            {$$ = opr('*',2,$1,$3);}
  |expr'/'expr            {$$ = opr('/',2,$1,$3);}
  |expr'%'expr            {$$ = opr('%',2,$1,$3);}
  |expr'<'expr            {$$ = opr('<',2,$1,$3);}
  |expr'>'expr            {$$ = opr('>',2,$1,$3);}
  |expr GE expr           {$$ = opr(GE,2,$1,$3);}
  |expr LE expr           {$$ = opr(LE,2,$1,$3);}
  |expr NE expr           {$$ = opr(NE,2,$1,$3);}
  |expr EQ expr           {$$ = opr(EQ,2,$1,$3);}
  |expr AND expr          {$$ = opr(AND,2,$1,$3);}
  |expr OR expr          {$$ = opr(OR,2,$1,$3);}
  |'('expr')'       {$$ = $2;}
  ;

optparams:
  params    {$$ = $1;}
  ;
params:
  expr   {$$ = $1;}
  |params','expr  {$$ = opr(',',2,$1,$3);}
  ;
%%
nodeType *con(int value){
    nodeType *p;
    size_t nodeSize;
    nodeSize = sizeof(nodeType*) + sizeof(conNodeType);
    if((p = (nodeType*)malloc(nodeSize)) == NULL)
       yyerror("out of memory");
    p->type = typeCon;
    p->con.value = value;
    p->linenum=yylineno;
    return p;
}

nodeType *id(char *s){ 
    nodeType *p;
    size_t nodeSize;
    int i = BKDRHash(s);
    //if(strcmp(s,"interger")==0)i = 1;
   // if(strcmp(s,"boolean")==0)i = 2;
    nodeSize = sizeof(nodeType*) + sizeof(idNodeType);
    if((p = (nodeType*)malloc(nodeSize)) == NULL)
      yyerror("out of memory");
    p->type = typeId;
    p->id.i = i;
    p->id.s = strdup(s);
    p->linenum=yylineno;
    return p;
}

nodeType *opr(int  oper, int nops, ...) { 
    va_list ap;
    nodeType *p;
    size_t nodeSize;
    int i;
    nodeSize = sizeof(nodeType*) + sizeof(oprNodeType) + 
    (nops - 1)*sizeof(nodeType*);
    if((p = (nodeType*)malloc(nodeSize)) == NULL)
      yyerror("out of memory");
    p->type = typeOpr;

    p->opr.oper = oper;
    p->opr.nops = nops;
    p->linenum=yylineno;
    va_start(ap,nops);
    for(i = 0;i<nops;i++)
      p->opr.op[i] = va_arg(ap,nodeType*);
    va_end(ap);
   
    return p;

} 

void freeNode(nodeType *p) { 
  int i;
  if(!p)return;
  if(p->type == typeOpr){
    for(i = 0;i < p->opr.nops;i++)
      freeNode(p->opr.op[i]);
  }
  free(p);
} 

unsigned int BKDRHash(char *str)
{
    unsigned int seed = 1; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
  
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
 
    return (hash & 0x7FFFFFFF);
}


  
void yyerror(const char *s)     //µ±yaccÓöµ½Óï·¨´íÎóÊ±£¬»á»Øµ÷yyerrorº¯Êý£¬²¢ÇÒ°Ñ´íÎóÐÅÏ¢·ÅÔÚ²ÎÊýsÖÐ
{
  cerr<<yylineno<<":"<<s<<endl;         //Ö±½ÓÊä³ö´íÎóÐÅÏ¢
}

int main()              //³ÌÐòÖ÷º¯Êý£¬Õâ¸öº¯ÊýÒ²¿ÉÒÔ·Åµ½ÆäËü.c, .cppÎÄ¼þÀï
{
  yyparse();            //Ê¹yacc¿ªÊ¼¶ÁÈ¡ÊäÈëºÍ½âÎö£¬Ëü»áµ÷ÓÃlexµÄyylex()¶ÁÈ¡¼ÇºÅ

  return 0;
}
