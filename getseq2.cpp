int getseq2(char *argv[])
{

	char FileName[400];
	strcpy(FileName, argv[1]);
	strcat(FileName, "DiffLocRunLength");


	int Nd=18;
        int SetMaxDiff = exp2(Nd);

	long int Location;
	long int Value;
	char str[400];
	FILE *fpRead = fopen(FileName, "r");
	if (fpRead == NULL){
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

	strcpy(FileName, argv[1]);
        strcat(FileName,"DiffLocSeq1");
        FILE *fpWriteDiffLocSeq1 = fopen(FileName, "w");
	if (fpWriteDiffLocSeq1 == NULL){
		fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
	}

       strcpy(FileName, argv[1]);
       strcat(FileName,"DiffLocSeq2");
       FILE *fpWriteDiffLocSeq2 = fopen(FileName, "w");
	if (fpWriteDiffLocSeq2 == NULL){
		fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
	}
	//fgets(str,sizeof(str),fpRead);
	while(!feof(fpRead)){
		fscanf(fpRead,"%ld %ld\n", &Location, &Value);
		fprintf(fpWriteDiffLocSeq1,"%ld ",Location);
		fprintf(fpWriteDiffLocSeq2,"%ld ",Value);
	}

	fclose(fpRead);
	fclose(fpWriteDiffLocSeq1);
	fclose(fpWriteDiffLocSeq2);

	return 1;
}
