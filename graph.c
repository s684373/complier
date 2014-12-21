#include<stdio.h>
#include<string.h>
#include"main.h"
#include"yacc.tab.h"

int del = 1;
int eps = 3;

void graphInit(void);
void graphFinish();
void graphBox(char *s,int *w,int *h);
void graphDrawBox(char *s,int c,int l);
void graphDrawArrow(int c1,int ll,int c2,int l2);

void exNode(nodeType *p,int c,int l,int *ce,int *cm);

void semanalysis(nodeType *p);
void pre_order(nodeType *p);

int ex(nodeType *p){
	int rte,rtm;

	semanalysis(p);
	//graphInit();
	//exNode(p,0,0,&rte,&rtm);
	//graphFinish();
	return 0;
}

void exNode(nodeType *p,int c,int l,int *ce,int *cm){
	int w,h;
	char *s;
	int cbar;
	int k;
	int che,chm;
	int cs;
	char word[20];
	if(!p)return;
	strcpy(word,"???");
	s = word;
	switch(p->type){
		case typeCon:sprintf(word,"c(%d)",p->con.value);break;
		case typeId:sprintf(word,"id(%s)",p->id.s);break;
		case typeOpr:
			switch(p->opr.oper){
				case PROGRAM:s = "program";break;
				case WHILE: s = "while";break;
				case REPEAT:s = "repeat";break;
				case FOREACH:s = "foreach";break;
				case CLASS: s = "class";break;
				case EXTENDS: s = "extends";break;
				case IF: s = "if";break;
				case VAR: s = "var";break;
				case ARRAY: s = "array";break;
				case RETURN: s = "return";break;
				case FUNCTION: s = "function";break;
				case PRINT:s = "print";break;
				case ';':s = "[;]";break;
				case ',':s = "[,]";break;
				case ASIGN:s = "[:=]";break;
				case ARRAYASIGN:s = "[:=]";break;
				case UMINUS:s = "[_]";break;
				case '+':s = "[+]";break;
				case '-':s = "[-]";break;
				case '*':s = "[*]";break;
				case '/':s = "[/]";break;
				case '%':s = "[%]";break;
				case '<':s = "[<]";break;
				case '>':s = "[>]";break;
				case GE:s = "[>=]";break;
				case LE:s = "[<=]";break;
				case NE:s = "[!=]";break;
				case EQ:s = "[==]";break;
				case AND:s = "[AND]";break;
				case OR :s = "[OR]";break;
			}
			break;
	}
	graphBox(s,&w,&h);
	cbar = c;
	*ce = c + w;
	*cm = c + w/2;
	/*node is leaf*/
	if(p->type == typeCon || p->type == typeId ||p->opr.nops == 0){
		graphDrawBox(s,cbar,l);
		return;
	}
	cs = c;
	for(k = 0;k<p->opr.nops;k++){
		exNode(p->opr.op[k],cs,l+h+eps,&che,&chm);
		cs = che;
	}
	if(w < che - c){
		cbar +=(che -c -w)/2;
		*ce = che;
		*cm = (c + che)/2;
	}
	graphDrawBox(s,cbar,l);
	cs = c;
	for(k = 0;k<p->opr.nops;k++){
		exNode(p->opr.op[k],cs,l+h+eps,&che,&chm);
		graphDrawArrow(*cm,l+h,chm,l+h+eps-1);
		cs = che;
	}
}

#define lmax 2000
#define cmax 2000
char graph[lmax][cmax];
int graphNumber = 0;
void graphTest(int l,int c){
	int ok;
	ok = 1;
	if(l < 0)ok = 0;
	if(l>=lmax)ok=0;
	if(c<0)ok=0;
	if(c>=cmax)ok=0;
	if(ok)return;
	printf("error\n");
	return;
}

void graphInit(void){
	int i,j;
	for(i = 0;i < lmax;i++){
		for(j=0;j<cmax;j++){
			graph[i][j]=' ';
		}
	}
}

void graphFinish(){
	int i,j;
	for(i = 0;i<lmax;i++){
		for(j = cmax-1;j>0 &&graph[i][j]==' ';j--);
		graph[i][cmax-1] = 0;
		if(j < cmax -1)graph[i][j+1] = 0;
		if(graph[i][j]==' ')graph[i][j]=0;
	}
	for(i=lmax-1;i>0&&graph[i][0]==0;i--);
	printf("\n\nGraph%d:\n",graphNumber++);
	for(j = 0;j<=i;j++)printf("\n%s",graph[j]);
	printf("\n");
}

void graphBox(char *s,int *w,int *h){
	*w = strlen(s)+del;
	*h = 1;
}

void graphDrawBox(char *s,int c,int l){
	int i;
	graphTest(l,c+strlen(s)-1+del);
	for(i=0;i<strlen(s);i++){
		graph[l][c+i+del] = s[i];
	}
}

void graphDrawArrow(int c1,int l1,int c2,int l2){
	int m;
	graphTest(l1,c1);
	graphTest(l2,c2);
	m=(l1+l2)/2;
	while(l1!=m){
		graph[l1][c1]='|';if(l1<l2)l1++;else l1--;
	}
	while(c1 != c2){
		graph[l1][c1]='-';if(c1<c2)c1++;else c1--;
	}
	while(l1 != l2){
		graph[l1][c1]='|';if(l1<l2)l1++;else l1--;
	}
	graph[l1][c1]='|';
}

void semanalysis(nodeType *p)
{
	pre_order(p);
}

void pre_order(nodeType *p)
{
	if(p!=NULL)
	{
		char* s;
		switch(p->type)
		{
		case typeCon:
			char word[20];
			sprintf(word,"%d",p->con.value);
			s=word;
			printf(s);
			printf("\n");
			break;
		case typeId:
			s=p->id.s;
			printf(s);
			printf("\n");
			break;
		case typeOpr:
			switch(p->opr.oper)
			{
				case PROGRAM:
					s = "program";break;
				case WHILE: s = "while";break;
				case REPEAT:s = "repeat";break;
				case FOREACH:s = "foreach";break;
				case CLASS: s = "class";break;
				case EXTENDS: s = "extends";break;
				case IF: s = "if";break;
				case VAR: s = "var";break;
				case ARRAY: s = "array";break;
				case RETURN: s = "return";break;
				case FUNCTION: s = "function";break;
				case PRINT:s = "print";break;
				case ';':s = "[;]";break;
				case ',':s = "[,]";break;
				case ASIGN:s = "[:=]";break;
				case ARRAYASIGN:s = "[:=]";break;
				case UMINUS:s = "[_]";break;
				case '+':s = "[+]";break;
				case '-':s = "[-]";break;
				case '*':s = "[*]";break;
				case '/':s = "[/]";break;
				case '%':s = "[%]";break;
				case '<':s = "[<]";break;
				case '>':s = "[>]";break;
				case GE:s = "[>=]";break;
				case LE:s = "[<=]";break;
				case NE:s = "[!=]";break;
				case EQ:s = "[==]";break;
				case AND:s = "[AND]";break;
				case OR :s = "[OR]";break;
			}
			printf(s);
			printf("\n");
			for(int i=0;i<p->opr.nops;i++)
			{
				pre_order(p->opr.op[i]);
			}
			break;
		}
	}

}