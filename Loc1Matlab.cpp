
int Loc1Matlab(char *argv[])
{

int type;
char FileName[200];
char str[400];
long int DiffLocation;
long int DiffValue;
long int Size;
int Nd=18;
int SetMaxDiff = exp2(Nd); //set max alphabet size
int Map[SetMaxDiff];
memset(Map,0,SetMaxDiff*sizeof(int));

strcpy(FileName, argv[1]);
strcat(FileName,"DiffLoc1");
FILE *fpReadDiff = fopen(FileName, "r");
if (fpReadDiff == NULL) {
   fprintf(stderr, "Can't open file %s!\n",FileName);
   exit(1);
}


strcpy(FileName, argv[1]);
strcat(FileName,"ExtPos");
FILE *fpWriteExtPos = fopen(FileName, "w");
if (fpWriteExtPos == NULL) {
   fprintf(stderr, "Can't open file %s!\n",FileName);
   exit(1);
}

strcpy(FileName, argv[1]);
strcat(FileName,"ExtNeg");
FILE *fpWriteExtNeg = fopen(FileName, "w");
if (fpWriteExtNeg == NULL) {
   fprintf(stderr, "Can't open file %s!\n",FileName);
   exit(1);
}

long int CountDiff;
int Diff;

 fgets(str,sizeof(str),fpReadDiff);
 long int i=0;
 while(!feof(fpReadDiff)) {
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
for(j=0;j<Size;++j){
	if(Map[j]>=0 && Map[j]<SetMaxDiff)
           Map_1[Map[j]] = j;
        else if (Map[j]>=0 && Map[j]>=SetMaxDiff)
           fprintf(fpWriteExtPos, "%ld ", 2*Map[j]-1);
	
        else if (Map[j]<0 && Map[j]<SetMaxDiff)
	   Map_2[-Map[j]] = j;
        else
           fprintf(fpWriteExtNeg, "%ld ", 2*(abs(Map[j])));


}

fclose(fpWriteExtPos);
fclose(fpWriteExtNeg);


strcpy(FileName, argv[1]);
strcat(FileName,"ExtPos");
FILE *fpReadExtPos = fopen(FileName, "r");
if (fpReadExtPos == NULL) {
   fprintf(stderr, "Can't open file %s!\n",FileName);
   exit(1);
}

strcpy(FileName, argv[1]);
strcat(FileName,"ExtNeg");
FILE *fpReadExtNeg = fopen(FileName, "r");
if (fpReadExtNeg == NULL) {
   fprintf(stderr, "Can't open file %s!\n",FileName);
   exit(1);
}



strcpy(FileName, argv[1]);
strcat(FileName,"DiffLocSeq1");
FILE *fpReadDiffSeq = fopen(FileName, "r");
if (fpReadDiffSeq == NULL) {
	fprintf(stderr, "Can't open file %s!\n",FileName);
        exit(1);}

strcpy(FileName, argv[1]);
strcat(FileName,"DiffLocSeqMatlab1");
FILE *fpWriteDiffSeqMatlab = fopen(FileName, "w");
if (fpWriteDiffSeqMatlab == NULL) {
	 fprintf(stderr, "Can't open file %s!\n",FileName);
         exit(1);}

 while(!feof(fpReadDiffSeq)){
	   fscanf(fpReadDiffSeq,"%d \n", &Diff);
	   if(Diff>=0 && Diff<SetMaxDiff )
		   fprintf(fpWriteDiffSeqMatlab, "%d ", Map_1[Diff]);
           else if (Diff>=0 && Diff>=SetMaxDiff){
                 fscanf(fpReadExtPos, "%ld ", &Diff);
                 fprintf(fpWriteDiffSeqMatlab, "%ld ", Diff);

               
            }      
	   else if(Diff<0 && Diff<SetMaxDiff)
		   fprintf(fpWriteDiffSeqMatlab, "%d ", Map_2[-Diff]);
          else{
            fscanf(fpReadExtNeg, "%ld ", &Diff);
            fprintf(fpWriteDiffSeqMatlab, "%ld ", Diff);


   }
 }

 fclose(fpWriteDiffSeqMatlab);
 fclose(fpReadDiffSeq);
 fclose(fpReadDiff);
fclose(fpReadExtPos);
fclose(fpReadExtNeg);

 return 1;
}