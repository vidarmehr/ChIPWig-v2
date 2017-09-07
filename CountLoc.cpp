int CountLoc(char *argv[])
{

	int type;
	char FileName[200];
	char str[400];
	long int DiffLocation;
	long int DiffValue;

	strcpy(FileName, argv[1]);
	strcpy(FileName, argv[1]);
	strcat(FileName, "DiffLocSeq");
	FILE *fpRead = fopen(FileName, "r");
	if (fpRead == NULL) {
		 fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
	}

long int Size;
int Nd=18;
int SetMaxDiff = exp2(Nd); //set max alphabet size
int Map[SetMaxDiff];
	memset(Map,0,SetMaxDiff*sizeof(int));

long int Diff;

while(!feof(fpRead))
{
	fscanf(fpRead,"%ld ", &DiffLocation);
	 ++Map[mydiff(DiffLocation)];

}
Map[SetMaxDiff-1] = 1;
Map[SetMaxDiff-2] = 1;
fclose(fpRead);


long int i;

   strcpy(FileName, argv[1]);
   strcat(FileName,"DiffLoc");
    FILE *fpWriteDiff = fopen(FileName, "w");
    if (fpWriteDiff == NULL) {
      fprintf(stderr, "Can't open file %s!\n",FileName);
       exit(1);
     }


	for(i=0;i<SetMaxDiff;++i)
	  if(Map[i] != 0)
		fprintf(fpWriteDiff, "%d %ld \n", getdiff(i), Map[i]);

fclose(fpWriteDiff);

strcpy(FileName, argv[1]);
strcat(FileName,"DiffLoc");
 FILE *fpReadDiff = fopen(FileName, "r");
if (fpReadDiff == NULL) {
   fprintf(stderr, "Can't open file %s!\n",FileName);
   exit(1);
}


long int CountDiff;

  i=0;
   while(!feof(fpReadDiff))
   {
	fscanf(fpReadDiff, "%d %ld \n", &Diff, &CountDiff);
    Map[i]= Diff;
	++i;
   }
   Size = i;


int Map_1[SetMaxDiff];
	memset(Map_1,0,SetMaxDiff*sizeof(int));

 int Map_2[SetMaxDiff];
	memset(Map_2,0,SetMaxDiff*sizeof(int));

	long int j;
for(j=0;j<Size;++j)
{
	if(Map[j]>=0)

       Map_1[Map[j]] = j;
	else
	   Map_2[-Map[j]] = j;
}

			strcpy(FileName, argv[1]);
			strcat(FileName,"DiffLocSeq");
            FILE *fpReadDiffSeq = fopen(FileName, "r");
			if (fpReadDiffSeq == NULL) {
		       fprintf(stderr, "Can't open file %s!\n",FileName);
		       exit(1);}


         	strcpy(FileName, argv[1]);
			strcat(FileName,"DiffLocSeqMatlab");
            FILE *fpWriteDiffSeqMatlab = fopen(FileName, "w");
			if (fpWriteDiffSeqMatlab == NULL) {
		       fprintf(stderr, "Can't open file %s!\n",FileName);
		       exit(1);}


   while(!feof(fpReadDiffSeq))
   {
	   fscanf(fpReadDiffSeq,"%ld \n", &Diff);
	   if(Diff>=0 )
		   fprintf(fpWriteDiffSeqMatlab, "%ld ", Map_1[Diff]);
	   else if(Diff<0 )
		   fprintf(fpWriteDiffSeqMatlab, "%ld ", Map_2[-Diff]);
   }

   fclose(fpWriteDiffSeqMatlab);
   fclose(fpReadDiffSeq);
   fclose(fpReadDiff);

	return 1;
}