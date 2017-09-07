int CountLoc2(char *argv[])
{

int type;
char FileName[200];
char str[400];
long int DiffLocation;
long int DiffValue;

strcpy(FileName, argv[1]);
strcat(FileName, "DiffLocSeq2");
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

while(!feof(fpRead)){
	fscanf(fpRead,"%ld ", &DiffLocation);
	 ++Map[mydiff(DiffLocation)];
}

fclose(fpRead);

unsigned int i;

 strcpy(FileName, argv[1]);
 strcat(FileName,"DiffLoc2");
 FILE *fpWriteDiff = fopen(FileName, "w");
 if (fpWriteDiff == NULL) {
      fprintf(stderr, "Can't open file %s!\n",FileName);
       exit(1);
     }
 fprintf(fpWriteDiff, "Diff\t\t CountDiff\n");

for(i=0;i<SetMaxDiff;++i)
	if(Map[i] != 0)
	   fprintf(fpWriteDiff, "%ld %d \n", getdiff(i), Map[i]);

fclose(fpWriteDiff);

return 1;
}