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