#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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
	printf("출력합니다.\n");
	printf("<Cross-reference List>\n");
	printf("Symbol\tDefined\tUsed\n");
	printf("----------------------------------\n");
	if(st->startSymbol==NULL){
		printf("비엇습니다.\n");
	}
	Symbol *s = st->startSymbol;
	while(s!=NULL){
		printf("%s\t",s->symbol);
		printf("%d\t",s->defineLine);
		printf("%x\t",s->defineMemory);
		printf("%d\t",s->used);
		
		s = s->nextSymbol;
		printf("\n");
	}
}


