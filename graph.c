#include<stdio.h>
#include<string.h>
#include<map>
#include<stack>
#include<sstream>
#include"main.h"
#include"yacc.tab.h"

int del = 1;
int eps = 3;

int setin=0;

map<string,map<string,string> >symtable;
map<string,map<string,int> >functable;
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
bool typeequal(string type1,string type2,int linenum,int arraynum1,int arraynum2);

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
				case IS: s = "is"; break;
				case BEGINNING: s="beginning"; break;
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
		{
			if(setin==0)
			{	
				
				string input=p->id.s;
				if(input.find(".")==string::npos)
				{
					string scope;
					if( (varintable(p->id.s,symtable,curscope,scope)==false && !isbool(p->id.s) ) && (strcmp(p->id.s,"integer")!=0 && strcmp(p->id.s,"boolean")!=0 ) )
					{
						cout<<"line: "<<p->linenum<<" this variable has not been defined: "<<p->id.s<<endl;
						break;
					}
				}
				else
				{
					string firvar=input.substr(0,input.find("."));
						string secvar=input.substr(input.find(".")+1,input.size());
						string firtype;
						string scope;
						
						if(varintable(firvar,symtable,curscope,scope)==false)
							cout<<"line: "<<p->linenum<<" this variable has not been defined: "<<firvar<<endl;
						else
						{	
							firtype=symtable[scope][firvar];
							if(symtable[firtype].find(secvar)==symtable[firtype].end())
								cout<<"line: "<<p->linenum<<" this variable has not been defined in class: "<<firtype<<" "<<secvar<<endl;
						}
				}
			}
			break;
		}
		case typeOpr:
			switch(p->opr.oper)
			{
				case PROGRAM:
					if(symtable.find(p->opr.op[0]->id.s)==symtable.end()&&!isbool(p->opr.op[0]->id.s))
          			{
            			curscope.push(p->opr.op[0]->id.s);
            			map<string,string>varmap;
            			symtable[p->opr.op[0]->id.s]=varmap;
            			symtable[p->opr.op[0]->id.s][p->opr.op[0]->id.s]="program";
          			}
          			else
          			{
            			cout<<"line: "<<p->opr.op[0]->linenum<<" this program can not be named this"<<endl;
            			return;
          			}    
					break;
				case WHILE: 
					break;
				case REPEAT:s = "repeat";break;
				case FOREACH:
				{
					string input1=p->opr.op[0]->id.s;
					string input2=p->opr.op[1]->id.s;
           			string type1,type2;
           			if(input1.find(".")==string::npos)
           			{
           				string scope;
						if(varintable(input1,symtable,curscope,scope)==false)
							cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[0]->id.s<<endl;
						else
							type1=symtable[scope][p->opr.op[0]->id.s];
					}
					else
					{
						string firvar=input1.substr(0,input1.find("."));
						string secvar=input1.substr(input1.find(".")+1,input1.size());
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
								type1=symtable[firtype][secvar];
						}
					}
					if(input2.find(".")==string::npos)
           			{
           				string scope;
						if(varintable(input2,symtable,curscope,scope)==false)
							cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[0]->id.s<<endl;
						else
							type2=symtable[scope][p->opr.op[1]->id.s];
					}
					else
					{
						string firvar=input2.substr(0,input2.find("."));
						string secvar=input2.substr(input2.find(".")+1,input2.size());
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
								type2=symtable[firtype][secvar];
						}
					}
					string scope;
					varintable(type2,symtable,curscope,scope);
					string arrayinfo=symtable[scope][type2];
					if(arrayinfo.find("array")==string::npos)
					{
						cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not an array: "<<input2<<endl;
						break;
					}
					else
					{
						string testtype2;
						int tem;
						getarrayinfo(arrayinfo,tem,testtype2);
						if(type1!=testtype2)
						{	
							cout<<"line: "<<p->opr.op[0]->linenum<<" this variable: "<<input2<<" is not an array of: "<<input1<<endl;
							break;
						}
					}
					
					
					break;
				}
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
						break;
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
          					if(setin==2)
           					{
           						if(functable[curscope.top()].find(p->opr.op[0]->id.s)==functable[curscope.top()].end())
           						{
           							cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been declare in this function: "<<p->opr.op[0]->id.s<<endl;	
           						}
           					}
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
           					{
           						if(setin==2)
           						{
           							if(functable[curscope.top()].find(p->opr.op[0]->id.s)==functable[curscope.top()].end())
           							{
           								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been declare in this function: "<<p->opr.op[0]->id.s<<endl;	
           							}
           						}
           						symtable[curscope.top()][p->opr.op[0]->id.s]=p->opr.op[1]->id.s;
           					}
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
						string testtype;
						string testscope;
						testtype=symtable[scope][varname];
						varintable(testtype,symtable,curscope,testscope);
						string arrayinfo=symtable[testscope][testtype];
						if(arrayinfo.find("array")==string::npos)
						{
							cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not an array: "<<varname<<endl;
							break;
						}

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
						string testtype;
						string testscope;
						testtype=symtable[scope][varname];
						varintable(testtype,symtable,curscope,testscope);
						string arrayinfo=symtable[testscope][testtype];
						if(arrayinfo.find("array")==string::npos)
						{
							cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not an array: "<<varname<<endl;
							break;
						}

						int tem;
						getarrayinfo(arrayinfo,tem,testtype);
						varintable(testtype,symtable,curscope,testscope);
						arrayinfo=symtable[testscope][testtype];
						if(arrayinfo.find("array")==string::npos)
						{
							cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not an array: "<<varname<<endl;
							break;
						}

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
				case RETURN: break;
				case IS:
				{
					map<string,int>::iterator iter4;
        			 for(iter4=functable[curscope.top()].begin();iter4!=functable[curscope.top()].end();++iter4)
        			 {
        			 	string scope;
        			 	string varname=iter4->first;
         			   	if(varintable(varname,symtable,curscope,scope)==false)
         			   		cout<<"line: "<<p->linenum<<" there are some declared variables not be defined: "<<iter4->first<<endl;
         			 }
					if(setin==2)
						setin=3;
					break;
				}
				case BEGINNING:
					if(setin==3)
						setin=4;
					break;
				case FUNCTION: 
          			if(symtable[curscope.top()].find(p->opr.op[0]->id.s)==symtable[curscope.top()].end())
          			{
           				symtable[curscope.top()][p->opr.op[0]->id.s]="function";

           				string scopename;
						if(curscope.size()==1)
						{
         			   		scopename=p->opr.op[0]->id.s;
						}
         			   	else
         			   	{
         			   		scopename=p->opr.op[0]->id.s;
         			   		scopename=curscope.top()+"."+scopename;
         			   	}

          			  	
          			  	map<string,string>varmap;
          			  	if(p->opr.op[1]->type==typeOpr)
          			  	{
          			  		int i=0;
          			  		nodeType *temp=p->opr.op[1];
          			  		while(temp->type==typeOpr)
          			  		{
          			  			if(temp->opr.oper==',')
          			  			{
          			  				if(temp->opr.op[1]->type==typeCon)
          			  				{
          			  					cout<<"line: "<<p->opr.op[0]->linenum<<" this function's parameter cannot be a digit: "<<p->opr.op[0]->id.s<<endl;
										break;
          			  				}
          			  				else if(temp->opr.op[1]->type==typeOpr)
          			  				{
          			  					cout<<"line: "<<p->opr.op[0]->linenum<<" this function's parameter cannot be a expression: "<<p->opr.op[0]->id.s<<endl;
          			  				}
          			  				functable[scopename][temp->opr.op[1]->id.s]=i;
          			  				temp=temp->opr.op[0];
          			  				i++;
          			  			}
          			  			else
          			  			{
          			  				cout<<"line: "<<p->opr.op[0]->linenum<<" this function's parameter cannot be a expression: "<<p->opr.op[0]->id.s<<endl;
									break;
          			  			}
          			  			
          			  		}
          			  		if(temp->type==typeCon)
          			  		{
          			  			cout<<"line: "<<p->opr.op[0]->linenum<<" this function's parameter cannot be a digit: "<<p->opr.op[0]->id.s<<endl;
								break;
          			  		}
          			  		functable[scopename][temp->id.s]=i;
          			  	}
          			  	else if(p->opr.op[1]->type==typeId)
          			  	{
          			  		functable[scopename][p->opr.op[1]->id.s]=0;
          			  	}
          			  	else
          			  	{
          			  		cout<<"line: "<<p->opr.op[0]->linenum<<" this function's parameter cannot be a digit: "<<p->opr.op[0]->id.s<<endl;
							break;
          			  	}

          			  	
         			   	symtable[scopename]=varmap;
         			   	curscope.push(scopename);

        			}
        			else if(symtable[curscope.top()].find(p->opr.op[0]->id.s)->second=="efunction")
        			{
        				symtable[curscope.top()][p->opr.op[0]->id.s]="function";
          			  	map<string,string>varmap;
         			   	string scopename;
						if(curscope.size()==1)
						{
         			   		scopename=p->opr.op[0]->id.s;
						}
         			   	else
         			   	{
         			   		scopename=p->opr.op[0]->id.s;
         			   		scopename=curscope.top()+"."+scopename;
         			   	}

         			   	if(p->opr.op[1]->type==typeOpr)
          			  	{
          			  		int i=0;
          			  		nodeType *temp=p->opr.op[1];
          			  		while(temp->type==typeOpr)
          			  		{
          			  			if(temp->opr.oper==',')
          			  			{
          			  				if(temp->opr.op[1]->type==typeCon)
          			  				{
          			  					cout<<"line: "<<p->opr.op[0]->linenum<<" this function's parameter cannot be a digit: "<<p->opr.op[0]->id.s<<endl;
										break;
          			  				}
          			  				else if(temp->opr.op[1]->type==typeOpr)
          			  				{
          			  					cout<<"line: "<<p->opr.op[0]->linenum<<" this function's parameter cannot be a expression: "<<p->opr.op[0]->id.s<<endl;
          			  				}
          			  				functable[scopename][temp->opr.op[1]->id.s]=i;
          			  				temp=temp->opr.op[0];
          			  				i++;
          			  			}
          			  			else
          			  			{
          			  				cout<<"line: "<<p->opr.op[0]->linenum<<" this function's parameter cannot be a expression: "<<p->opr.op[0]->id.s<<endl;
									break;
          			  			}
          			  			
          			  		}
          			  		if(temp->type==typeCon)
          			  		{
          			  			cout<<"line: "<<p->opr.op[0]->linenum<<" this function's parameter cannot be a digit: "<<p->opr.op[0]->id.s<<endl;
								break;
          			  		}
          			  		functable[scopename][temp->id.s]=i;
          			  	}
          			  	else if(p->opr.op[1]->type==typeId)
          			  	{
          			  		functable[scopename][p->opr.op[1]->id.s]=0;
          			  	}
          			  	else
          			  	{
          			  		cout<<"line: "<<p->opr.op[0]->linenum<<" this function's parameter cannot be a digit: "<<p->opr.op[0]->id.s<<endl;
							break;
          			  	}

         			   	symtable[scopename]=varmap;
         			   	curscope.push(scopename);
        			}
          			else
         			{
           			 	cout<<"line: "<<p->opr.op[0]->linenum<<" this function's name has been used: "<<p->opr.op[0]->id.s<<endl;
						return;
          			}  

          			setin=2; 
         			 break;
         		case CALLFUNCTION:
         			break;
				case PRINT:s = "print";break;
				case ';':s = "[;]";break;
				case ',':
				{

					break;
				}
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
										int arraynum=0;
										
										if(typeequal(type,type2,p->opr.op[0]->linenum,0,arraynum)==false)
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
								int arraynum=0;
								if(typeequal(type,type2,p->opr.op[0]->linenum,0,arraynum)==false)
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
										int arraynum=0;
										if(typeequal(type,type2,p->opr.op[0]->linenum,0,arraynum)==false)
											cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type<<" value: "<<input<<endl;
									}
								}
							}
							else if(varintable(p->opr.op[1]->opr.op[0]->id.s,symtable,curscope,scope)==false)
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<input<<endl;
							else
							{

								string type2=symtable[scope][p->opr.op[1]->opr.op[0]->id.s];
								int arraynum=0;
								if(p->opr.op[1]->opr.op[1]->opr.oper==XIABIAO)
									arraynum=p->opr.op[1]->opr.op[1]->opr.nops;
								
								if(typeequal(type,type2,p->opr.op[0]->linenum,0,arraynum)==false)
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
					int arraynum1=p->opr.op[1]->opr.nops;
					if(varintable(varname,symtable,curscope,scope)==false)
					{
						cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[0]->id.s<<endl;
						break;
					}
					type1=symtable[scope][varname];



					if(p->opr.op[1]->opr.nops==1)
					{
						string testtype;
						string testscope;
						testtype=symtable[scope][varname];
						varintable(testtype,symtable,curscope,testscope);
						string arrayinfo=symtable[testscope][testtype];
						if(arrayinfo.find("array")==string::npos)
						{
							cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not an array: "<<varname<<endl;
							break;
						}

						string type=symtable[scope][varname];
						varintable(type,symtable,curscope,scope);
						//type1=type;
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
						
					}
					else if(p->opr.op[1]->opr.nops==2)
					{
						string testtype;
						string testscope;
						testtype=symtable[scope][varname];
						varintable(testtype,symtable,curscope,testscope);
						string arrayinfo=symtable[testscope][testtype];
						if(arrayinfo.find("array")==string::npos)
						{
							cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not an array: "<<varname<<endl;
							break;
						}

						int tem;
						getarrayinfo(arrayinfo,tem,testtype);
						varintable(testtype,symtable,curscope,testscope);
						arrayinfo=symtable[testscope][testtype];
						if(arrayinfo.find("array")==string::npos)
						{
							cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not an array: "<<varname<<endl;
							break;
						}

						string type=symtable[scope][varname];
								varintable(type,symtable,curscope,scope);
								int size;
								getarrayinfo(symtable[scope][type],size,type);
						if(p->opr.op[1]->opr.op[0]->type==typeCon)
						{
								
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
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's type is not integer: "<<p->opr.op[1]->opr.op[1]->id.s<<endl;
									break;
								}
								type1=type;
							}
						}
						
					}

					switch(p->opr.op[2]->type)
					{
						case typeCon:
							if(type1!="integer")
								cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<p->opr.op[2]->con.value<<endl;
							break;
						case typeId:
						{
							string scope;
							string input=p->opr.op[2]->id.s;
							if(isbool(p->opr.op[2]->id.s))
							{	
								if(type1!="boolean")
								{
									 cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<p->opr.op[2]->id.s<<endl;
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
										int arraynum=0;
										
										if(typeequal(type1,type2,p->opr.op[0]->linenum,arraynum1,arraynum)==false)
											cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<input<<endl;
									}
								}
							}
							else if(varintable(p->opr.op[2]->id.s,symtable,curscope,scope)==false)
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[2]->id.s<<endl;
							}
							else
							{

								string type2=symtable[scope][p->opr.op[2]->id.s];
								int arraynum2=0;
								if(typeequal(type1,type2,p->opr.op[0]->linenum,arraynum1,arraynum2)==false)
									cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<p->opr.op[2]->id.s<<endl;
							}
							break;
						}
						case typeOpr:
						{
							string scope;
							string input=p->opr.op[2]->opr.op[0]->id.s;
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
										int arraynum2=0;
										if(typeequal(type1,type2,p->opr.op[0]->linenum,arraynum1,arraynum2)==false)
											cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<input<<endl;
									}
								}
							}
							else if(varintable(p->opr.op[2]->opr.op[0]->id.s,symtable,curscope,scope)==false)
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<input<<endl;
							else
							{

								string type2=symtable[scope][p->opr.op[2]->opr.op[0]->id.s];
								int arraynum=0;
								if(p->opr.op[2]->opr.op[1]->opr.oper==XIABIAO)
									arraynum=p->opr.op[2]->opr.op[1]->opr.nops;
								
								if(typeequal(type1,type2,p->opr.op[0]->linenum,arraynum1,arraynum)==false)
									cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<input<<endl;
							}
						}
						

					}
					


					break;
				}
				case UMINUS:s = "[_]";break;
				case '+': case '-': case '*': case '/': case '%': case '<': case '>':case GE: case LE: case NE: case EQ: 
				{
					/*if()
					string input1=p->opr.op[0]->id.s;
					string input2=p->opr.op[1]->id.s;
           			string type1,type2;
           			if(input1.find(".")==string::npos)
           			{
           				string scope;
						if(varintable(input1,symtable,curscope,scope)==false)
							cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[0]->id.s<<endl;
						else
							type1=symtable[scope][p->opr.op[0]->id.s];
					}
					else
					{
						string firvar=input1.substr(0,input1.find("."));
						string secvar=input1.substr(input1.find(".")+1,input1.size());
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
								type1=symtable[firtype][secvar];
						}
					}
					if(input2.find(".")==string::npos)
           			{
           				string scope;
						if(varintable(input2,symtable,curscope,scope)==false)
							cout<<"line: "<<p->opr.op[0]->linenum<<" this variable has not been defined: "<<p->opr.op[0]->id.s<<endl;
						else
							type2=symtable[scope][p->opr.op[1]->id.s];
					}
					else
					{
						string firvar=input2.substr(0,input2.find("."));
						string secvar=input2.substr(input2.find(".")+1,input2.size());
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
								type2=symtable[firtype][secvar];
						}
					}
					cout<<type1<<" "<<type2<<endl;*/
					break;
				}
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
         			 cout<<endl;
         			 map<string,map<string,int> >::iterator iter3;
         			 for(iter3=functable.begin();iter3!=functable.end();++iter3)
        			 {
        			 	cout<<"1key:  "<<iter3->first<<":"<<endl;
        			 	map<string,int>::iterator iter4;
        			 	for(iter4=iter3->second.begin();iter4!=iter3->second.end();++iter4)
         			   		cout<<"2key:  "<<iter4->first<<"  :"<<iter4->second<<endl;
         			 } 

         			 break;
         		}
				case FUNCTION:
				{
					setin=0;
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
bool typeequal(string type1,string type2,int linenum,int arraynum1,int arraynum2)
{
	string scope1;
	string scope2;
	if(type1!="integer"&&type1!="boolean")
	{
		varintable(type1,symtable,curscope,scope1);
	
		if(symtable[scope1][type1].find("array")!=string::npos&&arraynum1>0)
		{
			int size1;
			arraynum1--;
			getarrayinfo(symtable[scope1][type1],size1,type1);
			if(type1!="integer"&&type1!="boolean")
			{
				varintable(type1,symtable,curscope,scope1);
				if(symtable[scope1][type1].find("array"&&arraynum1>0)!=string::npos)
					getarrayinfo(symtable[scope1][type1],size1,type1);
			}
		}
	}
	if(type2!="integer"&&type2!="boolean")	
	{
		varintable(type2,symtable,curscope,scope2);
		if(symtable[scope2][type2].find("array")!=string::npos&&arraynum2>0)
		{
			int size2;
			arraynum2--;
			getarrayinfo(symtable[scope2][type2],size2,type2);
			if(type2!="integer"&&type2!="boolean")
			{
				varintable(type2,symtable,curscope,scope2);
				if(symtable[scope2][type2].find("array")!=string::npos&&arraynum2>0)
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