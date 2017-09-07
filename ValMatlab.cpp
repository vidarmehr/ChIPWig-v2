int ValMatlab(char *argv[])
{
	int type;
	char FileName[200];
	char str[200];
	long int DiffLocation;
	long int DiffValue;
        int Nd=18;
        int SetMaxDiff = exp2(Nd); //set max alphabet size
        int Map[SetMaxDiff];
	memset(Map,0,SetMaxDiff*sizeof(int));
        int Diff;
        strcpy(FileName, argv[1]);
        strcat(FileName,"DiffVal");
        FILE *fpReadDiff = fopen(FileName, "r");
        if (fpReadDiff == NULL) {
            fprintf(stderr, "Can't open file %s!\n",FileName);
             exit(1);
         }

         long int CountDiff;
         long int i=0;
         fgets(str,sizeof(str),fpReadDiff);
         while(!feof(fpReadDiff)) {
	     fscanf(fpReadDiff, "%d %ld \n", &Diff, &CountDiff);
             Map[i]= Diff;
	  //printf("%d ",Map[i]);
	     ++i;
         }
         long int Size = i;

         int Map_1[SetMaxDiff];
	 memset(Map_1,0,SetMaxDiff*sizeof(int));

         int Map_2[SetMaxDiff];
	 memset(Map_2,0,SetMaxDiff*sizeof(int));

         long int j;
         for(j=0;j<Size;++j){
	    if(Map[j]>=0)
               Map_1[Map[j]] = j;
	    else
	      Map_2[-Map[j]] = j;
         }

	strcpy(FileName, argv[1]);
	strcat(FileName,"DiffValSeq");
        FILE *fpReadDiffSeq = fopen(FileName, "r");
	if (fpReadDiffSeq == NULL) {
		 fprintf(stderr, "Can't open file %s!\n",FileName);
		  exit(1);}


      strcpy(FileName, argv[1]);
      strcat(FileName,"DiffValSeqMatlab");
      FILE *fpWriteDiffSeqMatlab = fopen(FileName, "w");
       if (fpWriteDiffSeqMatlab == NULL) {
		  fprintf(stderr, "Can't open file %s!\n",FileName);
		   exit(1);}


   while(!feof(fpReadDiffSeq)){
	   fscanf(fpReadDiffSeq,"%d \n", &Diff);
	   if(Diff>=0)
		   fprintf(fpWriteDiffSeqMatlab, "%d ", Map_1[Diff]);
	   else if(Diff<0 )
		   fprintf(fpWriteDiffSeqMatlab, "%d ", Map_2[-Diff]);
   }

   fclose(fpWriteDiffSeqMatlab);
   fclose(fpReadDiffSeq);
   fclose(fpReadDiff);

return 1;
}
