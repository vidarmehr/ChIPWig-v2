int De_RunLength(char *argv[])
 {
long int L1=0;
long int L2=0;
long int i;
int Nd=18;
int SetMaxDiff = exp2(Nd);


char FileName[400];
strcpy(FileName, argv[1]);
strcat(FileName,"DiffLocSeq1");
FILE *fpRead1 = fopen(FileName, "r");
if (fpRead1 == NULL){
		fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
}

strcpy(FileName, argv[1]);
strcat(FileName,"DiffLocSeq2");
FILE *fpRead2 = fopen(FileName, "r");
if (fpRead2 == NULL){
		fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
}

strcpy(FileName, argv[1]);
strcat(FileName,"DiffLocSeqDe_RunLength");
FILE *fpWrite = fopen(FileName, "w");
if (fpWrite == NULL){
	fprintf(stderr, "Can't open file %s!\n",FileName);
	 exit(1);
}

strcpy(FileName, argv[1]);
strcat(FileName,"DiffLoc1Ext");
FILE *fpLoc1Ext = fopen(FileName, "r");
if (fpLoc1Ext == NULL){
	fprintf(stderr, "Can't open file %s!\n",FileName);
	 exit(1);
}

while(!feof(fpRead1) && !feof(fpRead2)){
	   fscanf(fpRead1,"%ld ", &L1);
           if(L1 == getdiff(SetMaxDiff-3))
               fscanf(fpLoc1Ext, "%ld ", &L1);
	   fscanf(fpRead2,"%ld ", &L2);
	   for(i=0;i<L1;++i)
		   fprintf(fpWrite,"%ld ", L2);

   }

while(!feof(fpRead1)){
   fscanf(fpRead1,"%ld ", &L1);
   printf("%ld ", L1);
	printf("error");
}
while(!feof(fpRead2)){
   fscanf(fpRead2,"%ld ", &L2);
   printf("%ld ", L2);
	printf("error");
}

fclose(fpRead1);
fclose(fpRead2);
fclose(fpWrite);
fclose(fpLoc1Ext);

return 1;
 }
