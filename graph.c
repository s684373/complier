#include<stdio.h>
#include<string.h>
#include <sstream>
#include <fstream>
#include"main.h"
#include"yacc.tab.h"
#include <string>
#include <stdlib.h>
#include <stack>
#include <map>
using namespace std;
int del = 1;
int eps = 3;
ofstream out("out.txt"); 
stack<string> stackint;
stack<int> stacktype;
map<string , int >mapstring;
class Code
{
	public:
		Code()
		{
			regi = 1;
			ret = "ret i32 0";
			printtou = "@.str = private unnamed_addr constant [3 x i8] c\"%d\\00\", align 1";
			printdefine = "call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32 %";
			printdeclare = "declare i32 @printf(i8*, ...)";
		}
		string start = "define i32 @main() nounwind uwtable";
		int regi;
		string getallo = "alloca i32, align 4";
		string printdefine;
		string printtou;
		string printdeclare;
		void print(char *s)
		{
			string str(s);
			string ss = "%" + numtostr(regi) + "=" + "load i32* %" + str+",align 4";
			out << ss << endl;
			regi++;
			string s1 = "%" + numtostr(regi) + "=" + printdefine + numtostr(regi-1)+")";
			out << s1 << endl;
			regi++;
		}
		string globaldefine(int num , char *s)
		{
			string str(s);
			return "%"+str+"="+"global i32 "+numtostr(num)+", align 4";
		}
		string numtostr(int num)
		{
			char t[256];
    		string s;
    		sprintf(t, "%d", num);
    		s = t;
    		return s;
		}
		void load(char *s1)
		{
			string str(s1);
			string s = "%"+numtostr(regi++) + "=load i32* %"+str;
			s += ", align 4";
			out << s << endl;
		}
		void compare(string o,int cp)
		{
			string cmp[10]={"eq","sgt","slt","ne"};
			string s = "%" + numtostr(regi++);
			s += "= icmp " + cmp[cp] + " i32 %" + numtostr(regi - 2)
				+ "," + o;
			out << s << endl;
			string s2 = "br i1 %" + numtostr(regi - 1);
			s2 += ", label %if_then , label %if_else";
			out << s2 << endl;
		}
		string store(char *s1 , int s2)
		{
			string s;
			string str1(s1);
			string str2 = numtostr(s2);
			s = "store i32 " + str2;
			s +=",i32* %" + str1 + ", align 4";
			mapstring[str1] = s2;
			return s;
		}
		int stringtonum(string s)
		{
			int ans = atoi(s.c_str());
			return ans;
		}
		string assign_two_con(string str1 , string str2 , string str3)
		{
			int a2 = atoi(str1.c_str());
			int a1 = atoi(str2.c_str());
			int ans = 0;
			if(str3 == "[+]")
				ans = a1 + a2;
			else if(str3 == "[-]")
				ans = a1 - a2;
			else if(str3 == "[*]")
				ans = a1 * a2;
			else if(str3 == "[/]")
				ans = a1 / a2;
			else if(str3 == "[%]")
				ans = a1 % a2;
			return numtostr(ans);
		}
		void store_id(char *s1 , char *s2)
		{
			string s;
			string str1(s1);
			string str2(s2);
			s = "%" + numtostr(regi++) + "= load i32* %" + str1 + ",align 4";
			out << s << endl;
			s =  "store i32 %" + numtostr(regi - 1) + ",i32* %" + str2 + ",align 4";
			out << s << endl;
			mapstring[str2]=mapstring[str1];
		}
		string register_allo(int r) 
		{
    		 string s = numtostr(r);
    		 s = '%' + s;
    		 s += '=' + getallo;
    		 regi++;
			 return s;
	    }
	    void label(string s1)
	    {
	    	out << s1 << endl;
	    }
	    string register_allo_n(char *s) 
		{
    		 string str(s);
    		 str="%"+str+"=";
    		 return str+getallo;
	    }
	    string ret;
};
Code a;
void graphInit(void);
void graphFinish();
void graphBox(char *s,int *w,int *h);
void graphDrawBox(char *s,int c,int l);
void graphDrawArrow(int c1,int ll,int c2,int l2);

void exNode(nodeType *p,int c,int l,int *ce,int *cm);

void semanalysis(nodeType *p);
void ppre_order(nodeType *p);

