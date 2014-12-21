#include<stdio.h>
#include<string.h>
#include <sstream>
#include <fstream>
#include"main.h"
#include"yacc.tab.h"
#include <string>
using namespace std;
int del = 1;
int eps = 3;
ofstream out("out.txt"); 
class Code
{
	public:
		Code()
		{
			regi = 1;
			simicon = 0;
			ret = "ret i32 0";
			printtou = "@.str = private unnamed_addr constant [3 x i8] c\"%d\\00\", align 1";
			printdefine = "call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32 %";
			printdeclare = "declare i32 @printf(i8*, ...)";
		}
		string start = "define i32 @main() nounwind uwtable";
		int regi;
		int simicon;
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
		string store(char *s1 , int s2)
		{
			string s;
			string str1(s1);
			string str2 = numtostr(s2);
			s = "store i32 " + str2;
			s +=",i32* %" + str1 + ", align 4";
			return s;
		}
		string register_allo(int r) 
		{
    		 string s = numtostr(r);
    		 s = '%' + s;
    		 s += '=' + getallo;
    		 regi++;
			 return s;
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
void semanalysis(nodeType *p)
{
	ppre_order(p);
	out<< a.printdeclare << endl;
}

void ppre_order(nodeType *p)
{
	//::string b = "thisiszhou";
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
			//cout << a.globaldefine(3,s);
			//std::cout << a.register_allo(a.regi);
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
				case IF: s = "if";break;
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
				case ';':s = "[;]";a.simicon++;break;
				case ',':s = "[,]";break;
				case ASIGN:
					s = "[:=]";
					out << a.store(p->opr.op[0]->id.s,p->opr.op[1]->con.value) << endl;
					break;
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
			if(!isvar)
			for(int i=0;i<p->opr.nops;i++)
			{
				ppre_order(p->opr.op[i]);
			}
			break;
		}
	}

}