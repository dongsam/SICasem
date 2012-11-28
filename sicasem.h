#include <stdio.h>
#include <unistd.h>
#include <string.h>

int instList();

typedef struct{
	int startMemory;
	int lineCount;
	struct line *startLine;
	struct line *endLine;
}SIC;

typedef struct{
	int lineNumber;
	int memorySize;
	int memoryLocation;
	char *label;
	char *Inst;
	char *op1;
	char *op2;
	struct line *nextLine;
}Line;