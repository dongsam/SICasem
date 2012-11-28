#include "sicasem.h"
int main(int argc,char *argv[]){
	printf("LAD ia %d \n",checkInst("LDA"));
	SIC sic;
	sicInit(&sic);

	lineAdd(&sic,"sum","start","2000",NULL);

	printf("%d\n",sic.startMemory);
	printf("%d\n",sic.lineCount);	
	
}