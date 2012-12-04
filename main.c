#include "sicasem.h"
//main++

int main(int argc,char *argv[]){
	if ( argc < 2 ) {
        printf("프로그램 인수로 소스 파일명을 입력하세요\n");
        return 0;
    }

    char buffer[512];

	checkInstFormat("+add");

	SIC sic;
	sicInit(&sic);

	SymbolTable symbolTable;
	symbolTableInit(&symbolTable);


	//lineAdd(&sic,"sum","start","2000",NULL);


	FILE *source;
	source = fopen(argv[1],"r");

	
	char tmpWord[100];
	char tmpChar;
	int line=0;
	int i=0;

/*
	if(tmpChar = fgetc(source)){
		if(tmpChar!='\n'){
			printf("%c",tmpChar);	
		}
	}
*/	
	

	while( !feof(source)){
		
		
			//if(tmpChar!='\n'){
				
				printf("-----------\n");
				char tmpLabel[10]="";
				char tmpInst[10]="";
				char tmpOp1[10]="";
				char tmpComment[150]="";
				int memorySize=0;
				i=0;
				strClean(tmpWord);
				int firstCheck=0;
				int noLabelCheck=0;

				while(tmpChar = fgetc(source)){
					if(firstCheck==0 && (tmpChar==' ' || tmpChar=='\t' )){
						noLabelCheck=1;
						break;
					}
					firstCheck=1;
					if(tmpChar!='\n' && !feof(source) ){
						if(tmpChar!='\0' && tmpChar!=' ' && tmpChar!='\t'){
							printf("%c 1\n",tmpChar);
							tmpWord[i++]=tmpChar;
						}else{
							if(i==0){
								continue;
							}
							else{
								tmpWord[i++]='\0';
								break;
							}
						}
					}else break;
				}
				if(checkInst(toUpper(tmpWord))){
					strcpy(tmpInst,tmpWord);
				}else{
					if(noLabelCheck==0){
						strcpy(tmpLabel,tmpWord);
					}
					//추가
					i=0;
					strClean(tmpWord);
					while(tmpChar = fgetc(source)){
						if(tmpChar!='\n' && !feof(source)){
							if(tmpChar!='\0' && tmpChar!=' ' && tmpChar!='\t'){
								printf("%c 2\n",tmpChar);
								tmpWord[i++]=tmpChar;
							}else{
								if(i==0){
									continue;
								}
								else{
									tmpWord[i++]='\0';
									break;
								}
							}
						}else break;
					}
					if(!strcmp(tmpInst,"")){
						strcpy(tmpInst,tmpWord);
					}else{
						strcpy(tmpOp1,tmpWord);
					}	
					//추가
				}

				

				i=0;
				strClean(tmpWord);
				while(tmpChar = fgetc(source)){
					if(tmpChar!='\n' && !feof(source)){
						if(tmpChar!='\0' && tmpChar!=' ' && tmpChar!='\t'){
							printf("%c 3\n",tmpChar);
							tmpWord[i++]=tmpChar;
						}else{
							if(i==0){
								continue;
							}
							else{
								tmpWord[i++]='\0';
								break;
							}
						}
					}else break;
				}
				if(strlen(tmpOp1)<1){
					strcpy(tmpOp1,tmpWord);
				}
				if(1<=strlen(tmpInst)){
					line=line+1;
					printf("label %s  inst %s  op1 %s comment %s\n",tmpLabel,tmpInst,tmpOp1,tmpComment);
					memorySize=checkInstFormat(toUpper(tmpInst));
					lineAdd(&sic,line,tmpLabel,tmpInst,tmpOp1,tmpComment,memorySize);
				}
				if(1<strlen(tmpLabel)){
					printf("라벨있음 %s \n",tmpLabel);
					symbolAdd(&symbolTable,line,sic.pc-memorySize,tmpLabel);
				}	
		//	}
		//}
		//tmpChar = fgetc(source);


	}
	sicPrint(&sic);
	//sybolTablePrint(&symbolTable);
	


	//char *tmp;
	//fscanf(source,"%s\n",tmp);
	//printf("%s",tmp);


/*
	while ( feof(source) != EOF )
    {
        if ( fgets(buffer, 512, source) == NULL ) break;  
        printf("%s", buffer);
    }
*/




    symbolUsedCheck(&sic,&symbolTable);
    sybolTablePrint(&symbolTable);
    printf("%s",errorText);
}