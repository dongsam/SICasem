#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


typedef struct SICtype{
	int startMemory;
	int lineCount;
	int pc;
	struct Linetype *startLine;
	struct Linetype *endLine;
}SIC;

typedef struct Linetype{
	int lineNumber;
	int memorySize;
	int memoryLocation;
	char label[20];
	char inst[20];
	char op1[20];
	char comment[20];
	struct Linetype *nextLine;
}Line;

void sicInit(SIC *sic){
	sic->lineCount=0;
	sic->startMemory=0;
	sic->pc=0;
	sic->startLine=NULL;
	sic->endLine=NULL;
}

void lineAdd(SIC *sic,int line,char *label,char *inst,char *op1,char *comment,int memorySize){
	Line *nl;
	nl=(Line *)malloc(sizeof(Line));
	if(nl==NULL) printf("full memory\n");
	if(sic->startLine==NULL){
		sic->startLine=nl;
		//sic->startMemory=atoi(op1);
		sic->startMemory=(int)strtol(op1, NULL, 16);
		nl->lineNumber=1;
		nl->memoryLocation = sic->startMemory;
		sic->pc= sic->startMemory;
	}else{
		nl->memorySize = memorySize;
		nl->memoryLocation = sic->pc;
		sic->pc = nl->memoryLocation + nl->memorySize;
	}
	if(sic->endLine==NULL){
		sic->endLine=nl;
	}
	else{
		sic->endLine->nextLine=nl;
		sic->endLine=nl;
	}
	
	sic->lineCount++;
	nl->nextLine=NULL;
	
	strcpy(nl->label,label);
	strcpy(nl->inst,inst);
	strcpy(nl->op1,op1);
	strcpy(nl->comment,comment);

	nl->lineNumber=line;
	
	

	printf("추가됨  !%s! %s %s %s\n",label,inst,op1,comment);


	

}

void sicPrint(SIC *sic){
	printf("출력합니다.\n");
	if(sic->startLine==NULL){
		printf("비엇습니다.\n");
	}
	Line *l = sic->startLine;
	while(l!=NULL){
		printf("%-6d",l->lineNumber);
		printf("%-10x",l->memoryLocation);
		if(strcmp(l->label,"")){
			printf("%-5s\t",l->label);
		}else{
			printf("\t");
		}
		printf("%s\t",l->inst);
		printf("%s\t",l->op1);
		printf("\t%d",l->memorySize);
		
		l = l->nextLine;
		printf("\n");
	}
}




/////////////////symbol table///////////////////

typedef struct symbolTableType{
	//int startMemory;
	int SymbolCount;
	struct Symboltype *startSymbol;
	struct Symboltype *endSymbol;
}SymbolTable;

typedef struct Symboltype{
	int defineMemory;
	int defineLine;
	int used;
	int use[100];
	char symbol[20];
	struct Symboltype *nextSymbol;
}Symbol;



void symbolTableInit(SymbolTable *symbolTable){
	symbolTable->SymbolCount=0;
	symbolTable->startSymbol=NULL;
	symbolTable->endSymbol=NULL;
}

void symbolAdd(SymbolTable *st,int defineLine,int defineMemory,char *symbol){
	Symbol *sb;
	sb=(Symbol *)malloc(sizeof(Symbol));
	if(sb==NULL) printf("full memory\n");
	if(st->startSymbol==NULL){
		st->startSymbol=sb;
	}
	if(st->endSymbol==NULL){
		st->endSymbol=sb;
	}
	else{
		st->endSymbol->nextSymbol=sb;
		st->endSymbol=sb;
	}
	
	sb->nextSymbol=NULL;
	
	strcpy(sb->symbol,symbol);
	sb->defineLine=defineLine;
	sb->defineMemory=defineMemory;
	sb->used=0;


	printf("추가됨  %s  %d  %d  \n",symbol,defineLine,defineMemory);

}

void sybolTablePrint(SymbolTable *st){
	int i=0;
	printf("<Cross-reference List>\n");
	printf("Symbol\tDefLine\tMemory\tUsed\n");
	printf("----------------------------------\n");
	if(st->startSymbol==NULL){
		printf("비엇습니다.\n");
	}
	Symbol *s = st->startSymbol;
	while(s!=NULL){
		
		printf("%s\t",s->symbol);
		printf("%d\t",s->defineLine);
		printf("%x\t",s->defineMemory);
		printf("%d번 --> ",s->used);
		for(i=0; i < s->used; i++){
			printf("%d ",s->use[i]);
		}
		
		s = s->nextSymbol;
		printf("\n");
	}
}

/////////////////symbol table///////////////////







/////////////////2pass symbol used check ///////////////////



char* symbolFilter(char *sym){
	char filterdSym[10];

	if(sym[0]=='@'){
		strcpy(filterdSym,sym+1);
	}
	else if(sym[0]=='+'){
		strcpy(filterdSym,sym+1);
	}
	else if(sym[0]=='#'){
		strcpy(filterdSym,sym+1);
	}else{
		strcpy(filterdSym,sym+0);
	}
	return filterdSym;
}



int checkConst(char *sym){
	if(sym[0] >='0' && '9' >= sym[0] ){
		return 1;
	}else{
		return 0;
	}
}

int checkIndex(char *sym){
	int len =strlen(sym);
	int check=0;
	while(len--){
		if(sym[len]==39) check=1;
	}
	return check;
}



void sybolUse(SymbolTable *st,char* symbol,int line){
	if(st->startSymbol==NULL){
		printf("비엇습니다.3\n");
	}
	Symbol *s = st->startSymbol;
	while(s!=NULL){
		if(!strcmp(s->symbol,symbol)){
			s->use[s->used++]=line;

			//printf("--- %s, %d  used",symbol,line);

		}

		s = s->nextSymbol;
	}
}

void symbolUsedCheck(SIC *sic,SymbolTable *st){
	printf("//////////2pass symbol used check //////\n");
	char* filterdSym[10];
	if(sic->startLine==NULL){
		printf("비엇습니다.2\n");
	}
	Line *l = sic->startLine;
	while(l!=NULL){

		strcpy(filterdSym,symbolFilter(l->op1));		// 심볼에 +,#,@ 기호 생략 필터링
		if(!checkConst(filterdSym) && !checkIndex(filterdSym)){		// 상수가아니고, 인덱스가 아닌 심볼들만,
			printf("%d\t%s",l->lineNumber,filterdSym);
			sybolUse(st,filterdSym,l->lineNumber);
		}
		l = l->nextLine;
		printf("\n");
	}
}



/////////////////2pass symbol used check///////////////////






char *toUpper(char *str){
    char *newstr, *p;
    p = newstr = strdup(str);
    while(*p++=toupper(*p));
    return newstr;
}


char *strClean(char *str){
	int len = strlen(str);
	int i=0;
	for(i=0;i<len;i++){
		str[i]='\0';
	}
	return str;
}