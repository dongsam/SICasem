#include "sicasem.h"
int main(int argc,char *argv[]){
	if ( argc < 2 ) {
        printf("프로그램 인수로 소스 파일명을 입력하세요\n");
        return 0;
    }

    char buffer[512];

	printf("LAD ia %d \n",checkInst("LDA"));
	SIC sic;
	sicInit(&sic);

	//lineAdd(&sic,"sum","start","2000",NULL);

	printf("%d\n",sic.startMemory);
	printf("%d\n",sic.lineCount);	

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
		
		//while(tmpChar = fgetc(source)){
		//	if(tmpChar!='\n'){
				line++;
				printf("-----------\n");
				char tmpLabel[10]="";
				char tmpInst[10]="";
				char tmpOp1[10]="";
				char tmpOp2[10]="";
				i=0;
				strcpy(tmpWord,"");
				while(tmpChar = fgetc(source)){
					if(tmpChar!='\n' && !feof(source) ){
						if(tmpChar!='\0' && tmpChar!=' ' && tmpChar!='\t'){
							printf("%c 1\n",tmpChar);
							tmpWord[i++]=tmpChar;
						}else{
							tmpWord[i++]='\0';
							break;
						}
					}else break;
				}
				if(checkInst(tmpWord)){
					strcpy(tmpInst,tmpWord);
				}else{
					strcpy(tmpLabel,tmpWord);
				}

				i=0;
				strcpy(tmpWord,"");
				while(tmpChar = fgetc(source)){
					if(tmpChar!='\n' && !feof(source)){
						if(tmpChar!='\0' && tmpChar!=' ' && tmpChar!='\t'){
							printf("%c 2\n",tmpChar);
							tmpWord[i++]=tmpChar;
						}else{
							tmpWord[i++]='\0';
							break;
						}
					}else break;
				}
				if(strlen(tmpInst)<1){
					strcpy(tmpInst,tmpWord);
				}else{
					strcpy(tmpOp1,tmpWord);
				}

				i=0;
				strcpy(tmpWord,"");
				while(tmpChar = fgetc(source)){
					if(tmpChar!='\n' && !feof(source)){
						if(tmpChar!='\0' && tmpChar!=' ' && tmpChar!='\t'){
							printf("%c 3\n",tmpChar);
							tmpWord[i++]=tmpChar;
						}else{
							tmpWord[i++]='\0';
							break;
						}
					}else break;
				}
				if(strlen(tmpOp1)<1){
					strcpy(tmpOp1,tmpWord);
				}else{
					strcpy(tmpOp2,tmpWord);
				}
				
				printf("label %s  inst %s  op1 %s op2 %s\n",tmpLabel,tmpInst,tmpOp1,tmpOp2);
				lineAdd(&sic,line,tmpLabel,tmpInst,tmpOp1,tmpOp2);

		//	}
		//}
		//tmpChar = fgetc(source);


	}
	sicPrint(&sic);
	


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
}