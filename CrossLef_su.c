void CrossLef(node date[],int index,FILE *cross){
	int i,j;
	char* cmp_symbol;
	printf("<Cross-reference List>\n");
	printf("Symbol\tDefined\tUsed\n");
	printf("--------------------\n");
	fprintf(cross,"Symbol\tDefined\tUsed\n");
	fprintf(cross,"--------------------\n");
	for( i = 0 ; i < index ; i++ ){
		cmp_symbol=strdup(date[i].symbol);
		if( strcmp(cmp_symbol," ") ){
			printf("%s\t%d\t",cmp_symbol,date[i].line);
			fprintf(cross,"%s\t%d\t",cmp_symbol,date[i].line);
			for( j = 0 ; j < index ; j++ ){
				if( !strcmp(date[j].date,cmp_symbol) ){
					printf("%d ",date[j].line);
					fprintf(cross,"%d ",date[j].line);
				}

			}
			printf("\n");
			fprintf(cross,"\n");
		}
		free(cmp_symbol);
	}

}
