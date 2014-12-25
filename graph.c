#include<stdio.h>
#include<string.h>
#include<map>
#include<stack>
#include<sstream>
#include"main.h"
#include"yacc.tab.h"

int del = 1;
int eps = 3;

map<string,map<string,string> >symtable;
stack<string> curscope;

void graphInit(void);
void graphFinish();
void graphBox(char *s,int *w,int *h);
void graphDrawBox(char *s,int c,int l);
void graphDrawArrow(int c1,int ll,int c2,int l2);

void exNode(nodeType *p,int c,int l,int *ce,int *cm);

void semanalysis(nodeType *p);
void pre_order(nodeType *p);
void getarrayinfo(string s,int& size,string& type);
bool varintable(string varname,map<string,map<string,string> >symtable,stack<string> temstack,string& scope);
bool isbool(char* varname);
bool typeequal(string type1,string type2,int linenum);

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
			p->con.value;
			break;
		case typeId:
			p->id.s;
			break;
		case typeOpr:
			switch(p->opr.oper)
			{
				case PROGRAM:
					if(symtable.find(p->opr.op[0]->id.s)==symtable.end()&&!isbool(p->opr.op[0]->id.s))
          			{
            			curscope.push(p->opr.op[0]->id.s);
            			map<string,string>varmap;
            			symtable[p->opr.op[0]->id.s]=varmap;
          			}
          			else
          			{
            			cout<<"line: "<<p->opr.op[0]->linenum<<" this program can not be named this"<<endl;
            			return;
          			}	    
					break;
				case WHILE: s = "while";break;
				case REPEAT:s = "repeat";break;
				case FOREACH:s = "foreach";break;
				case CLASS:
					if(symtable[curscope.top()].find(p->opr.op[0]->id.s)==symtable[curscope.top()].end()&&!isbool(p->opr.op[0]->id.s))
          			{
           				 symtable[curscope.top()][p->opr.op[0]->id.s]="class";
          			  	 curscope.push(p->opr.op[0]->id.s);
          			  	 map<string,string>varmap;
          			  	 symtable[p->opr.op[0]->id.s]=varmap;
        			}
        			else
         			{
           			 	cout<<"line: "<<p->opr.op[0]->linenum<<" this class's name has been used: "<<p->opr.op[0]->id.s<<endl;
						return;
          			} 
          			break;  
				case EXTENDS:
					 if(symtable[curscope.top()].find(p->opr.op[0]->id.s)==symtable[curscope.top()].end()&&!isbool(p->opr.op[0]->id.s))
          			{
          				if(symtable[curscope.top()].find(p->opr.op[1]->id.s)==symtable[curscope.top()].end())
          				{
          					cout<<"line: "<<p->opr.op[0]->linenum<<" the desination class of this extend class's name has not been defined: "<<p->opr.op[1]->id.s<<endl;
          					return;
          				}
           				 symtable[curscope.top()][p->opr.op[0]->id.s]=string("extend ")+string(p->opr.op[1]->id.s);
          			  	 curscope.push(p->opr.op[0]->id.s);
          			  	 map<string,string>varmap;

          			  	 map<string,string>::iterator iter2;
        			 	 for(iter2=symtable[p->opr.op[1]->id.s].begin();iter2!=symtable[p->opr.op[1]->id.s].end();++iter2)
        			 	 {
        			 	 	if(iter2->second!="function")
         			   			varmap[iter2->first]=iter2->second;
         			   		else
         			   			varmap[iter2->first]="efunction";
        			 	 }
          			  	 symtable[p->opr.op[0]->id.s]=varmap;

        			}
        			else
         			{
           			 	cout<<"line: "<<p->opr.op[0]->linenum<<" this extend class's name has been used: "<<p->opr.op[0]->id.s<<endl;
						return;
          			} 
					break;
				case IF: s = "if";break;
				case VAR: 
				{
					string scope;
						if(varintable(p->opr.op[0]->id.s,symtable,curscope,scope)==false&&!isbool(p->opr.op[0]->id.s))
          			{
          				if(strcmp(p->opr.op[1]->id.s,"integer")==0||strcmp(p->opr.op[1]->id.s,"boolean")==0)
          				{
           				 	symtable[curscope.top()][p->opr.op[0]->id.s]=p->opr.op[1]->id.s;
           				}
           				else
           				{
           					stack<string>temstack=curscope;
           					string scope;
           				 	if(varintable(p->opr.op[1]->id.s,symtable,temstack,scope)==false)
           						 cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's class has not been defined: "<<p->opr.op[1]->id.s<<endl;
           					else if(isbool(p->opr.op[1]->id.s))
           						 cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's name is illegal: "<<p->opr.op[1]->id.s<<endl;
           					else
           						symtable[curscope.top()][p->opr.op[0]->id.s]=p->opr.op[1]->id.s;
           				}
        			}
        			else
         			{
           			 	cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's name has been used: "<<p->opr.op[0]->id.s<<endl;
						return;
          			} 
          			break;
          		}
				case ARRAY: 
					if(symtable[curscope.top()].find(p->opr.op[0]->id.s)==symtable[curscope.top()].end()&&!isbool(p->opr.op[0]->id.s))
          			{
          				 if(strcmp(p->opr.op[2]->id.s,"integer")==0||strcmp(p->opr.op[2]->id.s,"boolean")==0)
          				{
          					char temstr[20]="";
          				 	sprintf(temstr,"%d",p->opr.op[1]->con.value);
           				 	string tem=temstr;
           				 	tem=tem+" array of ";
           				 	tem=tem+p->opr.op[2]->id.s;
           				 	symtable[curscope.top()][p->opr.op[0]->id.s]=tem;
           				}
           				else
           				{
           					string scope;
           					 if(varintable(p->opr.op[2]->id.s,symtable,curscope,scope)==false)
           						 cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's class has not been defined: "<<p->opr.op[2]->id.s<<endl;
           					 else if(isbool(p->opr.op[2]->id.s))
           					 {
            					 cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's class name is illegal: "<<p->opr.op[2]->id.s<<endl;
           					 }
           					 else
           					 {
           					 	char temstr[20]="";
          				 		sprintf(temstr,"%d",p->opr.op[1]->con.value);
           				 		string tem=temstr;
           				 		tem=tem+" array of ";
           				 		tem=tem+p->opr.op[2]->id.s;
           				 		symtable[curscope.top()][p->opr.op[0]->id.s]=tem;
           					 }		
           				 }
        			}
        			else
         			{
           			 	cout<<"line: "<<p->opr.op[0]->linenum<<" this array's name has been used: "<<p->opr.op[0]->id.s<<endl;
						return;
          			}  
					break;
				case CALLARRAY:
				{
					string varname=p->opr.op[0]->id.s;
					string scope;
					if(varintable(varname,symtable,curscope,scope)==false)
					{
						cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[0]->id.s<<endl;
						break;
					}
					
					if(p->opr.op[1]->opr.nops==1)
					{
						if(p->opr.op[1]->opr.op[0]->type==typeCon)
						{
							string type=symtable[scope][varname];
							varintable(type,symtable,curscope,scope);
							int size;
							getarrayinfo(symtable[scope][type],size,type);
							if(size<=p->opr.op[1]->opr.op[0]->con.value||p->opr.op[1]->opr.op[0]->con.value<0)
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this array is out of range: "<<p->opr.op[0]->id.s<<endl;
								break;
							}
						}
						else if(p->opr.op[1]->opr.op[0]->type==typeId)
						{
							if(varintable(p->opr.op[1]->opr.op[0]->id.s,symtable,curscope,scope)==false)
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[1]->opr.op[0]->id.s<<endl;
								break;
							}
							else
							{
								if(symtable[scope][p->opr.op[1]->opr.op[0]->id.s]!="integer")
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's type is not ingeter: "<<p->opr.op[1]->opr.op[0]->id.s<<endl;
									break;
								}
							}

						}
					}
					else if(p->opr.op[1]->opr.nops==2)
					{
						if(p->opr.op[1]->opr.op[0]->type==typeCon)
						{
								string type=symtable[scope][varname];
								varintable(type,symtable,curscope,scope);
								int size;
								getarrayinfo(symtable[scope][type],size,type);
								if(size<=p->opr.op[1]->opr.op[0]->con.value||p->opr.op[1]->opr.op[0]->con.value<0)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this array is out of range: "<<p->opr.op[0]->id.s<<endl;
									break;
								}
						}
						else if(p->opr.op[1]->opr.op[0]->type==typeId)
						{
							if(varintable(p->opr.op[1]->opr.op[0]->id.s,symtable,curscope,scope)==false)
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[1]->opr.op[0]->id.s<<endl;
								break;
							}
							else
							{
								if(symtable[scope][p->opr.op[1]->opr.op[0]->id.s]!="integer")
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's type is not ingeter: "<<p->opr.op[1]->opr.op[0]->id.s<<endl;
									break;
								}
							}
						}
							
						
						if(p->opr.op[1]->opr.op[1]->type==typeCon)
						{
							string type=symtable[scope][varname];
							int size;
							varintable(type,symtable,curscope,scope);
							getarrayinfo(symtable[scope][type],size,type);
							varintable(type,symtable,curscope,scope);
							getarrayinfo(symtable[scope][type],size,type);
							if(size<=p->opr.op[1]->opr.op[1]->con.value||p->opr.op[1]->opr.op[1]->con.value<0)
							{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this array is out of range: "<<p->opr.op[0]->id.s<<endl;
									break;
							}
						}
						else if(p->opr.op[1]->opr.op[1]->type==typeId)
						{
							if(varintable(p->opr.op[1]->opr.op[1]->id.s,symtable,curscope,scope)==false)
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[1]->opr.op[1]->id.s<<endl;
								break;
							}
							else
							{
								if(symtable[scope][p->opr.op[1]->opr.op[1]->id.s]!="integer")
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's type is not ingeter: "<<p->opr.op[1]->opr.op[1]->id.s<<endl;
									break;
								}
							}
						}
					}
					break;
				}
				case RETURN: s = "return";break;
				case FUNCTION: 
          			if(symtable[curscope.top()].find(p->opr.op[0]->id.s)==symtable[curscope.top()].end())
          			{
           				symtable[curscope.top()][p->opr.op[0]->id.s]="function";
          			  	curscope.push(p->opr.op[0]->id.s);
          			  	map<string,string>varmap;
         			   	symtable[p->opr.op[0]->id.s]=varmap;
        			}
        			else if(symtable[curscope.top()].find(p->opr.op[0]->id.s)->second=="efunction")
        			{
        				symtable[curscope.top()][p->opr.op[0]->id.s]="function";
        				curscope.push(p->opr.op[0]->id.s);
          			  	map<string,string>varmap;
         			   	symtable[p->opr.op[0]->id.s]=varmap;
        			}
          			else
         			{
           			 	cout<<"line: "<<p->opr.op[0]->linenum<<" this function's name has been used: "<<p->opr.op[0]->id.s<<endl;
						return;
          			}   
         			 break;
         		case CALLFUNCTION:
         			break;
				case PRINT:s = "print";break;
				case ';':s = "[;]";break;
				case ',':s = "[,]";break;
				case ASIGN:
				{	
					stack<string>temstack=curscope;
           			int flag=0;
           			string input=p->opr.op[0]->id.s;
           			string type;
           			if(input.find(".")==string::npos)
           			{
           				string scope;
						if(varintable(input,symtable,temstack,scope)==false)
							cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[0]->id.s<<endl;
						else
							type=symtable[scope][p->opr.op[0]->id.s];
					}
					else
					{
						string firvar=input.substr(0,input.find("."));
						string secvar=input.substr(input.find(".")+1,input.size());
						string firtype;
						string scope;
						
						if(varintable(firvar,symtable,temstack,scope)==false)
							cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<firvar<<endl;
						else
						{	
							firtype=symtable[scope][firvar];
							if(symtable[firtype].find(secvar)==symtable[firtype].end())
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined in class: "<<firtype<<" "<<secvar<<endl;
							else if(symtable[firtype][secvar]=="function")
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined in class: "<<firtype<<" "<<secvar<<endl;
							else
								type=symtable[firtype][secvar];
						}
					}
					switch(p->opr.op[1]->type)
					{
						case typeCon:
							if(type!="integer")
								cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type<<" value: "<<p->opr.op[1]->con.value<<endl;
							break;
						case typeId:
						{
							string scope;
							string input=p->opr.op[1]->id.s;
							if(isbool(p->opr.op[1]->id.s))
							{	
								if(type!="boolean")
								{
									 cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type<<" value: "<<p->opr.op[1]->id.s<<endl;
									 break;
								}
							}
							else if(input.find(".")!=string::npos)
							{
								string firvar=input.substr(0,input.find("."));
								string secvar=input.substr(input.find(".")+1,input.size());
								string firtype;
								string scope;
						
								if(varintable(firvar,symtable,curscope,scope)==false)
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<firvar<<endl;
								else
								{	
									firtype=symtable[scope][firvar];
									if(symtable[firtype].find(secvar)==symtable[firtype].end())
										cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined in class: "<<firtype<<" "<<secvar<<endl;
									else if(symtable[firtype][secvar]=="function")
										cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined in class: "<<firtype<<" "<<secvar<<endl;
									else
									{
										string type2=symtable[firtype][secvar];
										if(typeequal(type,type2,p->opr.op[0]->linenum)==false)
											cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type<<" value: "<<input<<endl;
									}
								}
							}
							else if(varintable(p->opr.op[1]->id.s,symtable,curscope,scope)==false)
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[1]->id.s<<endl;
							}
							else
							{
								string type2=symtable[scope][p->opr.op[1]->id.s];
								if(typeequal(type,type2,p->opr.op[0]->linenum)==false)
									cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type<<" value: "<<p->opr.op[1]->id.s<<endl;
							}
							break;
						}
						case typeOpr:
						{
							string scope;
							input=p->opr.op[1]->opr.op[0]->id.s;
							if(input.find(".")!=string::npos)
							{
								string firvar=input.substr(0,input.find("."));
								string secvar=input.substr(input.find(".")+1,input.size());
								string firtype;
								string scope;
						
								if(varintable(firvar,symtable,curscope,scope)==false)
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<firvar<<endl;
								else
								{	
									firtype=symtable[scope][firvar];
									if(symtable[firtype].find(secvar)==symtable[firtype].end())
										cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined in class: "<<firtype<<" "<<secvar<<endl;
									else if(symtable[firtype][secvar]=="function")
										cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined in class: "<<firtype<<" "<<secvar<<endl;
									else
									{
										string type2=symtable[firtype][secvar];
										if(typeequal(type,type2,p->opr.op[0]->linenum)==false)
											cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type<<" value: "<<input<<endl;
									}
								}
							}
							else if(varintable(p->opr.op[1]->opr.op[0]->id.s,symtable,curscope,scope)==false)
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<input<<endl;
							else
							{

								string type2=symtable[scope][p->opr.op[1]->opr.op[0]->id.s];
								if(typeequal(type,type2,p->opr.op[0]->linenum)==false)
									cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type<<" value: "<<input<<endl;
							}
						}
						

					}
					break;
				}
				case ARRAYASIGN:
				{
					string varname=p->opr.op[0]->id.s;
					string scope;
					string type1;
					if(varintable(varname,symtable,curscope,scope)==false)
					{
						cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[0]->id.s<<endl;
						break;
					}

					if(p->opr.op[1]->opr.nops==2)
					{
						string type=symtable[scope][varname];
						varintable(type,symtable,curscope,scope);
						int size;
						getarrayinfo(symtable[scope][type],size,type);

						if(p->opr.op[1]->opr.op[0]->type==typeCon)
						{
							if(size<=p->opr.op[1]->opr.op[0]->con.value||p->opr.op[1]->con.value<0)
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this array is out of range: "<<p->opr.op[0]->id.s<<endl;
								break;
							}
						}
						else if(p->opr.op[1]->opr.op[0]->type==typeId)
						{
							if(varintable(p->opr.op[1]->opr.op[0]->id.s,symtable,curscope,scope)==false)
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[1]->opr.op[0]->id.s<<endl;
								break;
							}
							else
							{
								if(symtable[scope][p->opr.op[1]->opr.op[0]->id.s]!="integer")
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's type is not integer: "<<p->opr.op[1]->opr.op[0]->id.s<<endl;
									break;
								}
							}
						}
						type1=type;
					}
					else if(p->opr.op[1]->opr.nops==3)
					{
						if(p->opr.op[1]->opr.op[0]->type==typeCon)
						{
								string type=symtable[scope][varname];
								varintable(type,symtable,curscope,scope);
								int size;
								getarrayinfo(symtable[scope][type],size,type);
								if(size<=p->opr.op[1]->opr.op[0]->con.value||p->opr.op[1]->opr.op[0]->con.value<0)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this array is out of range: "<<p->opr.op[0]->id.s<<endl;
									break;
								}
							
						}
						else if(p->opr.op[1]->opr.op[0]->type==typeId)
						{
							if(varintable(p->opr.op[1]->opr.op[0]->id.s,symtable,curscope,scope)==false)
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[1]->opr.op[0]->id.s<<endl;
								break;
							}
							else
							{
								if(symtable[scope][p->opr.op[1]->opr.op[0]->id.s]!="integer")
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's type is not integer: "<<p->opr.op[1]->opr.op[0]->id.s<<endl;
									break;
								}
							}
						}
						string type=symtable[scope][varname];
							int size;
							varintable(type,symtable,curscope,scope);
							getarrayinfo(symtable[scope][type],size,type);
							varintable(type,symtable,curscope,scope);
							getarrayinfo(symtable[scope][type],size,type);
						if(p->opr.op[1]->opr.op[1]->type==typeCon)
						{
							
							if(size<=p->opr.op[1]->opr.op[1]->con.value||p->opr.op[1]->opr.op[1]->con.value<0)
							{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this array is out of range: "<<p->opr.op[0]->id.s<<endl;
									break;
							}
						}
						else if(p->opr.op[2]->type==typeId)
						{
							if(varintable(p->opr.op[1]->opr.op[1]->id.s,symtable,curscope,scope)==false)
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[1]->opr.op[1]->id.s<<endl;
								break;
							}
							else
							{
								if(symtable[scope][p->opr.op[1]->opr.op[1]->id.s]!="integer")
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's type is not integer: "<<p->opr.op[1]->opr.op[1]->id.s<<endl;
									break;
								}
							}
						}
						type1=type;
					}

					/*switch(p->opr.op[arrayend]->type)
					{
						case typeCon:
							if(type1!="integer")
								cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<p->opr.op[arrayend]->con.value<<endl;
							break;
						case typeId:
						{
							string scope;
							string input=p->opr.op[arrayend]->id.s;
							if(isbool(p->opr.op[arrayend]->id.s))
							{	
								if(type1!="boolean")
								{
									 cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<p->opr.op[arrayend]->id.s<<endl;
									 break;
								}
							}
							else if(input.find(".")!=string::npos)
							{
								string firvar=input.substr(0,input.find("."));
								string secvar=input.substr(input.find(".")+1,input.size());
								string firtype;
								string scope;
						
								if(varintable(firvar,symtable,curscope,scope)==false)
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<firvar<<endl;
								else
								{	
									firtype=symtable[scope][firvar];
									if(symtable[firtype].find(secvar)==symtable[firtype].end())
										cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined in class: "<<firtype<<" "<<secvar<<endl;
									else if(symtable[firtype][secvar]=="function")
										cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined in class: "<<firtype<<" "<<secvar<<endl;
									else
									{
										string type2=symtable[firtype][secvar];
										if(typeequal(type1,type2,p->opr.op[0]->linenum)==false)
											cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<input<<endl;
									}
								}
							}
							else if(varintable(p->opr.op[arrayend]->id.s,symtable,curscope,scope)==false)
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[arrayend]->id.s<<endl;
							}
							else
							{
								string type2=symtable[scope][p->opr.op[arrayend]->id.s];
								if(typeequal(type1,type2,p->opr.op[0]->linenum)==false)
									cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<p->opr.op[arrayend]->id.s<<endl;
							}
							break;
						}
						case typeOpr:
						{
							string input=p->opr.op[arrayend]->opr.op[0]->id.s;
							if(input.find(".")!=string::npos)
							{
								string firvar=input.substr(0,input.find("."));
								string secvar=input.substr(input.find(".")+1,input.size());
								string firtype;
								string scope;
						
								if(varintable(firvar,symtable,curscope,scope)==false)
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<firvar<<endl;
								else
								{	
									firtype=symtable[scope][firvar];
									if(symtable[firtype].find(secvar)==symtable[firtype].end())
										cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined in class: "<<firtype<<" "<<secvar<<endl;
									else if(symtable[firtype][secvar]=="function")
										cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined in class: "<<firtype<<" "<<secvar<<endl;
									else
									{
										string type2=symtable[firtype][secvar];
										if(typeequal(type1,type2,p->opr.op[0]->linenum)==false)
											cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<input<<endl;
									}
								}
							}
							else if(varintable(p->opr.op[arrayend]->opr.op[0]->id.s,symtable,curscope,scope)==false)
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<input<<endl;
							else
							{

								string type2=symtable[scope][p->opr.op[arrayend]->opr.op[0]->id.s];
								if(typeequal(type1,type2,p->opr.op[0]->linenum)==false)
									cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<input<<endl;
							}
							break;
						}
						

					}*/


					break;
				}
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
			for(int i=0;i<p->opr.nops;i++)
			{
				pre_order(p->opr.op[i]);
			}
			switch(p->opr.oper)
			{
				case PROGRAM:
				{
					curscope.pop();
					map<string,map<string,string> >::iterator iter;
					for(iter=symtable.begin();iter!=symtable.end();++iter)
        			 {
        			 	cout<<"1key:  "<<iter->first<<":"<<endl;
        			 	map<string,string>::iterator iter2;
        			 	for(iter2=iter->second.begin();iter2!=iter->second.end();++iter2)
         			   		cout<<"2key:  "<<iter2->first<<"  :"<<iter2->second<<endl;
         			 } 
         			 break;
         		}
				case FUNCTION:
				{
					curscope.pop();
					break;
				}
				case CLASS:
				{
					curscope.pop();
					break;
				}
				case EXTENDS:
				{
					curscope.pop();
					break;
				}
			}
			break;
		}
	}

}
bool varintable(string varname,map<string,map<string,string> >symtable,stack<string> temstack,string& scope)
{
	while(temstack.size()>=1)
    {
		if(symtable[temstack.top()].find(varname)!=symtable[temstack.top()].end())
		{
			scope=temstack.top();
			return true;
		}
		temstack.pop();
	}
	return false;
}
bool isbool(char* varname)
{
	if(strcmp(varname,"yes")==0||strcmp(varname,"no")==0)
		return true;
	else 
		return false;
}
bool typeequal(string type1,string type2,int linenum,int arraynum)
{
	string scope1;
	string scope2;
	//cout<<type2<<endl;
	if(type1!="integer"&&type1!="boolean")
	{
		varintable(type1,symtable,curscope,scope1);
	
		if(symtable[scope1][type1].find("array")!=string::npos&&arraynum>0)
		{
			int size1;
			getarrayinfo(symtable[scope1][type1],size1,type1);
			if(type1!="integer"&&type1!="boolean")
			{
				varintable(type1,symtable,curscope,scope1);
				if(symtable[scope1][type1].find("array"&&arraynum>0)!=string::npos)
					getarrayinfo(symtable[scope1][type1],size1,type1);
			}
		}
	}
	if(type2!="integer"&&type2!="boolean")	
	{
		varintable(type2,symtable,curscope,scope2);
		if(symtable[scope2][type2].find("array")!=string::npos&&arraynum>0)
		{
			int size2;
			getarrayinfo(symtable[scope2][type2],size2,type2);
			if(type2!="integer"&&type2!="boolean")
			{
				varintable(type2,symtable,curscope,scope2);
				if(symtable[scope2][type2].find("array")!=string::npos&&arraynum>0)
					getarrayinfo(symtable[scope2][type2],size2,type2);
			}
		}	
	}
	if(type1==type2)
		return true;
	if(symtable[scope2][type2].find("extend")!=string::npos)
	{
		string desclass=symtable[scope2][type2].substr(symtable[scope2][type2].find("extend")+7,symtable[scope2][type2].size());
		if(desclass!=type1)
			return false;
		else
			return true;
	}
	else
		return false;
}

void getarrayinfo(string s,int& size,string& type)
{
	std::stringstream ss;
	string scope;
	ss<<s.substr(0,s.find("array"));
	ss>>size;
	type=s.substr(s.find("of")+3,s.size());
}