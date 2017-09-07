int DiffValSeq(char *argv[])
{
char FileName[400];
char str[400];
	strcpy(FileName, argv[1]);
	strcat(FileName, "DiffValSeqMatlabDecode");

	FILE *fpRead = fopen(FileName, "r");
	if (fpRead == NULL){
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

	strcpy(FileName, argv[1]);
	strcat(FileName, "DiffValSeq");

	FILE *fpWrite = fopen(FileName, "w");
	if (fpWrite == NULL){
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

	strcpy(FileName, argv[1]);
	strcat(FileName, "DiffVal");

	FILE *fpReadDiff = fopen(FileName, "r");
	if (fpReadDiff == NULL){
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

int Nd=18;
int SetMaxDiff = exp2(Nd); //set max alphabet size
int Map[SetMaxDiff];
	memset(Map,0,SetMaxDiff*sizeof(int));

long int CountDiff;
 long int Diff;

  fgets(str,sizeof(str),fpReadDiff);
   int i=0;
   while(!feof(fpReadDiff)){
	fscanf(fpReadDiff, "%ld %ld \n", &Diff, &CountDiff);
    Map[i]= Diff;
	++i;
   }

   fclose(fpReadDiff);

   while(!feof(fpRead)){
	   fscanf(fpRead, "%ld ", &Diff);
	   if (Diff>= SetMaxDiff)
	   printf("%ld\n", Diff);
	   else
	   fprintf(fpWrite, "%d ", Map[Diff]);
   }
   fclose(fpRead);
   fclose(fpWrite);

   	return 1;
}