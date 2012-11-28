#include "sicasem.h"
int main(int argc,char *argv[]){
	printf("LAD ia %d \n",checkInst("LDA"));
	SIC sic;
	sic.startMemory=1000;
	printf("%d",sic.startMemory);
}