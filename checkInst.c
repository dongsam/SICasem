//#include "sicasem.h"
//#include <string.h>
//#include <stdio.h>
//#include <unistd.h>
int checkInst(char *word ){
	
	char *instList[] = {"BASE","BYTE","RESW","RESB","END","START","ADD","ADDF","ADDR","AND","CLEAR","COMP","COMPF","COMPR","DIV","DIVF","DIVR","FIX","FLOAT","HIO","J","JEQ","JGT","JLT","JSUB","LDA","LDB","LDCH","LDF","LDL","LDS","LDT","LDX","LPS","MUL","MULF","MULR","NORM","OR","RD","RMO","RSUB","SHIFTL","SHIFTR","SIO","SSK","STA","STB","STCH","STF","STI","STL","STS","STSW","STT","STX","SUB","SUBF","SUBR","SVC","TD","TIO","TIX","TIXR","WD"};
	int i;
	int check=0;

	char newWord[10];

	int format4=0;
	int indirect=0;
	int immediate=0;

	if(word[0]=='@'){
		indirect=1;
		strcpy(newWord,word+1);
	}
	else if(word[0]=='+'){
		format4=1;
		strcpy(newWord,word+1);
	}
	else if(word[0]=='#'){
		immediate=1;
		strcpy(newWord,word+1);
	}else{
		strcpy(newWord,word);
	}

	for(i=0;i<65;i++){
		//printf("%s and %s is  %d \n" ,word,instList[i],strcmp(word,instList[i]));
		if(strcmp(newWord,instList[i])==0){
			check=1;
			//printf("find! %d \n",i);
		}
	}
	return check;
}

int checkInstFormat(char *word ){
	
	char *instList1[] = {"FIX","FLOAT","HIO","NORM","SIO","TIO"};
	char *instList2[] = {"ADDR","CLEAR","COMPR","DIVR","MULR","RMO","SHIFTL","SHIFTR","SUBR","SVC","TIXR"};
	char *instList34[] = {"ADD","ADDF","AND","COMP","COMPF","DIV","DIVF","J","JEQ","JGT","JLT","JSUB","LDA","LDB","LDCH","LDF","LDL","LDS","LDT","LDX","LPS","MUL","MULF","OR","RD","RSUB","SSK","STA","STB","STCH","STF","STI","STL","STS","STSW","STT","STX","SUB","SUBF","TD","TIX","WD"};
	char *instListAsem[] = {"BASE","BYTE","RESW","RESB","END","START"};
	int i;
	int check=-1;
	
	char newWord[10];

	int format4=0;
	int indirect=0;
	int immediate=0;

	if(word[0]=='@'){
		indirect=1;
		strcpy(newWord,word+1);
	}
	else if(word[0]=='+'){
		format4=1;
		strcpy(newWord,word+1);
	}
	else if(word[0]=='#'){
		immediate=1;
		strcpy(newWord,word+1);
	}else{
		strcpy(newWord,word+0);
	}

	//printf("~~~~~~~~~~~%s\n",newWord);

	
	for(i=0;i<6;i++){
		if(strcmp(newWord,instList1[i])==0){
			check=1;
		}
	}
	for(i=0;i<11;i++){
		if(strcmp(newWord,instList2[i])==0){
			check=2;
		}
	}
	for(i=0;i<42;i++){
		if(strcmp(newWord,instList34[i])==0){
			check=3;
		}
	}
	for(i=0;i<6;i++){
		if(strcmp(newWord,instListAsem[i])==0){
			check=0;
		}
	}

	if(format4==1){
		check=4;
	}
	
	return check;
}

