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
	char *label;
	char *inst;
	char *op1;
	char *op2;
	struct Linetype *nextLine;
}Line;

void sicInit(SIC *sic){
	sic->lineCount=0;
	sic->startMemory=0;
	sic->startLine=NULL;
	sic->endLine=NULL;
}

void lineAdd(SIC *sic,char *label,char *inst,char *op1,char *op2){
	Line *nl;
	nl=(Line *)malloc(sizeof(Line));
	if(nl==NULL) printf("full memory\n");
	if(sic->startLine==NULL){
		sic->startLine=nl;
		sic->startMemory=atoi(op1);
		nl->lineNumber=1;
	}
	if(sic->endLine!=NULL){
		sic->endLine->nextLine=nl;
	}
	sic->endLine=nl;
	sic->lineCount++;

	nl->nextLine=NULL;
	nl->label=label;
	nl->inst=inst;
	nl->op1=op1;
	nl->op2=op2;

}