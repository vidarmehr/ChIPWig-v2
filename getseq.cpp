int getseq(char *argv[])
{
	char FileName[400];
	strcpy(FileName, argv[1]);
	strcat(FileName, "New");
	strcat(FileName,"DCoding2");

	int Nd=18;
    int SetMaxDiff = exp2(Nd);

	long int Location;
	long int Value;
	char str[400];
	FILE *fpRead = fopen(FileName, "r");
	if (fpRead == NULL)
	{
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}
	strcpy(FileName, argv[1]);
	strcat(FileName,"ExceedLoc");
	FILE *fpExceedLoc = fopen(FileName, "w+");
	if (fpExceedLoc == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

	strcpy(FileName, argv[1]);
	strcat(FileName,"ExceedVal");
	FILE *fpExceedVal = fopen(FileName, "w+");
	if (fpExceedVal == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}


	strcpy(FileName, argv[1]);
    strcat(FileName,"DiffLocSeq");
    FILE *fpWriteDiffLocSeq = fopen(FileName, "w");
	if (fpWriteDiffLocSeq == NULL)
	{
		fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
	}

    strcpy(FileName, argv[1]);
    strcat(FileName,"DiffValSeq");
    FILE *fpWriteDiffValSeq = fopen(FileName, "w");
	if (fpWriteDiffValSeq == NULL)
	{
		fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
	}
	fgets(str,sizeof(str),fpRead);
	while(!feof(fpRead))
	{
		fscanf(fpRead, "%ld %ld", &Location, &Value);

		if(mydiff(Location) == SetMaxDiff-1  && mydiff(Value) == SetMaxDiff-1)
		{
			fprintf(fpWriteDiffLocSeq, "%ld ",getdiff(SetMaxDiff-1));
			fprintf(fpExceedLoc, "%ld ", Location);
			fprintf(fpWriteDiffValSeq, "%ld ",getdiff(SetMaxDiff-1));
			fprintf(fpExceedVal, "%ld ", Value);
		}
		else if (mydiff(Location) == SetMaxDiff-2  && mydiff(Value) == SetMaxDiff-2)
		{

			fprintf(fpWriteDiffLocSeq, "%ld ",getdiff(SetMaxDiff-2));
			fprintf(fpExceedLoc, "%ld ", Location);
			fprintf(fpWriteDiffValSeq, "%ld ",getdiff(SetMaxDiff-2));
			fprintf(fpExceedVal, "%ld ", Value);
		}

		else if ((mydiff(Location)>=SetMaxDiff-3 && mydiff(Location)!= SetMaxDiff-1 && mydiff(Location)!= SetMaxDiff-2) || (mydiff(Value)>=SetMaxDiff-3 && mydiff(Value)!= SetMaxDiff-1 && mydiff(Value)!= SetMaxDiff-2 ))
		{
			if (mydiff(Location)>=SetMaxDiff-3 && mydiff(Location)!= SetMaxDiff-1 && mydiff(Location)!= SetMaxDiff-2)
			{
			   fprintf(fpWriteDiffLocSeq, "%ld ",getdiff(SetMaxDiff-3));
			   fprintf(fpExceedLoc, "%ld ", Location);
			}
			else
				fprintf(fpWriteDiffLocSeq,"%ld ",Location);

			if (mydiff(Value)>=SetMaxDiff-3 && mydiff(Value)!= SetMaxDiff-1 && mydiff(Value)!= SetMaxDiff-2)
			{
				fprintf(fpWriteDiffValSeq, "%ld ",getdiff(SetMaxDiff-3));
			    fprintf(fpExceedVal, "%ld ", Value);
			}
			else
				fprintf(fpWriteDiffValSeq,"%ld ",Value);

		}
		else
		{
			fprintf(fpWriteDiffLocSeq,"%ld ",Location);
			fprintf(fpWriteDiffValSeq,"%ld ",Value);
		}


		}

	fclose(fpRead);
	fclose(fpWriteDiffLocSeq);
	fclose(fpWriteDiffValSeq);
	fclose(fpExceedVal);
	fclose(fpExceedLoc);

    strcpy(FileName, argv[1]);
	strcat(FileName, "New");
	strcat(FileName,"DCoding2");
	remove(FileName);

	return 1;
}
