#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int instList();

typedef struct SICtype{
	int startMemory;
	int lineCount;
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
	char op2[20];
	struct Linetype *nextLine;
}Line;

void sicInit(SIC *sic){
	sic->lineCount=0;
	sic->startMemory=0;
	sic->startLine=NULL;
	sic->endLine=NULL;
}

void lineAdd(SIC *sic,int line,char *label,char *inst,char *op1,char *op2){
	Line *nl;
	nl=(Line *)malloc(sizeof(Line));
	if(nl==NULL) printf("full memory\n");
	if(sic->startLine==NULL){
		sic->startLine=nl;
		sic->startMemory=atoi(op1);
		nl->lineNumber=1;
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
	strcpy(nl->op2,op2);

	nl->lineNumber=line;

	printf("추가됨  !%s! %s %s %s\n",label,inst,op1,op2);

}

void sicPrint(SIC *sic){
	printf("출력합니다.\n");
	if(sic->startLine==NULL){
		printf("비엇습니다.\n");
	}
	Line *l = sic->startLine;
	while(l!=NULL){
		printf("%-5d",l->lineNumber);
		if(strcmp(l->label,"")){
			printf("%s\t",l->label);
		}else{
			printf("\t\t");
		}
		printf("%s\t",l->inst);
		printf("%s\t",l->op1);
		
		l = l->nextLine;
		printf("\n");
	}
}