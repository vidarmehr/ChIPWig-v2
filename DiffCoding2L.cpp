int DiffCoding2L (char *argv[])
{

	char tmp;
	char str[200];
	char str2[200];
    char tmpFileName[400];
    fpos_t position;
    long  unsigned int Location=0;
    long unsigned int Exp=0;
	int flag=0;
    long unsigned int PreLocation = 0;
	char Prestr[200];
	strcpy(Prestr,"empty");
	long unsigned int PreExp = 0;
	int Nd=18;
    int SetMaxDiff = exp2(Nd);
	int ChrmCount=0;
	int j;
	int k;

	char ChrmNames[8*32];
	memset(ChrmNames,0,8*32*sizeof(char));
	char *tmpChrmName;

	char SpanNames[8*32];
	memset(SpanNames,0,8*32*sizeof(char));
	char *tmpSpanName;

	char FileName[400];
	strcpy(FileName, argv[1]);
	strcat(FileName, "New");
	//strcat(FileName,"DCoding");

	FILE *fpRead = fopen(FileName, "r");
	if (fpRead == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

	strcpy(FileName, argv[1]);
	strcat(FileName, "New");
	strcat(FileName,"DCoding2");
	FILE *fpWrite = fopen(FileName, "w");
	if (fpWrite == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}
	strcpy(FileName, argv[1]);
	strcat(FileName, "NonZeroDiff");
	FILE *fpWriteNonZero = fopen(FileName, "w");
	if (fpWriteNonZero == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

    long int Peak = 1000000;
    long int M = 0;
    long int Min_Peak = 1000000;
    long int Max_Peak = 0;
	fprintf(fpWrite,"DiffLocation\tDiffValue\n");

	while (!feof(fpRead))
	{
		tmp = fgetc(fpRead);
		if  (tmp >= '0' && tmp <= '9')
		{
			ungetc(tmp,fpRead);
			//fscanf(fpRead,"%ld %ld\n", &Location,&Exp);
	        fscanf(fpRead,"%lu %lu\n", &Location,&Exp);
			fprintf(fpWrite, "%ld \t %ld\n", Location-PreLocation, Exp-PreExp);
			if((Exp-PreExp) != 0){
				fprintf(fpWriteNonZero, "%ld \n ", Exp-PreExp );}
			/*if(PreExp != 0)
			{
				if(M>0 && Exp-PreExp<0)
                  if(M < abs(Exp-PreExp))
                    Peak = M;
				  else
				    Peak = abs(Exp-PreExp);

				if(Peak<Min_Peak)
				  Min_Peak = Peak;
			}
			else
			{
			   M = Exp - PreExp;
			   Min_Peak = 10000000;
		   }
		    if((Exp - PreExp) != 0)
		      M = Exp - PreExp;*/
		    PreLocation = Location;
		    PreExp = Exp;
		}
		else
		{
			ungetc(tmp,fpRead);
		    fgets(str,sizeof(str),fpRead);
	        if(strcmp(Prestr, str)==0)
			{
	            strcpy(Prestr,str);
				fprintf(fpWrite, "%ld \t %ld\n", getdiff(SetMaxDiff-2) , getdiff(SetMaxDiff-2));
			}

			else
			{
				strcpy(Prestr,str);
				//fputs(str,fpWrite);
				fprintf(fpWrite, "%ld \t %ld\n", getdiff(SetMaxDiff-1) , getdiff(SetMaxDiff-1));
				tmpChrmName = strstr(str, "chrom=");
				if (tmpChrmName == NULL){
					printf("Wrong annotation line: %s, must contain chromosome name!\n", str);
					exit(1);
				}
				j=6;
				while (tmpChrmName[j]!=' ' && j<14){
					ChrmNames[8*ChrmCount+j-6]=tmpChrmName[j];
					j++;
				}
				tmpSpanName = strstr(str, "span=");
				if (tmpSpanName == NULL){
					printf("Wrong annotation line: %s, must contain chromosome name!\n", str);
					exit(1);
				}
				k=5;
				while (tmpSpanName[k]!=' ' && k<14){
					SpanNames[8*ChrmCount+k-5]=tmpSpanName[k];
					k++;
				}
				++ChrmCount;
				PreLocation = 0;
		        PreExp = 0;
			}
		}
	}

	int i;
	strcpy(FileName,argv[1]);
	strcat(FileName,"ChrmName");
	FILE *fpName = fopen(FileName,"w");
	if (fpName == NULL) {
		fprintf(stderr,"Can't open output file!\n");
		exit(1);
	}
    for (i=0; i<ChrmCount; i++){
		fprintf(fpName,"%s ",&ChrmNames[8*i]);
	}


	strcpy(FileName,argv[1]);
	strcat(FileName,"SpanName");
	FILE *fpSpan = fopen(FileName,"w");
	if (fpSpan == NULL) {
		fprintf(stderr,"Can't open output file!\n");
		exit(1);
	}
    for (i=0; i<ChrmCount; i++){
		fprintf(fpSpan,"%s ",&SpanNames[8*i]);
	}

	fclose(fpRead);
	fclose(fpWrite);
	fclose(fpName);
	fclose(fpSpan);
	fclose(fpWriteNonZero);

	/////////////////////////////////////////
	//Min_Jump_Peak//


	long int L,V,L1,V1;
	strcpy(FileName,argv[1]);
	//strcat(FileName,"NewDCoding2");
	strcat(FileName,"NonZeroDiff");
	FILE *fpReadDC = fopen(FileName,"r");
	if (fpReadDC == NULL) {
			fprintf(stderr,"Can't open output file!\n");
			exit(1);
	}
	//fgets(str,sizeof(str),fpReadDC);
	while(!feof(fpReadDC))
	{
		fscanf(fpReadDC,"%ld \n", &V);
		fgetpos(fpReadDC,&position);
		if (V != 0 && V != getdiff(SetMaxDiff-1) && V!= getdiff(SetMaxDiff-2))
		{
			if(!feof(fpReadDC))
			{
				fscanf(fpReadDC,"%ld \n",  &V1);
				fsetpos(fpReadDC,&position);
				if(V > 0 && V1 < 0 && V1 != getdiff(SetMaxDiff-1) && V1!= getdiff(SetMaxDiff-2))
				{
					if(V < abs(V1)){
						if(V<Min_Peak)
						Min_Peak = V;
						if(abs(V1)>Max_Peak)
						Max_Peak = abs(V1);
					}
					else{
						if(V>Max_Peak)
						Max_Peak = V;
						if(abs(V1)<Min_Peak)
						Min_Peak = abs(V1);
					}

					/*  Peak = V;
					else
					  Peak = abs(V1);
					if(Peak < Min_Peak)
					  Min_Peak = Peak;
					if(Peak > Max_Peak)
					  Max_Peak = Peak;*/
				  }
			  }
		  }
  }

    fclose(fpReadDC);
	strcpy(FileName,argv[1]);
	strcat(FileName,"Jump");
	FILE *fpJump = fopen(FileName,"w");
	if (fpJump == NULL) {
			fprintf(stderr,"Can't open output file!\n");
			exit(1);
	}
   fprintf(fpJump, "%.3f %.3f \n ", Min_Peak*(1.0)/100, Max_Peak*(1.0)/100);
   fclose(fpJump);


	////////////////////////////////////////

	strcpy(FileName, argv[1]);
	strcat(FileName, "New");
	remove(FileName);
	strcpy(FileName, argv[1]);
	strcat(FileName, "NonZeroDiff");
	remove(FileName);
	/*strcpy(FileName, argv[1]);
	strcat(FileName, "New");
	strcat(FileName,"DCoding2");
	FILE *fpread25=fopen(FileName,"r");
	long unsigned int Counter25 = 0;
	long unsigned int Counternon25 =0;
	long unsigned int CounterOriginal = 0;
	long int l;
	long int v;
	fgets(str,50,fpread25);
	while(!feof(fpread25))
	{
		fscanf(fpread25, "%ld \t %ld \n", &l, &v);
		if(l == 0)
		{
			++Counter25;
			++CounterOriginal;
		}
		else if (l == getdiff(SetMaxDiff-1) || l == getdiff(SetMaxDiff-2))
				{
					++CounterOriginal;

		}
		else
		{
			++CounterOriginal;
			++Counternon25;
		}

	}
	fclose(fpread25);
	printf("Counter25=%lu, Counternon25= %lu , CounterOriginal= %lu", Counter25, Counternon25, CounterOriginal);*/


	return 1;
}