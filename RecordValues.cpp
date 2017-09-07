int RecordValues(char *argv[])
 {

        char FileName[400];//name of processed Wig file
	long unsigned int Location=0;
	int Coeff = 100;
	char tmp;
	char str[1000];  //annotation line
	unsigned long int Value=0;
	float Exp;
	unsigned int i;
	long int TotalNumbers=0;
	long unsigned int Max =0;
	int Min = 1000;
	int NumberofLargeValues=0;

	int Nd=20;
        unsigned int SetMaxDiff = exp2(Nd);
	unsigned int CountVal[SetMaxDiff]; //maps each consecutive integer to the actual alphabet
	memset(CountVal,0,SetMaxDiff*sizeof(int));

	strcpy(FileName, argv[1]);
	//strcat(FileName, "New");
	//strcat(FileName, "RoundVal");
	FILE *fp;
	fp = fopen(FileName, "r");
	if (fp == NULL) {
		fprintf(stderr, "Can't open input file %s!\n",FileName);
		exit(1);
	}

	strcpy(FileName, argv[1]);
	strcat(FileName, "RecordVal");
	FILE *fpWrite;
	fpWrite = fopen(FileName, "a");
	if (fpWrite == NULL) {
		fprintf(stderr, "Can't open input file %s!\n",FileName);
		exit(1);
	}

	strcpy(FileName, argv[1]);
	strcat(FileName, "Large");
	FILE *fpLarge;
	fpLarge = fopen(FileName, "w");
	if (fpLarge == NULL) {
		fprintf(stderr, "Can't open input file %s!\n",FileName);
		exit(1);
	}
	while (!feof(fp)){
		tmp = fgetc(fp);
		if  (tmp >= '0' && tmp <= '9'){
			ungetc(tmp,fp);
			fscanf(fp,"%lu %f\n", &Location,&Exp);
			Value = (unsigned long)(ceil)(1000.0 * Exp);
			Value = Value/10;
			if(Value>SetMaxDiff-1)
			{
				++TotalNumbers;
				fprintf(fpLarge,"%lu ", Value);
				++NumberofLargeValues;
			}
			else
			{
				++CountVal[Value];
				++TotalNumbers;
			}
			if(Value>Max)
			Max = Value;
			if(Value<Min)
			Min = Value;
		}
		else
		{
			ungetc(tmp,fp);
			fgets(str,sizeof(str),fp);
		}
}
fclose(fp);
fclose(fpLarge);
for(i=0;i<SetMaxDiff;++i)
{
	if(CountVal[i]>0)
	{
		fprintf(fpWrite,"%u %u %.8f\n", i, CountVal[i], CountVal[i]*(1.00)/TotalNumbers);
	}
}
fclose(fpWrite);
strcpy(FileName, argv[1]);
strcat(FileName, "Maximum");
FILE *fpWriteMax;
fpWriteMax = fopen(FileName, "w");
if (fpWriteMax == NULL) {
	fprintf(stderr, "Can't open input file %s!\n",FileName);
	exit(1);
}
fprintf(fpWriteMax,"Total numbers,\t Max of Values, \tMinimum of Values \n");
fprintf(fpWriteMax,"%ld %.3f %.3f ", TotalNumbers, Max *(1.0)/100, Min*(1.0)/100);
fclose(fpWriteMax);

 long unsigned int *matrix;
 matrix= (long unsigned int *)malloc(sizeof(long unsigned int)*NumberofLargeValues);
 long unsigned int Valu;
 strcpy(FileName, argv[1]);
strcat(FileName, "Large");
FILE *fpReadLarge;
fpReadLarge = fopen(FileName, "r");
if (fpReadLarge == NULL) {
     fprintf(stderr, "Can't open input file %s!\n",FileName);
      exit(1);
}

strcpy(FileName, argv[1]);
strcat(FileName, "RecordVal");
FILE *fpWrite2;
fpWrite2 = fopen(FileName, "a");
if (fpWrite2 == NULL) {
	fprintf(stderr, "Can't open input file %s!\n",FileName);
	exit(1);
}

i=0;
while(i<NumberofLargeValues & !feof(fpReadLarge)){
    fscanf(fpReadLarge, "%lu", &Valu);
    matrix[i]=Valu;
    ++i;
}
fclose(fpReadLarge);

int j;
long unsigned int b;
for(i=0;i<NumberofLargeValues;++i){
	if(matrix[i]!=0){
		j=i+1;
		while(j<NumberofLargeValues){
    		    if(matrix[i] > matrix[j]){
        		//printf("vaayyy");
        		b = matrix[i];
        		matrix[i] = matrix[j];
        		matrix[j]= b;
        	   }
        	   ++j;
		}
	}
}
//while(!feof(fpReadLarge))
//	{
	for(i=0;i<NumberofLargeValues;++i){
		//fscanf(fpReadLarge, "%lu ", &Valu);
		if(matrix[i] != 0)
		   fprintf(fpWrite2,"%lu %u %.8f\n", matrix[i], 1,(1.00)/TotalNumbers);
	  }
	fclose(fpWrite2);
//	fclose(fpReadLarge);

        strcpy(FileName, argv[1]);
	strcat(FileName, "Large");
	remove(FileName);

	 return 1;
}
