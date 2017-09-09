 int RunLength(char *argv[])
 {
long  int Location=0;
long  int PreLocation=-1;
long unsigned int NumberOfLocations=0;
int Nd=18;
int SetMaxDiff = exp2(Nd); //set max alphabet size
char FileName[400];
strcpy(FileName, argv[1]);
strcat(FileName,"DiffLocSeq");
FILE *fpRead = fopen(FileName, "r");
if (fpRead == NULL){
		fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
}

strcpy(FileName, argv[1]);
strcat(FileName, "DiffLoc1Ext");
FILE *fpExt = fopen(FileName, "w");
if (fpExt == NULL) {
    fprintf(stderr, "Can't open file %s!\n",FileName);
    exit(1);
}


strcpy(FileName, argv[1]);
strcat(FileName,"DiffLocRunLength");
FILE *fpWrite = fopen(FileName, "w");
if (fpWrite == NULL){
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
while(!feof(fpRead)){
	fscanf(fpRead,"%ld\n", &Location);
	if(PreLocation == -1 ){
				//++NumberOfLocations;
				PreLocation = Location;
	}
	else{
		if(PreLocation == Location)
			++NumberOfLocations;
		else{
			++NumberOfLocations;
                        if( mydiff(NumberOfLocations) <= SetMaxDiff-3){
			    fprintf(fpWrite,"%lu \t %ld\n",  NumberOfLocations, PreLocation);
			    fprintf(fpWriteDiffLocSeq1,"%lu ",NumberOfLocations);
		            fprintf(fpWriteDiffLocSeq2,"%ld ",PreLocation);
                            }
                        else{
                            fprintf(fpWrite,"%lu \t %ld\n",  getdiff(SetMaxDiff-3), PreLocation);
			    fprintf(fpWriteDiffLocSeq1,"%lu ",getdiff(SetMaxDiff-3));
                            fprintf(fpExt,"%lu ",NumberOfLocations);
		            fprintf(fpWriteDiffLocSeq2,"%ld ",PreLocation);
                            }

			PreLocation = Location;
			NumberOfLocations = 0;
		}
	}

  }
++NumberOfLocations;
if( mydiff(NumberOfLocations) <= SetMaxDiff-3){
			    fprintf(fpWrite,"%lu \t %ld\n",  NumberOfLocations, PreLocation);
			    fprintf(fpWriteDiffLocSeq1,"%lu ",NumberOfLocations);
		            fprintf(fpWriteDiffLocSeq2,"%ld ",PreLocation);
                            }
                        else{
                            fprintf(fpWrite,"%lu \t %ld\n",  getdiff(SetMaxDiff-3), PreLocation);
			    fprintf(fpWriteDiffLocSeq1,"%lu ",getdiff(SetMaxDiff-3));
                            fprintf(fpExt,"%lu ",NumberOfLocations);
		            fprintf(fpWriteDiffLocSeq2,"%ld ",PreLocation);
                            }

//fprintf(fpWrite,"%lu \t %ld\n",  NumberOfLocations, PreLocation);
//fprintf(fpWriteDiffLocSeq1,"%lu ",NumberOfLocations);
//fprintf(fpWriteDiffLocSeq2,"%ld ",PreLocation);

fclose(fpRead);
fclose(fpWrite);
fclose(fpWriteDiffLocSeq1);
fclose(fpWriteDiffLocSeq2);
fclose(fpExt);


return 1;
 }
