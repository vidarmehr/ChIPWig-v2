int CountLoc1(char *argv[])
{

int type;
char FileName[200];
char str[400];
long int DiffLocation,c;
long int DiffValue;

strcpy(FileName, argv[1]);
strcat(FileName, "DiffLocSeq1");
FILE *fpRead = fopen(FileName, "r");
if (fpRead == NULL) {
		 fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
	}

//strcpy(FileName, argv[1]);
//strcat(FileName, "DiffLoc1Ext");
//FILE *fpExt = fopen(FileName, "w");
//if (fpExt == NULL) {
  //  fprintf(stderr, "Can't open file %s!\n",FileName);
    //exit(1);
//}
long int Size;
int Nd=18;
int SetMaxDiff = exp2(Nd); //set max alphabet size
int Map[SetMaxDiff];
memset(Map,0,SetMaxDiff*sizeof(int));
int Diff;

while(!feof(fpRead)){
	fscanf(fpRead,"%ld ", &DiffLocation);
        // printf("%ld ", DiffLocation);
           if (mydiff(DiffLocation) <= SetMaxDiff-3)
	     ++Map[mydiff(DiffLocation)];
           else{
              printf("Largeeee");
printf("%d %ld ",mydiff(DiffLocation) , DiffLocation);
             // ++Map[SetMaxDiff-1];
              //fprintf(fpExt, "%ld ", DiffLocation);
           }

}

fclose(fpRead);
//fclose(fpExt);

/*strcpy(FileName, argv[1]);
strcat(FileName, "DiffLoc1Ext");
FILE *fpReadExt = fopen(FileName, "r");
if (fpReadExt == NULL) {
    fprintf(stderr, "Can't open file %s!\n",FileName);
    exit(1);
}

long int NumberOfExt = 0;
while(!feof(fpReadExt)){
 fscanf(fpReadExt, "%ld ", &DiffLocation);
 ++NumberOfExt;
}
printf("%d", NumberOfExt);

unsigned int j,i=0;
long int *ExtVal;
ExtVal= (long int *)malloc(sizeof(long int)*NumberOfExt);
fseek(fpReadExt, 0L, SEEK_SET);
while(!feof(fpReadExt)){
fscanf(fpReadExt, "%ld ", &DiffLocation);
//printf("%ld ",DiffLocation );
ExtVal[i++] = DiffLocation;
printf(" %ld ",ExtVal[i-1] );
}

fclose(fpReadExt);
for(i=0;i<NumberOfExt-1;++i){
    for(j=i+1;j<NumberOfExt;++j){
       if(ExtVal[i]>ExtVal[j]){
          c = ExtVal[i];
          ExtVal[i] = ExtVal[j];
          ExtVal[j] = c;
       }
  }
}
for(i=0;i<NumberOfExt;++i){
printf("\n%ld", ExtVal[i]);
}*/

strcpy(FileName, argv[1]);
strcat(FileName,"DiffLoc1");
FILE *fpWriteDiff = fopen(FileName, "w");
 if (fpWriteDiff == NULL) {
      fprintf(stderr, "Can't open file %s!\n",FileName);
       exit(1);
     }
fprintf(fpWriteDiff, "Diff\t\t CountDiff\n");

for(int i=0;i<SetMaxDiff;++i)
	if(Map[i] != 0)
		fprintf(fpWriteDiff, "%ld %d \n", getdiff(i), Map[i]);

/*long int Count, Count2;
while(i<NumberOfExt){
   Count = 1;
   Count2 = 0;
   for(j=i+1;j< NumberOfExt;++j){
      if(ExtVal[i] == ExtVal[j]){
        ++Count2;
        ++Count;
      }
   i = i + Count2;
   }
   fprintf(fpWriteDiff, "%ld %ld \n", ExtVal[i], Count);
       
}*/
    


fclose(fpWriteDiff);

return 1;
}