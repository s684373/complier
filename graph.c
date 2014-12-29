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
stack<string> stackint;
stack<int> stacktype;



string curtype;

int id_num=0;

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
bool isbool(string varname);
bool typeequal(string type1,string type2,int linenum,int arraynum1,int arraynum2);
string assign_pre(nodeType *p);

string getidtype(string id,int linenum);

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
			if(setin==0||setin==4)
			{	
				
				string input=p->id.s;
				if(input.find(".")==string::npos)
				{
					string scope;
					if( (varintable(p->id.s,symtable,curscope,scope)==false && !isbool(input)) && (strcmp(p->id.s,"integer")!=0 && strcmp(p->id.s,"boolean")!=0 ) )
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
				{
					string name=p->opr.op[0]->id.s;
					if(symtable.find(p->opr.op[0]->id.s)==symtable.end()&&!isbool(name))
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
				}
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
							string type2=getidtype(p->opr.op[1]->opr.op[0]->id.s,p->opr.op[1]->opr.op[0]->linenum);
							if(type2!="integer")
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's type is not ingeter: "<<p->opr.op[1]->opr.op[0]->id.s<<endl;
								break;
							}
							

						}
						else if(p->opr.op[1]->opr.op[0]->type==typeOpr)
						{
							if(p->opr.op[1]->opr.op[0]->opr.oper==CALLARRAY)
							{
								string type2;
								type2=symtable[curscope.top()][p->opr.op[1]->opr.op[0]->opr.op[0]->id.s];
								int arraynum=p->opr.op[1]->opr.op[0]->opr.op[1]->opr.nops;
								if(typeequal("integer",type2,p->opr.op[0]->linenum,0,arraynum)==false)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer"<<endl;
									break;
								}
							}
							else if(p->opr.op[1]->opr.op[0]->opr.oper==CALLFUNCTION)
							{
								string type2;
								string funname;
								string scope;
								funname=p->opr.op[1]->opr.op[0]->opr.op[0]->id.s;
								type2=symtable[funname]["return"];
								if("integer"!=type2)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer "<<endl;
									break;
								}
							}
							else
							{
								if("integer"!=assign_pre(p->opr.op[1]->opr.op[0]))
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer"<<endl;
									while(!stacktype.empty())
										stacktype.pop();
									while(!stackint.empty())
										stackint.pop();
									id_num=0;
									break;
								}
								while(!stacktype.empty())
									stacktype.pop();
								while(!stackint.empty())
									stackint.pop();
								id_num=0;
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
							string type2=getidtype(p->opr.op[1]->opr.op[0]->id.s,p->opr.op[1]->opr.op[0]->linenum);
							if(type2!="integer")
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's type is not integer: "<<p->opr.op[1]->opr.op[0]->id.s<<endl;
								break;
							}
						}
						else if(p->opr.op[1]->opr.op[0]->type==typeOpr)
						{
							if(p->opr.op[1]->opr.op[0]->opr.oper==CALLARRAY)
							{
								string type2;
								type2=symtable[curscope.top()][p->opr.op[1]->opr.op[0]->opr.op[0]->id.s];
								int arraynum=p->opr.op[1]->opr.op[0]->opr.op[1]->opr.nops;
								if(typeequal("integer",type2,p->opr.op[0]->linenum,0,arraynum)==false)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer"<<endl;
									break;
								}
							}
							else if(p->opr.op[1]->opr.op[0]->opr.oper==CALLFUNCTION)
							{
								string type2;
								string funname;
								string scope;
								funname=p->opr.op[1]->opr.op[0]->opr.op[0]->id.s;
								type2=symtable[funname]["return"];
								if("integer"!=type2)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer "<<endl;
									break;
								}
							}
							else
							{
								if("integer"!=assign_pre(p->opr.op[1]->opr.op[0]))
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer"<<endl;
									while(!stacktype.empty())
										stacktype.pop();
									while(!stackint.empty())
										stackint.pop();
									id_num=0;
									break;
								}
								while(!stacktype.empty())
									stacktype.pop();
								while(!stackint.empty())
									stackint.pop();
								id_num=0;
							}
						}

							
						
						if(p->opr.op[1]->opr.op[1]->type==typeCon)
						{
							varintable(varname,symtable,curscope,scope);
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
							string type2=getidtype(p->opr.op[1]->opr.op[1]->id.s,p->opr.op[1]->opr.op[1]->linenum);
							if(type2!="integer")
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's type is not ingeter: "<<p->opr.op[1]->opr.op[1]->id.s<<endl;
								break;
							}
						}
						else if(p->opr.op[1]->opr.op[1]->type==typeOpr)
						{
							if(p->opr.op[1]->opr.op[1]->opr.oper==CALLARRAY)
							{
								string type2;
								type2=symtable[curscope.top()][p->opr.op[1]->opr.op[1]->opr.op[0]->id.s];
								int arraynum=p->opr.op[1]->opr.op[1]->opr.op[1]->opr.nops;
								if(typeequal("integer",type2,p->opr.op[0]->linenum,0,arraynum)==false)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer"<<endl;
									break;
								}
							}
							else if(p->opr.op[1]->opr.op[1]->opr.oper==CALLFUNCTION)
							{
								string type2;
								string funname;
								string scope;
								funname=p->opr.op[1]->opr.op[1]->opr.op[0]->id.s;
								type2=symtable[funname]["return"];
								if("integer"!=type2)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer "<<endl;
									break;
								}
							}
							else
							{
								if("integer"!=assign_pre(p->opr.op[1]->opr.op[1]))
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer"<<endl;
									while(!stacktype.empty())
										stacktype.pop();
									while(!stackint.empty())
										stackint.pop();
									id_num=0;
									break;
								}
								while(!stacktype.empty())
									stacktype.pop();
								while(!stackint.empty())
									stackint.pop();
								id_num=0;
							}
						}
					}
					break;
				}
				case RETURN: 
				{
					if(setin==2)
					{
						if(p->opr.op[0]->type!=typeId)
						{
							cout<<"line: "<<p->linenum<<" the declaration of return cannot be a expression: "<<endl;
							break;
						}
						if(strcmp(p->opr.op[0]->id.s,"integer")==0||strcmp(p->opr.op[0]->id.s,"boolean")==0)
          				{
           				 		symtable[curscope.top()]["return"]=p->opr.op[0]->id.s;
           				}
           				else
           				{
           					stack<string>temstack=curscope;
           					string scope;
           				 	if(varintable(p->opr.op[0]->id.s,symtable,temstack,scope)==false)
           						 cout<<"line: "<<p->linenum<<" this variable's class has not been defined: "<<p->opr.op[0]->id.s<<endl;
           					else if(isbool(p->opr.op[0]->id.s))
           						 cout<<"line: "<<p->linenum<<" this variable's name is illegal: "<<p->opr.op[0]->id.s<<endl;
           					else
           					{
           						symtable[curscope.top()]["return"]=p->opr.op[0]->id.s;
           					}
           				}
           			}
           			else if(setin==4)
           			{
           				if(symtable[curscope.top()].find("return")==symtable[curscope.top()].end())
           				{
           					cout<<"line: "<<p->linenum<<" this function should not has return value: "<<endl;
           					break;
           				}

           				if(p->opr.op[0]->type==typeCon)
           				{
           					if(symtable[curscope.top()]["return"]!="integer")
           					{
           						cout<<"line: "<<p->opr.op[0]->linenum<<" this function should not return this value: "<<endl;
           						break;
           					}
           				}
           				else if(p->opr.op[0]->type==typeId)
						{
							string type2=getidtype(p->opr.op[0]->id.s,p->linenum);
							if(typeequal(symtable[curscope.top()]["return"],type2,p->opr.op[0]->linenum,0,0)==false)
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this function should not return this value"<<endl;
								break;
							}
						}
						else if(p->opr.op[0]->type==typeOpr)
						{
							if(p->opr.op[0]->opr.oper==CALLARRAY)
							{
								string type2;
								type2=symtable[curscope.top()][p->opr.op[0]->opr.op[0]->id.s];
								int arraynum=p->opr.op[0]->opr.op[1]->opr.nops;
								if(typeequal(symtable[curscope.top()]["return"],type2,p->opr.op[0]->linenum,0,arraynum)==false)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this function should not return this value"<<endl;
									break;
								}
							}
							else if(p->opr.op[0]->opr.oper==CALLFUNCTION)
							{
								string type2;
								string funname;
								string scope;
								funname=p->opr.op[0]->opr.op[0]->id.s;
								type2=symtable[funname]["return"];
								if(symtable[curscope.top()]["return"]!=type2)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this function should not return this value "<<type2<<endl;
									break;
								}
							}
							else
							{
								if(symtable[curscope.top()]["return"]!=assign_pre(p->opr.op[0]))
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this function should not return this value"<<endl;
									while(!stacktype.empty())
										stacktype.pop();
									while(!stackint.empty())
										stackint.pop();
									id_num=0;
									break;
								}
								while(!stacktype.empty())
									stacktype.pop();
								while(!stackint.empty())
									stackint.pop();
								id_num=0;
							}
						}

           			}
					break;
				}
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
          			  		else if(temp->type==typeOpr)
          			  		{
          			  			cout<<"line: "<<p->opr.op[0]->linenum<<" this function's parameter cannot be a expression: "<<p->opr.op[0]->id.s<<endl;
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
         		{
         			string funname=p->opr.op[0]->id.s;
         			string scope;
         			if(funname.find(".")==string::npos)
					{
         				if(varintable(funname,symtable,curscope,scope)==false)
         				{
         					cout<<"line: "<<p->opr.op[0]->linenum<<" this function has not been defined "<<endl;
         					break;
         				}
         				else if(symtable[scope][funname]!="function"&&symtable[scope][funname]!="efunction")
         				{
         					cout<<"line: "<<p->opr.op[0]->linenum<<" this function has not been defined "<<endl;
         					break;
         				}
         			}
         			else
					{
						string firvar=funname.substr(0,funname.find("."));
						string secvar=funname.substr(funname.find(".")+1,funname.size());
						string firtype;
						
						if(varintable(firvar,symtable,curscope,scope)==false)
							cout<<"line: "<<p->linenum<<" this variable has not been defined: "<<firvar<<endl;
						else
						{	
							firtype=symtable[scope][firvar];
							if(symtable[firtype].find(secvar)==symtable[firtype].end())
							{
								cout<<"line: "<<p->linenum<<" this function has not been defined in class: "<<firtype<<" "<<secvar<<endl;
								break;
							}
							else if(symtable[firtype][secvar]!="function"&&symtable[firtype][secvar]!="efunction")
							{
								cout<<"line: "<<p->linenum<<" this function has not been defined in class: "<<firtype<<" "<<secvar<<endl;
								break;
							}
							else
								funname=firtype+"."+secvar;
						}
					}

         			int i=0;
         			if(p->opr.nops>=2)
         			{
         				nodeType *temp=p->opr.op[1];
         				while(temp->opr.oper==',')
          				{
          					i++;
          					temp=temp->opr.op[0];
          				}
          				i++;
          			}
          			if(i!=functable[funname].size())
          				cout<<"line: "<<p->opr.op[0]->linenum<<" this function's parameters' number is wrong"<<endl;

          			i=0;
          			if(p->opr.nops>=2)
         			{
         				nodeType *temp=p->opr.op[1];
         				while(temp->opr.oper==',')
          				{
          					string type1;
          					map<string,int>::iterator iter4;
        			 		for(iter4=functable[funname].begin();iter4!=functable[funname].end();++iter4)
        			 		{
         			   			if(iter4->second==i)
         			   				type1=symtable[funname][iter4->first];
         			   		}

          			 	 	if(temp->opr.op[1]->type==typeCon)
          			 	 	{
         			   			if(type1!="integer")
         			   			{
         			   				cout<<"line: "<<p->opr.op[0]->linenum<<" this function's parameters' cannot be fitted"<<endl;
         			   				break;
         			   			}
          			  		}
          			  		else if(temp->opr.op[1]->type==typeId)
          			  		{
          			  			string type2=getidtype(temp->opr.op[1]->id.s,temp->opr.op[1]->linenum);
								if(type1!=type2)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this function's parameters' cannot be fitted"<<endl;
									break;
								}
          				  	}
          				  	else if(temp->opr.op[1]->type==typeOpr)
          				  	{
          				  		if(temp->opr.op[1]->opr.oper==CALLARRAY)
								{
									string type2;
									type2=symtable[curscope.top()][temp->opr.op[1]->opr.op[0]->id.s];
									int arraynum=temp->opr.op[1]->opr.op[1]->opr.nops;
									if(typeequal(type1,type2,temp->opr.op[1]->linenum,0,arraynum)==false)
									{
										cout<<"line: "<<p->opr.op[1]->linenum<<" this function's parameters' cannot be fitted"<<endl;
										break;
									}
								}
								else if(temp->opr.op[1]->opr.oper==CALLFUNCTION)
								{
									string type2;
									string funname;
									string scope;
									funname=temp->opr.op[1]->opr.op[0]->id.s;
									type2=symtable[funname]["return"];
									if(type1!=type2)
									{
										cout<<"line: "<<temp->opr.op[1]->linenum<<" this function's parameters' cannot be fitted"<<endl;
										break;
									}
								}
								else
								{
									if(type1!=assign_pre(temp->opr.op[1]))
									{
										cout<<"line: "<<temp->opr.op[1]->linenum<<" this function's parameters' cannot be fitted"<<endl;
										while(!stacktype.empty())
										stacktype.pop();
										while(!stackint.empty())
										stackint.pop();
										id_num=0;
										break;
									}
									while(!stacktype.empty())
										stacktype.pop();
									while(!stackint.empty())
										stackint.pop();
									id_num=0;
								}
          				  	}
          			 	 	temp=temp->opr.op[0];
          			  		i++;
          			  
          			  	}

          			  		string type1;
          					map<string,int>::iterator iter4;
        			 		for(iter4=functable[funname].begin();iter4!=functable[funname].end();++iter4)
        			 		{
         			   			if(iter4->second==i)
         			   				type1=symtable[funname][iter4->first];
         			   		}

          			 	 	if(temp->type==typeCon)
          			 	 	{
         			   			if(type1!="integer")
         			   			{
         			   				cout<<"line: "<<temp->linenum<<" this function's parameters' cannot be fitted"<<endl;
         			   				break;
         			   			}
          			  		}
          			  		else if(temp->type==typeId)
          			  		{
          			  			string type2=getidtype(temp->id.s,temp->linenum);
								if(type1!=type2)
								{
									cout<<"line: "<<temp->linenum<<" this function's parameters' cannot be fitted"<<endl;
									break;
								}
          				  	}
          				  	else if(temp->type==typeOpr)
          				  	{
          				  		if(temp->opr.oper==CALLARRAY)
								{
									string type2;
									type2=symtable[curscope.top()][temp->opr.op[0]->id.s];
									int arraynum=temp->opr.op[1]->opr.nops;
									if(typeequal(type1,type2,temp->linenum,0,arraynum)==false)
									{
										cout<<"line: "<<p->linenum<<" this function's parameters' cannot be fitted"<<endl;
										break;
									}
								}
								else if(temp->opr.oper==CALLFUNCTION)
								{
									string type2;
									string funname;
									string scope;
									funname=temp->opr.op[0]->id.s;
									type2=symtable[funname]["return"];
									if(type1!=type2)
									{
										cout<<"line: "<<temp->linenum<<" this function's parameters' cannot be fitted"<<endl;
										break;
									}
								}
								else
								{
									if(type1!=assign_pre(temp))
									{
										cout<<"line: "<<temp->linenum<<" this function's parameters' cannot be fitted"<<endl;
										while(!stacktype.empty())
										stacktype.pop();
										while(!stackint.empty())
										stackint.pop();
										id_num=0;
										break;
									}
									while(!stacktype.empty())
										stacktype.pop();
									while(!stackint.empty())
										stackint.pop();
									id_num=0;
								}
          				  	}

          			}
         			break;
         		}
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
							string type2;
							if(p->opr.op[1]->opr.op[1]->opr.oper==XIABIAO)
							{
								type2=symtable[curscope.top()][p->opr.op[1]->opr.op[0]->id.s];
								int arraynum=p->opr.op[1]->opr.op[1]->opr.nops;
								if(typeequal(type,type2,p->opr.op[0]->linenum,0,arraynum)==false)
									cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type<<" value: "<<input<<endl;
							}
							else if(p->opr.op[1]->opr.op[0]->opr.oper==CALLFUNCTION)
							{
								string type2;
								string funname;
								string scope;
								funname=p->opr.op[1]->opr.op[0]->opr.op[0]->id.s;
								type2=symtable[funname]["return"];
								if(type!=type2)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type<<" value: "<<input<<endl;
									break;
								}
							}
							else
							{	
								if(type!=assign_pre(p->opr.op[1]))
									cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<assign_pre(p->opr.op[1])<<" value: "<<input<<endl;
								while(!stacktype.empty())
									stacktype.pop();
								while(!stackint.empty())
									stackint.pop();
								id_num=0;

							}
							break;
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
							string type2=getidtype(p->opr.op[1]->opr.op[0]->id.s,p->opr.op[1]->opr.op[0]->linenum);
							if(type2!="integer")
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's type is not ingeter: "<<p->opr.op[1]->opr.op[0]->id.s<<endl;
								break;
							}
						}
						else if(p->opr.op[1]->opr.op[0]->type==typeOpr)
						{
							if(p->opr.op[1]->opr.op[0]->opr.oper==CALLARRAY)
							{
								string type2;
								type2=symtable[curscope.top()][p->opr.op[1]->opr.op[0]->opr.op[0]->id.s];
								int arraynum=p->opr.op[1]->opr.op[0]->opr.op[1]->opr.nops;
								if(typeequal("integer",type2,p->opr.op[0]->linenum,0,arraynum)==false)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer"<<endl;
									break;
								}
							}
							else if(p->opr.op[1]->opr.op[0]->opr.oper==CALLFUNCTION)
							{
								string type2;
								string funname;
								string scope;
								funname=p->opr.op[1]->opr.op[0]->opr.op[0]->id.s;
								type2=symtable[funname]["return"];
								if("integer"!=type2)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer "<<endl;
									break;
								}
							}
							else
							{
								if("integer"!=assign_pre(p->opr.op[1]->opr.op[0]))
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer"<<endl;
									while(!stacktype.empty())
										stacktype.pop();
									while(!stackint.empty())
										stackint.pop();
									id_num=0;
									break;
								}
								while(!stacktype.empty())
									stacktype.pop();
								while(!stackint.empty())
									stackint.pop();
								id_num=0;
							}
						}
						type1=type;
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
							string type2=getidtype(p->opr.op[1]->opr.op[0]->id.s,p->opr.op[1]->opr.op[0]->linenum);
							if(type2!="integer")
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's type is not ingeter: "<<p->opr.op[1]->opr.op[0]->id.s<<endl;
								break;
							}
						}
						else if(p->opr.op[1]->opr.op[0]->type==typeOpr)
						{
							if(p->opr.op[1]->opr.op[0]->opr.oper==CALLARRAY)
							{
								string type2;
								type2=symtable[curscope.top()][p->opr.op[1]->opr.op[0]->opr.op[0]->id.s];
								int arraynum=p->opr.op[1]->opr.op[0]->opr.op[1]->opr.nops;
								if(typeequal("integer",type2,p->opr.op[0]->linenum,0,arraynum)==false)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer"<<endl;
									break;
								}
							}
							else if(p->opr.op[1]->opr.op[0]->opr.oper==CALLFUNCTION)
							{
								string type2;
								string funname;
								string scope;
								funname=p->opr.op[1]->opr.op[0]->opr.op[0]->id.s;
								type2=symtable[funname]["return"];
								if("integer"!=type2)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer "<<endl;
									break;
								}
							}
							else
							{
								if("integer"!=assign_pre(p->opr.op[1]->opr.op[0]))
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer"<<endl;
									while(!stacktype.empty())
										stacktype.pop();
									while(!stackint.empty())
										stackint.pop();
									id_num=0;
									break;
								}
								while(!stacktype.empty())
									stacktype.pop();
								while(!stackint.empty())
									stackint.pop();
								id_num=0;
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
							string type2=getidtype(p->opr.op[1]->opr.op[1]->id.s,p->opr.op[1]->opr.op[1]->linenum);
							if(type2!="integer")
							{
								cout<<"line: "<<p->opr.op[0]->linenum<<" this variable's type is not ingeter: "<<p->opr.op[1]->opr.op[1]->id.s<<endl;
								break;
							}
						}
						else if(p->opr.op[1]->opr.op[1]->type==typeOpr)
						{
							if(p->opr.op[1]->opr.op[1]->opr.oper==CALLARRAY)
							{
								string type2;
								type2=symtable[curscope.top()][p->opr.op[1]->opr.op[1]->opr.op[0]->id.s];
								int arraynum=p->opr.op[1]->opr.op[1]->opr.op[1]->opr.nops;
								if(typeequal("integer",type2,p->opr.op[0]->linenum,0,arraynum)==false)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer"<<endl;
									break;
								}
							}
							else if(p->opr.op[1]->opr.op[1]->opr.oper==CALLFUNCTION)
							{
								string type2;
								string funname;
								string scope;
								funname=p->opr.op[1]->opr.op[1]->opr.op[0]->id.s;
								type2=symtable[funname]["return"];
								if("integer"!=type2)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer "<<endl;
									break;
								}
							}
							else
							{
								if("integer"!=assign_pre(p->opr.op[1]->opr.op[1]))
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this variable is not a integer"<<endl;
									while(!stacktype.empty())
										stacktype.pop();
									while(!stackint.empty())
										stackint.pop();
									id_num=0;
									break;
								}
								while(!stacktype.empty())
									stacktype.pop();
								while(!stackint.empty())
									stackint.pop();
								id_num=0;
							}
						}
						type1=type;
						
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
							if(isbool(input))
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
										
										if(typeequal(type1,type2,p->opr.op[0]->linenum,0,arraynum)==false)
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
								if(typeequal(type1,type2,p->opr.op[0]->linenum,0,arraynum2)==false)
									cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<p->opr.op[2]->id.s<<endl;
							}
							break;
						}
						case typeOpr:
						{
							string type2;

							if(p->opr.op[2]->opr.op[1]->opr.oper==XIABIAO)
							{
								type2=symtable[curscope.top()][p->opr.op[2]->opr.op[0]->id.s];
								string input=p->opr.op[0]->id.s;
								int arraynum=p->opr.op[2]->opr.op[1]->opr.nops;
								if(typeequal(type1,type2,p->opr.op[0]->linenum,0,arraynum)==false)
									cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<input<<endl;
							}
							else if(p->opr.op[2]->opr.op[0]->opr.oper==CALLFUNCTION)
							{
								string type2;
								string funname;
								string scope;
								string input=p->opr.op[0]->id.s;
								funname=p->opr.op[2]->opr.op[0]->opr.op[0]->id.s;
								type2=symtable[funname]["return"];
								if(typeequal(type1,type2,p->opr.op[0]->linenum,0,0)==false)
								{
									cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<input<<endl;
									break;
								}
							}
							else
							{	
								string input=p->opr.op[0]->id.s;
								if(type1!=assign_pre(p->opr.op[2]))
									cout<<"line: "<<p->opr.op[0]->linenum<<" this value can not be setted to this variable ||type: "<<type1<<" value: "<<input<<endl;
								while(!stacktype.empty())
									stacktype.pop();
								while(!stackint.empty())
									stackint.pop();
								id_num=0;
							}
							break;
						}
						

					}


					break;
				}
				case UMINUS:s = "[_]";break;
				case '+': case '-': case '*': case '/': case '%': case '<': case '>':case GE: case LE: case NE: case EQ: 
				{
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
					if(functable[curscope.top()].find("return")!=functable[curscope.top()].end())
						if(symtable[curscope.top()].find("return")==symtable[curscope.top()].end())
							cout<<"line: "<<p->opr.op[0]->linenum<<" this function should has a return value"<<endl;

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
bool isbool(string varname)
{
	if(varname=="yes"||varname=="no")
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
				if(symtable[scope1][type1].find("array")!=string::npos&&arraynum1>0)
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

string assign_pre(nodeType *p)
{                  

	if(p!=NULL)
	{

		char *s;
		string str;
		switch(p->type)
		{
			case typeCon:
				char word[20];
				sprintf(word,"%d",p->con.value);
				s=word;
				str = "integer";
				stackint.push(str);
				stacktype.push(1);
				id_num++;  
				break;
			case typeId:
			{

				s = p->id.s;
				str=s;
				if(str=="yes"||str=="no")
					str="boolean";
				else
				{
					string scope;
					varintable(str,symtable,curscope,scope);
					str=symtable[scope][s];
				}
				stackint.push(str);
				stacktype.push(2);
				id_num++;
				break;
			}
			case typeOpr:
			{
				if(p->opr.oper==CALLARRAY)
				{
					int arraynum1=p->opr.op[1]->opr.nops;
					string scope1;
					string type1=symtable[curscope.top()][p->opr.op[0]->id.s];
					varintable(type1,symtable,curscope,scope1);
					
					if(symtable[scope1][type1].find("array")!=string::npos&&arraynum1>0)
					{
						int size1;
						arraynum1--;
						getarrayinfo(symtable[scope1][type1],size1,type1);
						varintable(type1,symtable,curscope,scope1);
						if(symtable[scope1][type1].find("array")!=string::npos&&arraynum1>0)
							getarrayinfo(symtable[scope1][type1],size1,type1);
						
					}
					str=type1;
					stacktype.push(2);
					stackint.push(str);	
					id_num++;
					break;
				}
				else if(p->opr.oper==CALLFUNCTION)
				{
					string type2;
					string funname;
					string scope;
					funname=p->opr.op[0]->id.s;

					type2=symtable[funname]["return"];

					str=type2;
					stacktype.push(2);
					stackint.push(str);	
					id_num++;
					break;
				}
				else
				{
					switch(p->opr.oper)
					{
						case '+':s = "[+]";break;
						case '-':s = "[-]";break;
						case '*':s = "[*]";break;
						case '/':s = "[/]";break;
						case '%':s = "[%]";break;
						case '>':s = "[>]";break;
						case '<':s = "[<]";break;
						case 'GE':s = "[<=]";break;
						case 'LE':s = "[>=]";break;
						case 'NE':s = "[!=]";break;
						case 'EQ':s = "[==]";break;
						case 'AND':s = "[&&]";break;
						case 'OR':s = "[||]";break;
					}
					id_num = 0;
					str =s;
					stacktype.push (3);
					stackint.push(str);	
					break;
				}
			}
				
		}	
		while(id_num == 2)
		{
			string s1,s2,s3;
			string ans;
			s1 = stackint.top();
			stackint.pop();
			s2 = stackint.top();
			stackint.pop();
			s3 = stackint.top();
			stackint.pop();

			string outcome;
			stacktype.pop();
			stacktype.pop();
			if(stacktype.top() == 3)
			{
				
				if((s3=="[+]"||s3=="[*]")||(s3=="[-]"||s3=="[/]"))
				{
					if(s1!="integer"||s2!="integer")
					{
						cout<<"line: "<<p->linenum<<" this operation cannot be setted between there: "<<s1<<" "<<s2<<endl;
						break;
					}
					outcome="integer";
				}
				else if(s3=="[<]"||s3=="[>]"||s3=="[<=]"||s3=="[>=]"||s3=="[!=]"||s3=="[==]") 
				{
					if(s1!="integer"||s2!="integer")
					{
						cout<<"line: "<<p->linenum<<" this operation cannot be setted between there: "<<s1<<" "<<s2<<endl;
						break;
					}
					outcome="boolean";
				}
				else if(s3=="[&&]"||s3=="[||]")
				{
					if(s1!="boolean"||s2!="boolean")
					{
						cout<<"line: "<<p->linenum<<" this operation cannot be setted between there: "<<s1<<" "<<s2;
						break;
					}
					outcome="boolean";
				}
			}
			stacktype.pop();
			stackint.push(outcome);
			curtype=outcome;
			if(!stacktype.empty())
			{	
				int s = stacktype.top();
				if(s == 1 || s == 2)
					id_num = 1;
				else
					id_num = 0;
			}
			stacktype.push(2);
			id_num ++;
		}

		if(p->opr.oper!=CALLARRAY&&p->opr.oper!=CALLFUNCTION)
		{
			for(int i=0;i<p->opr.nops;i++)
				assign_pre(p->opr.op[i]);
		}
	}

	return curtype;
}

string getidtype(string id,int linenum)
{
	string scope;
	string input=id;
	string type2;
	if(isbool(input))
	{	
		return "boolean";
	}
	else if(input.find(".")!=string::npos)
	{
		string firvar=input.substr(0,input.find("."));
		string secvar=input.substr(input.find(".")+1,input.size());
		string firtype;
		string scope;
						
		if(varintable(firvar,symtable,curscope,scope)==false)
			cout<<"line: "<<linenum<<" this variable has not been defined: "<<firvar<<endl;
		else
		{	
			firtype=symtable[scope][firvar];
			if(symtable[firtype].find(secvar)==symtable[firtype].end())
				cout<<"line: "<<linenum<<" this variable has not been defined in class: "<<firtype<<" "<<secvar<<endl;
			else if(symtable[firtype][secvar]=="function")
				cout<<"line: "<<linenum<<" this variable has not been defined in class: "<<firtype<<" "<<secvar<<endl;
			else
			{
				type2=symtable[firtype][secvar];
			}
		}
	}
	else if(varintable(input,symtable,curscope,scope)==false)
		{
			cout<<"line: "<<linenum<<" this variable has not been defined: "<<input<<endl;
		}	
	else
		{
			type2=symtable[scope][input];
		}
		return type2;
}