int ex(nodeType *p){
	int rte,rtm;
	semanalysis(p);
	return 0;
}
string chartostring(char *s)
{
	string ans(s);
	return ans;
}
void semanalysis(nodeType *p)
{
	ppre_order(p);
	out<< a.printdeclare << endl;
}
int id_num = 0;
void assign_pre_order(nodeType *p)
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
				str = chartostring(s);
				stackint.push(str);
				stacktype.push(1);
				id_num++;
				break;
			case typeId:
				s = p->id.s;
				str = chartostring(s);
				stackint.push(str);
				stacktype.push(2);
				id_num++;
				break;
			case typeOpr:
			switch(p->opr.oper)
			{
				case '+':s = "[+]";break;
				case '-':s = "[-]";break;
				case '*':s = "[*]";break;
				case '/':s = "[/]";break;
				case '%':s = "[%]";break;
			}
				id_num = 0;
				str = chartostring(s);
				stackint.push(str);
				stacktype.push(3);
				break;
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
			if(stacktype.top()==2)
				s1 = a.numtostr(mapstring[s1]);
			stacktype.pop();
			if(stacktype.top()==2)
				s2 = a.numtostr(mapstring[s2]);			
			stacktype.pop();
			stacktype.pop();
			ans = a.assign_two_con(s1,s2,s3);
			stackint.push(ans);
			if(!stacktype.empty())
			{	
				int s = stacktype.top();
				if(s == 1 || s == 2)
					id_num = 1;
				else
					id_num = 0;
			}
			stacktype.push(1);
			/*if(stacktype.top() == 1)
			{
				stacktype.pop();
				string ans;
				string s1,s2,s3;
				s1 = stackint.top();
				stackint.pop();
				s2 = stackint.top();
				stackint.pop();
				s3 = stackint.top();
				stackint.pop();
				if(stacktype.top() == 1)
				{
					ans = a.assign_two_con(s1,s2,s3);
					stacktype.pop();
					stacktype.pop();
					stackint.push(ans);
					if(!stacktype.empty())
					{	
						int s = stacktype.top();
						if(s == 1 || s == 2)
							id_num = 1;
						else
							id_num = 0;
					}
					stacktype.push(1);
				}
			}*/
			id_num ++;
		}
		for(int i=0;i<p->opr.nops;i++)
			{
				assign_pre_order(p->opr.op[i]);
			}
	}
}
void if_expression(nodeType *p)
{
	string rightval;
	if(p->opr.op[1]->type == typeOpr)
	{
		if(p->opr.op[1]->opr.oper == '+'
			|| p->opr.op[1]->opr.oper == '-'
			|| p->opr.op[1]->opr.oper == '*'
			||p->opr.op[1]->opr.oper == '/')
		{
		 	assign_pre_order(p->opr.op[1]);
			rightval = stackint.top();
			stackint.pop();
			stacktype.pop();
		}
	}
	else if(p->opr.op[1]->type == typeCon)
		rightval = a.numtostr(p->opr.op[1]->con.value);
	else
		rightval = a.numtostr(mapstring[chartostring(p->opr.op[1]->id.s)]);
	switch(p->type)
	{
		case typeOpr:
		switch(p->opr.oper)
		{
			case EQ:
				a.load(p->opr.op[0]->id.s);
				a.compare(rightval,0);
				a.label("if_then:");
			break;
			case GE:
				a.load(p->opr.op[0]->id.s);
				a.compare(rightval,1);
				a.label("if_then:");
			break;
			case LE:
				a.load(p->opr.op[0]->id.s);
				a.compare(rightval,2);
				a.label("if_then:");
			break;
			case NE:
				a.load(p->opr.op[0]->id.s);
				a.compare(rightval,3);
				a.label("if_then:");
			break; 
		}
	}
}
void ppre_order(nodeType *p)
{
	if(p!=NULL)
	{
		char* s;
		int temp = 0;
		bool isvar = false;
		bool isassign = false;
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
					s = "program";
					out << a.printtou << endl;
					out << a.start << '{' << endl;
					break;
				case WHILE: s = "while";break;
				case REPEAT:s = "repeat";break;
				case FOREACH:s = "foreach";break;
				case CLASS: s = "class";break;
				case EXTENDS: s = "extends";break;
				case IF: 
					s = "if";
					if_expression(p->opr.op[0]);
					break;
				case VAR: 
					s = "var";
					isvar = true;
					out << a.register_allo_n(p->opr.op[0]->id.s)<<endl;
				break;
				case ARRAY: s = "array";break;
				case RETURN:
				s = "return";
				out << a.ret<<"}"<<endl;
				break;
				case FUNCTION: s = "function";break;
				case PRINT:
					s = "print";
					a.print(p->opr.op[0]->id.s);
					break;
				case ';':s = "[;]";break;
				case ',':s = "[,]";break;
				case ASIGN:
					s = "[:=]";
					if(p->opr.op[1] -> type == typeCon)
						out << a.store(p->opr.op[0]->id.s,p->opr.op[1]->con.value) << endl;
					else if(p->opr.op[1] -> type == typeId)
						a.store_id(p->opr.op[1] -> id.s , p->opr.op[0] -> id.s);
					else
						assign_pre_order(p->opr.op[1]);
						//cout <<"^^^^^^^^^^^^^^^^^^"<<endl;
						//cout << mapstring["q"];
						//cout << stackint.top();
						if(stackint.size() == 1 && stacktype.top() == 1)
						{
							out << a.store(p->opr.op[0]->id.s,a.stringtonum(stackint.top())) << endl;
							stackint.pop();
							stacktype.pop();
						}
						//while(!stackint.empty())
						//{
					//		cout << stackint.top() << endl;
				//			cout << "type:" << stacktype.top() << endl;
					//		stacktype.pop();
					//		stackint.pop();
				//		}
						//cout <<"^^^^^^^^^^^^^^^^^^"<<endl;
					break;
				case ARRAYASIGN:s = "[:=]";break;
				case UMINUS:s = "[_]";break;
				case ENDIF: s = "endif";break;
				case ENDWHILE: s = "endwhile";break;
				case ENDFOR: s = "endforeach";break;
				case XIABIAO: s = "xiabiao";break;
				case '+':s = "[+]";break;
				case '-':s = "[-]";break;
				case '*':s = "[*]";break;
				case '/':s = "[/]";break;
				case '%':s = "[%]";break;
				case '<':s = "[<]";break;
				case '>':s = "[>]";break;
				case ELIF:s="elif";break;
				case ELSE:s="else";break;
				case GE:s = "[>=]";break;
				case LE:s = "[<=]";break;
				case NE:s = "[!=]";break;
				case EQ:s = "[==]";break;
				case AND:s = "[AND]";break;
				case OR :s = "[OR]";break;
			}
			printf(s);
			printf("\n");
			if(!isvar)
			for(int i=0;i<p->opr.nops;i++)
			{
				ppre_order(p->opr.op[i]);
			}
			break;
		}
	}

}