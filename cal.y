%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "calc3.h"
nodeType *opr(int oper,int nops,...);
nodeType *id(char *s);
nodeType *con(int value);
unsigned int BKDRHash(char *str);
void freeNode(nodeType *p);
int ex(nodeType *p);
int yylex(void);
void yyerror(char *s);
int symi[1000];
int symb[1000];
%}
%union{
	int iValue;
	char *sIndex;
	struct nodeType *nPtr;
};
%token <iValue>INTEGER
%token <sIndex>VARIABLE
%token VAR IS
%token WHILE IF PRINT
%nonassoc IFX
%nonassoc ELSE
%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%type<nPtr> stmt expr stmt_list
%%
program:
	function   {exit(0);}
	;
function:
	function stmt   {ex($2);freeNode($2);}
	| 
	;
stmt:
	';'     				{$$ = opr(';',2,NULL,NULL);}
	|expr';'				{$$ = $1}
	|PRINT expr';'  		{$$ = opr(PRINT,1,$2);}
	|VAR VARIABLE IS VARIABLE {$$ = opr(IS,2,id($2),id($4));}
	|VARIABLE'='expr';'		{$$ = opr('=',2,id($1),$3);}
	|WHILE'('expr')'stmt	{$$ = opr(WHILE,2,$3,$5);}
	|IF'('expr')'stmt%prec IFX {$$ = opr(IF,2,$3,$5);}
	|IF'('expr')'stmt ELSE stmt{$$ = opr(IF,3,$3,$5,$7);}
	|'{'stmt_list'}'		{$$ = $2;}
	;
stmt_list:
	stmt 			{$$ = $1}
	|stmt_list stmt {$$ = opr(';',2,$1,$2);}
	;
expr:
	INTEGER                	{$$ = con($1);}
	|VARIABLE				{$$ = id($1);}
	|'-'expr %prec UMINUS   {$$ = opr(UMINUS,1,$2);}
	|expr'+'expr            {$$ = opr('+',2,$1,$3);}
	|expr'-'expr            {$$ = opr('-',2,$1,$3);}
	|expr'*'expr            {$$ = opr('*',2,$1,$3);}
	|expr'/'expr            {$$ = opr('/',2,$1,$3);}
	|expr'<'expr            {$$ = opr('<',2,$1,$3);}
	|expr'>'expr            {$$ = opr('>',2,$1,$3);}
	|expr GE expr           {$$ = opr(GE,2,$1,$3);}
	|expr LE expr           {$$ = opr(LE,2,$1,$3);}
	|expr NE expr           {$$ = opr(NE,2,$1,$3);}
	|expr EQ expr           {$$ = opr(EQ,2,$1,$3);}
	|'('expr')'				{$$ = $2;}
	;
%%
nodeType *con(int value){
    nodeType *p;
    size_t nodeSize;
    nodeSize = sizeof(nodeType*) + sizeof(conNodeType);
    if((p = malloc(nodeSize)) == NULL)
   	   yyerror("out of memory");
    p->type = typeCon;
    p->con.value = value;
    return p;
}

nodeType *id(char *s){ 
    nodeType *p;
    size_t nodeSize;
    int i = BKDRHash(s);
    if(strcmp(s,"interger")==0)i = 1;
    if(strcmp(s,"boolean")==0)i = 2;
    nodeSize = sizeof(nodeType*) + sizeof(idNodeType);
    if((p = malloc(nodeSize)) == NULL)
    	yyerror("out of memory");
    p->type = typeId;
    p->id.i = i;
    return p;
}

nodeType *opr(int  oper, int nops, ...) { 
    va_list ap;
    nodeType *p;
    size_t nodeSize;
    int i;
    nodeSize = sizeof(nodeType*) + sizeof(oprNodeType) + 
    (nops - 1)*sizeof(nodeType*);
    if((p = malloc(nodeSize)) == NULL)
   		yyerror("out of memory");
   	p->type = typeOpr;
   	p->opr.oper = oper;
   	p->opr.nops = nops;
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



void yyerror(char *s) { 
    fprintf(stdout,"%s\n",s);
}
int main(void) { 
    yyparse();
    return 0;
}