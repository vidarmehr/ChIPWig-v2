int merge(char *argv[])
{

	char FileName[400];//name of processed Wig file 1
	strcpy(FileName, argv[1]);
	strcat(FileName, "DiffLocSeqDe_RunLength");
	FILE *fpRead = fopen(FileName, "r");
	if (fpRead == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

	strcpy(FileName, argv[1]);
	strcat(FileName, "DiffValSeq");
	FILE *fpRead2 = fopen(FileName, "r");
	if (fpRead2 == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}
	strcpy(FileName, argv[1]);
	strcat(FileName, "DCoding2");
	FILE *fpWrite = fopen(FileName, "w");
	if (fpWrite == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

	long int Diff1;
	long int Diff2;
	while(!feof(fpRead)&& !feof(fpRead2)){
		fscanf(fpRead, "%ld ", &Diff1);
		fscanf(fpRead2, "%ld ", &Diff2);
		fprintf(fpWrite, "%ld %ld \n", Diff1, Diff2);
	}

	while(!feof(fpRead)){
		fscanf(fpRead,"%ld ", &Diff1);
		printf("error");
	}
	while(!feof(fpRead2)){
		fscanf(fpRead2,"%ld ", &Diff2);
		printf("error");
	}

fclose(fpRead);
fclose(fpRead2);
fclose(fpWrite);

	return 1;
}