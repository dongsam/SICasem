#include "sicasem.h"
//#include <string.h>
//#include <stdio.h>
//#include <unistd.h>
int checkInst(char *word ){
	char *instList[] = {"ADD","ADDF","ADDR","AND","CLEAR","COMP","COMPF","COMPR","DIV","DIVF","DIVR","FIX","FLOAT","HIO","J","JEQ","JGT","JLT","JSUB","LDA","LDB","LDCH","LDF","LDL","LDS","LDT","LDX","LPS","MUL","MULF","MULR","NORM","OR","RD","RMO","RSUB","SHIFTL","SHIFTR","SIO","SSK","STA","STB","STCH","STF","STI","STL","STS","STSW","STT","STX","SUB","SUBF","SUBR","SVC","TD","TIO","TIX","TIXR","WD"};
	int i;
	int check=0;
	for(i=0;i<59;i++){
		//printf("%s and %s is  %d \n" ,word,instList[i],strcmp(word,instList[i]));
		if(strcmp(word,instList[i])==0){
			check=1;
			//printf("find! %d \n",i);
		}
	}
	return check;
}
//int main(void){
//	printf("add %d\n",checkInst("add"));
//	printf("WD %d\n",checkInst("WD"));
//	return 0;
//}
