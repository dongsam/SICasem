#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>



char errorText[10000] = "\n-------------------------------\n \t <error List>\n-------------------------------\n";
char *toUpper(char *str);
char* itoa2(int val, int base);

typedef struct SICtype{
	int startMemory;
	int lineCount;
	int pc;
	int lastLocation;
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
	sic->lastLocation=0;
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
		

		
		if(!strcmp(toUpper(inst),"RESW")){
			nl->memorySize = 3*atoi(op1);
		}else if(!strcmp(toUpper(inst),"RESB")){
			nl->memorySize = atoi(op1);
		}else if(!strcmp(toUpper(inst),"BYTE")){
			
			if(op1[0]=='C'){
				nl->memorySize = strlen(op1)-3;
			}else if(op1[0]=='X'){
				nl->memorySize = (strlen(op1)-3)/2;
			}else{
				strcat(errorText,"BYTE inst error\n");
			}

		}else if(!strcmp(toUpper(inst),"WORD")){
			nl->memorySize = 3;
		}else{
			nl->memorySize = memorySize;
		}

		

		nl->memoryLocation = sic->pc;
		sic->lastLocation = nl->memoryLocation;
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
	
	

	//printf("추가됨  !%s! %s %s %s\n",label,inst,op1,comment);


	if(memorySize==-1){					// 잘못된 명령어 에러 처리 
		strcat(errorText,"Line : ");
		strcat(errorText,itoa2(line,10));
		strcat(errorText,"\t\"");
		strcat(errorText,inst);
		strcat(errorText,"\" 은 잘못된 명령어 입니다. 오타인지 체크해보세요.\n");
	}

}

void sicPrint(SIC *sic){
	//printf("출력합니다.\n");
	if(sic->startLine==NULL){
		//printf("비엇습니다.\n");
	}
	Line *l = sic->startLine;
	while(l!=NULL){
		if(0<strlen(l->comment)){			//주석 이면, 주석만출력
			printf("%-6d          ",l->lineNumber);
			printf("%s",l->comment);
		}else{
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
			
			
			
		}
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


	//printf("추가됨  %s  %d  %d  \n",symbol,defineLine,defineMemory);

}

void sybolTablePrint(SymbolTable *st){
	int i=0;
	printf("\n\n<Cross-reference List>\n");
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
	int existCheck=0;
	char tmpLine[10];
	if(st->startSymbol==NULL){
		printf("비엇습니다.3\n");
	}
	if(!strcmp(symbol,"X") || !strcmp(symbol,"F") || !strcmp(symbol,"P") || !strcmp(symbol,"C") || !strcmp(symbol,"A") || !strcmp(symbol,"S") || !strcmp(symbol,"C") ){
		//레지스터는 심볼체크 안해도됨,
		return;
	}

	Symbol *s = st->startSymbol;
	while(s!=NULL){
		if(!strcmp(s->symbol,symbol)){
			s->use[s->used++]=line;
			existCheck = 1;
		}

		s = s->nextSymbol;
	}
	if(existCheck==0){ // 해당 심볼이 심볼테이블에 등록이안된 심볼이면 에러처리
		//itoa(line,tmpLine,10)
		strcat(errorText,"Line : ");
		strcat(errorText,itoa2(line,10));
		strcat(errorText,"\t\"");
		strcat(errorText,symbol);
		strcat(errorText,"\" 은 정의되지 않은 symbol 입니다.\n");
	}
}

void symbolUsedCheck(SIC *sic,SymbolTable *st){
	//printf("//////////2pass symbol used check //////\n");
	char* filterdSym[10];
	if(sic->startLine==NULL){
		printf("비엇습니다.2\n");
	}
	Line *l = sic->startLine;
	while(l!=NULL){
		if(0<strlen(l->comment)){	// 주석이면 건너뛰기
			l = l->nextLine;
			continue;
		}
		strcpy(filterdSym,symbolFilter(l->op1));		// 심볼에 +,#,@ 기호 생략 필터링
		if(!checkConst(filterdSym) && !checkIndex(filterdSym)){		// 상수가아니고, 인덱스가 아닌 심볼들만,
			//printf("%d\t%s",l->lineNumber,filterdSym);
			sybolUse(st,filterdSym,l->lineNumber);
		}
		l = l->nextLine;
		//printf("\n");
	}
}


int getSymbolLocation(SymbolTable *st, char *symbol){
	int existCheck=0;
	if(st->startSymbol==NULL){
		printf("비엇습니다.3\n");
	}
	Symbol *s = st->startSymbol;
	while(s!=NULL){
		if(!strcmp(s->symbol,symbol)){
			existCheck = 1;
			return s->defineMemory;
		}
		s = s->nextSymbol;
	}
	return -1;
}





/////////////////2pass symbol used check///////////////////





///////////////// 3pass format4 check ///////////////////

void format4Check(SIC *sic,SymbolTable *st){
	char* filterdSym[10];
	if(sic->startLine==NULL){
		printf("비엇습니다.4\n");
	}
	Line *l = sic->startLine;
	int relative=0;

	while(l!=NULL){
		if(0<strlen(l->comment)){	// 주석이면 건너뛰기
			l = l->nextLine;
			continue;
		}
		strcpy(filterdSym,symbolFilter(l->op1));		// 심볼에 +,#,@ 기호 생략 필터링
		if(!checkConst(filterdSym) && !checkIndex(filterdSym)){		// 상수가아니고, 인덱스가 아닌 심볼들만,
			if(!strcmp(filterdSym,"X") || !strcmp(filterdSym,"F") || !strcmp(filterdSym,"P") || !strcmp(filterdSym,"C") || !strcmp(filterdSym,"A") || !strcmp(filterdSym,"S") || !strcmp(filterdSym,"C") ){
				l = l->nextLine;	//레지스터는 심볼체크 안해도됨,
				return;
			}
			
			if(l->inst[0]!='+'){
				//printf("%d\t%s   ",l->lineNumber,filterdSym);
				//printf("%d  -  %d\n",getSymbolLocation(st,filterdSym) , l->memoryLocation+l->memorySize ); 
				relative = getSymbolLocation(st,filterdSym) - l->memoryLocation+l->memorySize;
				if( 2047 < relative || relative  < -2048){
					strcat(errorText,"Line : ");
					strcat(errorText,itoa2(l->lineNumber,10));
					strcat(errorText,"\t\"");
					strcat(errorText,l->inst);
					strcat(errorText,"\" 은 PC-relative 의 범위를 초과하였습니다.  \n");
				}
			}

		}
		
		l = l->nextLine;
	}
}


///////////////// 3pass format4 check ///////////////////





char* itoa2(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
}

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

char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
}



