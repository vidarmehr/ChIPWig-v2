
int GetChr(char * argv[])
{
	clock_t start = clock();
	SPAM(("=================\ngetseq.c start!\n"));


	char FileName[400];//name of processed Wig file
	long unsigned int Location=0;
	char tmp;
	char str[1000];  //annotation line
        char str2[40];
	double Value=0;
	long unsigned int IntValue=0;
	long unsigned int C1=0;
	long unsigned int C2=0;
        int i;

	strcpy(FileName, argv[1]);


	FILE *fp;
	fp = fopen(FileName, "r");
	if (fp == NULL) {
		fprintf(stderr, "Can't open input file %s!\n",FileName);
		exit(1);
	}
	strcpy(FileName, argv[2]);
	
	FILE *fpWrite;
	fpWrite = fopen(FileName, "w");
	if (fpWrite == NULL) {
		fprintf(stderr, "Can't open input file %s!\n",FileName);
		exit(1);
	}


int flag=0;
while (!feof(fp) &&flag==0){
     tmp = fgetc(fp);
     if  (tmp >= '0' && tmp <= '9'){
		ungetc(tmp,fp);
		fscanf(fp,"%lu %lf\n", &Location,&Value);
		//fprintf(fpWrite, "%lu %.2f\n", Location,Value);
    }
   else{
    	ungetc(tmp,fp);
	fgets(str,sizeof(str),fp);
        strcpy(str2,"variableStep chrom=chr2 span=25 \0");
        
        for(i=0;i<23;++i){
              if(str[i]!=str2[i]){
                 printf("%d, Length string wig=%d, Length string2=%d \n", i, strlen(str),strlen(str2));
                 flag=0;
                 break;}
}
        if(i==23){
            puts(str2);
            flag=1;}
         
       

   }
}
int flag2=0;
int ite=0;
while (!feof(fp) &&flag2==0 && ite<100){
     tmp = fgetc(fp);
     if  (tmp >= '0' && tmp <= '9'){
		ungetc(tmp,fp);
		fscanf(fp,"%lu %lf\n", &Location,&Value);
		fprintf(fpWrite, "%lu %.2f\n", Location,Value);
    }
   else{
	ungetc(tmp,fp);
        ++ite;
	fgets(str,sizeof(str),fp);
        for(i=0;i<23;++i){
              if(str[i]!=str2[i]){
                 printf("%d, Length string wig=%d, Length string2=%d \n", i, strlen(str),strlen(str2));
                 flag2=1;
                 break;
                 }

              }
          
	
   }
}

fclose(fp);
fclose(fpWrite);
return 1;
}
