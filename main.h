
#include <iostream>//ʹ��C++��
#include <string>
#include <stdio.h>//printf��FILEҪ�õ�
using namespace std;
enum nodeEnum{typeCon,typeId,typeOpr} ;
struct conNodeType{
	int value;
};
struct idNodeType{
	int i;
	char *s;
};
struct oprNodeType{
	int oper;
	int nops;
	struct nodeType *op[1];
};
struct nodeType{
	nodeEnum type;
	union{
		struct conNodeType con;
		struct idNodeType id;
		struct oprNodeType opr;
	};
};
extern int symi[1000];
extern int symb[1000];
/*��lexÿʶ���һ���Ǻź���ͨ������yylval��yacc�������ݵġ�Ĭ�������yylval��int���ͣ�Ҳ����ֻ�ܴ����������ݡ�
yylval����YYSTYPE�궨��ģ�ֻҪ�ض���YYSTYPE�꣬��������ָ��yylval������(�ɲμ�yacc�Զ����ɵ�ͷ�ļ�yacc.tab.h)��
�����ǵ��������ʶ�����ʶ����Ҫ��yacc���������ʶ������yylval��������Ͳ�̫����(Ҫ��ǿ��ת�������ͣ�yacc����ת����char*)��
�����YYSTYPE�ض���Ϊstruct Type���ɴ�Ŷ�����Ϣ*/
/*struct Type//ͨ��������ÿ����Ա��ÿ��ֻ��ʹ������һ����һ���Ƕ����union�Խ�ʡ�ռ�(����������string�ȸ���������ɲ�����)
{
	string m_sId;
	int m_nInt;
	char m_cOp;
};
*/
struct Type{
	int iValue;
	char *sIndex;
	nodeType *nPtr;
};
#define YYSTYPE Type//��YYSTYPE(��yylval����)�ض���Ϊstruct Type���ͣ�����lex������yacc���ظ����������
