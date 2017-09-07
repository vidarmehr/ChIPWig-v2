int to_wig_Lossy(char *argv[])
{
	char FileName[400];
	long int DiffVal;
	long int DiffLoc;
	long int DiffExVal;
	long int DiffExLoc;
	int Nd=18;
    unsigned int SetMaxDiff = exp2(Nd);
	long int PreLoc=0;
	long int PreVal=0;
	double C1;
	strcpy(FileName, argv[1]);
	strcat(FileName, "DCoding2");
	FILE *fpRead = fopen(FileName, "r");
	if (fpRead == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

	strcpy(FileName, argv[1]);
	strcat(FileName, "buffer1");
	FILE *fpWriteb = fopen(FileName, "w");
	if (fpWriteb == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

	strcpy(FileName, argv[1]);
	strcat(FileName, "ExceedLoc");
	FILE *fpReadExLoc = fopen(FileName, "r");
	if (fpReadExLoc == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

	strcpy(FileName, argv[1]);
	strcat(FileName, "ExceedVal");
	FILE *fpReadExVal = fopen(FileName, "r");
	if (fpReadExVal == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

    strcpy(FileName, argv[1]);
	strcat(FileName, "Extra");
	FILE *fpReadExtra = fopen(FileName, "r");
	if (fpReadExtra == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}


	while(!feof(fpRead))
	{
		fscanf(fpRead,"%ld %ld\n", &DiffLoc,&DiffVal);
		if(DiffLoc==getdiff(SetMaxDiff-1) || DiffVal==getdiff(SetMaxDiff-1))
		{
			if(DiffLoc==getdiff(SetMaxDiff-1) && DiffVal!=getdiff(SetMaxDiff-1))
			{
			fscanf(fpReadExLoc,"%ld",&DiffExLoc);
			  fprintf(fpWriteb,"%ld %ld\n", DiffLoc,DiffVal);
		    }
			else if (DiffLoc!=getdiff(SetMaxDiff-1) && DiffVal==getdiff(SetMaxDiff-1))
			{
			  fscanf(fpReadExVal,"%ld",&DiffExVal);
			  fprintf(fpWriteb,"%ld %ld\n", DiffLoc,DiffVal);
			}
			else
			{
				fscanf(fpReadExLoc,"%ld",&DiffExLoc);
				fscanf(fpReadExVal,"%ld",&DiffExVal);
			  fprintf(fpWriteb,"%ld %ld\n", DiffLoc,DiffVal);
			}

		}

		else if(DiffLoc==getdiff(SetMaxDiff-2) || DiffVal==getdiff(SetMaxDiff-2))
		{
			if(DiffLoc==getdiff(SetMaxDiff-2) && DiffVal!=getdiff(SetMaxDiff-2))
			{
				fscanf(fpReadExLoc,"%ld",&DiffExLoc);
				fprintf(fpWriteb,"%ld %ld\n", DiffExLoc,DiffVal);
			}
			else if (DiffLoc!=getdiff(SetMaxDiff-2) && DiffVal==getdiff(SetMaxDiff-2))
			{
				fscanf(fpReadExVal,"%ld ",&DiffExVal);
				fprintf(fpWriteb,"%ld %ld\n", DiffLoc,DiffExVal);
			}
			else if (DiffLoc==getdiff(SetMaxDiff-2) && DiffVal==getdiff(SetMaxDiff-2))
			{
				fscanf(fpReadExLoc,"%ld ",&DiffExLoc);
				fscanf(fpReadExVal,"%ld ",&DiffExVal);
				fprintf(fpWriteb,"%ld %ld\n", DiffLoc,DiffVal);
			}
		}


		else if(DiffLoc==getdiff(SetMaxDiff-3) || DiffVal==getdiff(SetMaxDiff-3))
		{
			if(DiffLoc==getdiff(SetMaxDiff-3) && DiffVal!=getdiff(SetMaxDiff-3))
			{
				fscanf(fpReadExLoc,"%ld",&DiffExLoc);
				fprintf(fpWriteb,"%ld %ld\n", DiffExLoc,DiffVal);
			}
			else if (DiffLoc!=getdiff(SetMaxDiff-3) && DiffVal==getdiff(SetMaxDiff-3))
			{
				fscanf(fpReadExVal,"%ld ",&DiffExVal);
				fprintf(fpWriteb,"%ld %ld\n", DiffLoc,DiffExVal);
			}
			else if (DiffLoc==getdiff(SetMaxDiff-3) && DiffVal==getdiff(SetMaxDiff-3))
			{
				fscanf(fpReadExLoc,"%ld ",&DiffExLoc);
				fscanf(fpReadExVal,"%ld ",&DiffExVal);
				fprintf(fpWriteb,"%ld %ld\n", DiffExLoc,DiffExVal);
			}
		}
		else

                 fprintf(fpWriteb,"%ld %ld\n", DiffLoc,DiffVal);
	}
	fclose(fpWriteb);
	fclose(fpReadExVal);
	fclose(fpReadExLoc);
	fclose(fpRead);

	//////////////////////////////////////
	/////////////////////////////////////
	////////////////////////////////////
	/*strcpy(FileName, argv[1]);
	strcat(FileName, "buffer1");
	FILE *fpReadb = fopen(FileName, "r");
	if (fpReadb == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

	strcpy(FileName, argv[1]);
	strcat(FileName, "buffer2");
	FILE *fpWriteb2 = fopen(FileName, "w");
	if (fpWriteb2 == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}


	while(!feof(fpReadb))
	{
		fscanf(fpReadb, "%ld %ld\n",  &DiffLoc,&DiffVal);
		if(DiffLoc==getdiff(SetMaxDiff-1) && DiffVal==getdiff(SetMaxDiff-1))
		{
			fprintf(fpWriteb2,"%ld %ld\n", DiffLoc, DiffVal);
			PreLoc=0;
			PreVal=0;
		}
		else if (DiffLoc==getdiff(SetMaxDiff-2) && DiffVal==getdiff(SetMaxDiff-2))
		{
			fprintf(fpWriteb2,"%ld %ld\n", DiffLoc, DiffVal);
			//PreLoc=0;
			//PreVal=0;
		}
		else
		{
			fprintf(fpWriteb2,"%ld %ld\n", DiffLoc+PreLoc, DiffVal+PreVal);
			PreLoc=DiffLoc+PreLoc;
			PreVal=DiffVal+PreVal;
		}
	}


	fclose(fpReadb);
	fclose(fpWriteb2);*/
	///////////////////////////////////////
	/////////////////////////////////////

	char ChrmNames[8*32]; //every chrm has a name less than 8 characters, assume no more than 32 chrm
	memset(ChrmNames,0,8*32*sizeof(char));
	char *tmpChrmName;
	int ChrmCount=0;
	int i=0;

	strcpy(FileName,argv[1]);
	strcat(FileName,"ChrmName");
	FILE *fpName = fopen(FileName, "r");
	if (fpName == NULL) {
		fprintf(stderr, "Can't open input file %s!\n",FileName);
		exit(1);
	}
    while(!feof(fpName)){
        fscanf(fpName,"%8s",&ChrmNames[8*ChrmCount]);
        ChrmCount++;
    }
	fclose(fpName);
	int SpanNames[32]; //every chrm has a name less than 8 characters, assume no more than 32 chrm
	//memset(SpanNames,0,2*32*sizeof(char));
	char *tmpSpanName;
	 ChrmCount=0;
	strcpy(FileName,argv[1]);
	strcat(FileName,"SpanName");
	FILE *fpSpan = fopen(FileName, "r");
	if (fpSpan == NULL) {
		fprintf(stderr, "Can't open input file %s!\n",FileName);
		exit(1);
	}
	int l;
    while(!feof(fpSpan)){
        fscanf(fpSpan,"%d\n",&l);
		SpanNames[ChrmCount]=l;
        ChrmCount++;
    }
	fclose(fpSpan);
	strcpy(FileName, argv[1]);
	//strcat(FileName, "buffer2");
   strcat(FileName, "buffer1");
	FILE *fpReadb2 = fopen(FileName, "r");
	if (fpReadb2 == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

	strcpy(FileName, argv[2]);
	//strcat(FileName, "Final");
	FILE *fpWritebf = fopen(FileName, "w");
	if (fpWritebf == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}
	int dum;
	int flag;
	float Dummy;
	int Help;
	char lastline[100];
	for(i=0;i<100;++i)
		lastline[i]=' ';

	fpos_t position;

	i=0;
	int Dumm=0;
	long int DiffLoc1,DiffVal1;
	while(!feof(fpReadb2))
	{

		fscanf(fpReadb2, "%ld %ld\n",  &DiffLoc,&DiffVal);
		fgetpos(fpReadb2,&position);
		//
		//if(!fscanf(fpReadb2, "%ld %ld\n",  &DiffLoc1,&DiffVal1))
			if(feof(fpReadb2) )
		      break;
		else
		{
			fsetpos(fpRead, &position);
		    if(DiffLoc==getdiff(SetMaxDiff-1) && DiffVal==getdiff(SetMaxDiff-1))
		    {
			   //fprintf(fpWritebf,"%ld %ld\n", DiffLoc, DiffVal);
			   fprintf(fpWritebf,"variableStep chrom=%s span=%d\n", &ChrmNames[i*8], SpanNames[i]);
			    ++i;
			    flag=0;
			    PreLoc=0;
			    PreVal=0;
			    Dumm = 1;
		     }
		    else if (DiffLoc==getdiff(SetMaxDiff-2) && DiffVal==getdiff(SetMaxDiff-2))
		     {
			//fprintf(fpWritebf,"%ld %ld\n", DiffLoc, DiffVal);

			   if(flag==0)
				   dum=i-1;;
			   fprintf(fpWritebf,"variableStep chrom=%s span=%d\n", &ChrmNames[dum*8], SpanNames[dum]);
			   flag=1;
			   Dumm = 1;
			   //++i;
		       //PreLoc=0;
			   //PreVal=0;
			 }
		   else
		   {
			 //Dummy = round(100*(DiffVal+PreVal));
			// Help = (int)Dummy *100;
			  if(Dumm == 0)
			   {
				 PreLoc=0;
			     PreVal=0;
				 Dumm = 1;
			   }

              /* if((DiffVal+PreVal) == 0 )
               {
				   fscanf(fpReadExtra, "%lf ", &C1);
				   fprintf(fpWritebf, "%ld\t%.4f\n", DiffLoc+PreLoc, C1);
			   }

			   else if( (DiffVal+PreVal)% 100 == 0)
			  	{
			  	//fgetpos(fpWriteb,&position);
			  	fprintf(fpWritebf, "%ld\t%.2f\n", DiffLoc+PreLoc, (DiffVal+PreVal)/100.0 );
			  }
			 else if ((DiffVal+PreVal) % 10 == 0)
			  {
				//fgetpos(fpWriteb,&position);
                 fprintf(fpWritebf,"%ld\t%.2f\n", DiffLoc+PreLoc, (DiffVal+PreVal)/100.0);
			  }
			  //else if ((DiffVal+PreVal) % 10 == 0)
			  //{
				// fprintf(fpWritebf,"%ld\t%.2f\n", DiffLoc+PreLoc, (DiffVal+PreVal)/100.0);
			 //}

			 else{*/
				//fgetpos(fpWriteb,&position);
				fprintf(fpWritebf,"%ld\t%.2f\n", DiffLoc+PreLoc, (DiffVal+PreVal)/100.0);
			 // }
			 PreLoc=DiffLoc+PreLoc;
			 PreVal=DiffVal+PreVal;
	    	}
		 }
	 }


	fclose(fpReadb2);
	fclose(fpWritebf);
	fclose(fpReadExtra);

   char T[24][40];//files to delete
   char Removelist[1][24][40]={
   		{"buffer1","buffer2","DiffLocSeq1", "DiffLocSeq2","DiffValSeq","DiffLocSeqMatlab1", "DiffLocSeqMatlab2","DiffValSeqMatlab","DiffLocSeqMatlab1Decode", "DiffLocSeqMatlab2Decode","DiffValSeqMatlabDecode","ExceedLoc","ExceedVal","DiffLoc1","DiffLoc2","ChrmName","SpanName","DiffLocSeqDe_RunLength","DiffVal","DiffValSeqMatlabCode","DiffLocSeqMatlab2Code","DiffLocSeqMatlab1Code","DCoding2"},
	};
	int j;
     for (i=0; i<24; i++){
		for (j=0; j<40; j++){
			T[i][j] = Removelist[0][i][j];
		}
	}

   strcpy(FileName, argv[1]);
   i=0;
	while (i<24 && T[i][0]){
		strcpy(Removelist[0][i],FileName);
		strcat(Removelist[0][i],T[i]);
		remove(Removelist[0][i]);
		//printf("file %s removed\n",d[i]);
		i++;
	}
	return 1;
}