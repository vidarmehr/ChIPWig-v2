int partial_unblock(char *argv[], char *str, long int Start, long int End)
{
	long int sz,sz1,sz2;
	char * buffer;
	char FileName[200];
	long int i;
	FILE *fpRead;
	FILE *fpWriteLocStart;
	FILE *fpWriteFirstLocChr;
	FILE *fpWriteBlockNumber;
	FILE *fpWriteSizeCodedBlock;
	FILE *fpWriteCodedBlocks;
	FILE *fpWriteAllName;

	strcpy(FileName,argv[1]);
	fpRead=fopen(FileName,"r");

	strcpy(FileName,argv[1]);
	strcat(FileName,"fpFirstLoc");
	fpWriteLocStart=fopen(FileName,"w");
	if (fpWriteLocStart == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}
	//file size
	fscanf(fpRead,"%ld ",&sz);
	buffer = (char*)malloc(sz*sizeof(char));
	fread(buffer,sizeof(char),sz,fpRead);
	fwrite(buffer,sizeof(char),sz,fpWriteLocStart);
        fclose(fpWriteLocStart);
	free(buffer);

/////////////////////////////////////////////
        strcpy(FileName,argv[1]);
	strcat(FileName,"fpFirstLocChr");
	fpWriteFirstLocChr=fopen(FileName,"w");
	if (fpWriteFirstLocChr == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}
	fscanf(fpRead,"%ld ",&sz);
	buffer = (char*)malloc(sz*sizeof(char));
	fread(buffer,sizeof(char),sz,fpRead);
	fwrite(buffer,sizeof(char),sz,fpWriteFirstLocChr);
        fclose(fpWriteFirstLocChr);
	free(buffer);
////////////////////////////////////////////
	strcpy(FileName,argv[1]);
	strcat(FileName,"AllChrmName");
	fpWriteAllName=fopen(FileName,"w");
	if (fpWriteAllName == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}
	fscanf(fpRead,"%ld ",&sz);
	buffer = (char*)malloc(sz*sizeof(char));
	fread(buffer,sizeof(char),sz,fpRead);
	fwrite(buffer,sizeof(char),sz,fpWriteAllName);
        fclose(fpWriteAllName);
	free(buffer);

////////////////////////////////////////////////
	strcpy(FileName,argv[1]);
	strcat(FileName,"BlockNumber");
	fpWriteBlockNumber=fopen(FileName,"w");
	if (fpWriteBlockNumber == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}
	fscanf(fpRead,"%ld ",&sz);
	buffer = (char*)malloc(sz*sizeof(char));
	fread(buffer,sizeof(char),sz,fpRead);
	fwrite(buffer,sizeof(char),sz,fpWriteBlockNumber);
        fclose(fpWriteBlockNumber);
	free(buffer);
/////////////////////////////////////////////////////
	strcpy(FileName,argv[1]);
	strcat(FileName,"SizeCodedBlock");
	fpWriteSizeCodedBlock=fopen(FileName,"w");
	if (fpWriteSizeCodedBlock == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}
	fscanf(fpRead,"%ld ",&sz);
	buffer = (char*)malloc(sz*sizeof(char));
	fread(buffer,sizeof(char),sz,fpRead);
	fwrite(buffer,sizeof(char),sz,fpWriteSizeCodedBlock);
        fclose(fpWriteSizeCodedBlock);
	free(buffer);
/////////////////////////////////////////////////
	strcpy(FileName,argv[1]);
	strcat(FileName,"CodedBlocks");
	fpWriteCodedBlocks=fopen(FileName,"w");
	if (fpWriteCodedBlocks == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}
	fscanf(fpRead,"%ld ",&sz);
	buffer = (char*)malloc(sz*sizeof(char));
	fread(buffer,sizeof(char),sz,fpRead);
	fwrite(buffer,sizeof(char),sz,fpWriteCodedBlocks);
        fclose(fpWriteCodedBlocks);
	free(buffer);
///////////////////////////////////////////
	fclose(fpRead);

//////////////////////////////////////////////
	FILE *fpReadSizeBlock;
	strcpy(FileName,argv[1]);
	strcat(FileName,"SizeCodedBlock");
	fpReadSizeBlock=fopen(FileName,"r");
	if (fpReadSizeBlock == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
	}
//	fclose(fpReadSizeBlock);
	FILE *fpReadCodedBlocks;
	strcpy(FileName,argv[1]);
	strcat(FileName,"CodedBlocks");
	fpReadCodedBlocks=fopen(FileName,"r");
	if (fpReadCodedBlocks == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
	}
		//fclose(fpReadCodedBlocks);

	FILE *fpWriteWig;
	strcpy(FileName,argv[2]);
	strcat(FileName,"Seq");
	fpWriteWig=fopen(FileName,"w");
	if (fpWriteWig == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}
	//fclose(fpWriteWig);

	char str2[6];
	int flag=0;
	int ChrNumber=1;
	FILE *fpReadAllNames;
	strcpy(FileName,argv[1]);
	strcat(FileName,"AllChrmName");
	fpReadAllNames=fopen(FileName,"r");

	int loop=0;

	while(!feof(fpReadAllNames) && flag == 0){
		fscanf(fpReadAllNames,"%s \n",str2);
		//puts(str2);

		if(strcmp(str,str2)  ){
			++ChrNumber;
		}
		else{
		flag = 1;
		}
	}
	if(flag==0){
		printf("Wrong chr name is entered.");
		exit(1);
	}
	fclose(fpReadAllNames);

	//printf("\n%d\n", ChrNumber);


	FILE *fpReadBlockNumber;
	strcpy(FileName,argv[1]);
	strcat(FileName,"BlockNumber");
	fpReadBlockNumber=fopen(FileName,"r");

	long int BlockNumberChr;
	long int NextBlockNumberChr;

	for(i=1;i<=ChrNumber;i++){
		fscanf(fpReadBlockNumber, "%ld ", &BlockNumberChr);
		//printf("%ld \n",BlockNumberChr );
	}

	if(!feof(fpReadBlockNumber))
		fscanf(fpReadBlockNumber, "%ld \n", &NextBlockNumberChr);
	else
		NextBlockNumberChr = 1000000000;



	//printf("%ld %ld \n", BlockNumberChr, NextBlockNumberChr);

	fclose(fpReadBlockNumber);

	FILE *fpReadFirstLoc;
	strcpy(FileName,argv[1]);
	strcat(FileName,"fpFirstLoc");
	fpReadFirstLoc=fopen(FileName,"r");


	FILE *fpReadFirstLocChr;
	strcpy(FileName,argv[1]);
	strcat(FileName,"fpFirstLocChr");
	fpReadFirstLocChr=fopen(FileName,"r");

	long int StartLoc;
	long int NextLoc;
	for(i=0;i<ChrNumber;++i)
		fscanf(fpReadFirstLocChr, "%ld ", &StartLoc);
	fclose(fpReadFirstLocChr);

	//printf("%ld ", StartLoc);

	//new

	if(NextBlockNumberChr == 1000000000)
	    NextLoc = StartLoc + 1000000000;
	else{
	    for(i=0;i<=BlockNumberChr+1;++i)
		fscanf(fpReadFirstLoc, "%ld ", &NextLoc);
	}
     
           

	//printf(" %ld ", NextLoc);
	//fclose(fpReadFirstLoc);
        
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
 //if chr str and next chr are in one block//
 // just decompress one block//
    if (BlockNumberChr == NextBlockNumberChr){
	//printf("equal equal");
        int flag1 = 0;
	long int Sum=0;
	long int j;
        i = i-2;
        //printf("\n%d\n ", i);
        int m=0;
       if(Start<StartLoc){
	    printf("Wrong Chr Loc. Increase the first location!");
            flag1 = 1;
            return 1;
	   }
       else{
           fseek(fpReadSizeBlock,0,SEEK_SET);
	       Sum = 0;
	       if (i==0){
		//fscanf(fpReadSizeBlock, "%ld ", &sz2);
		      Sum = 0;
		    }
	    else{
                for(j=0;j<i;++j){
	                fscanf(fpReadSizeBlock, "%ld ", &sz2);
		            Sum = Sum + sz2;
	              }
		    }

			fseek(fpReadCodedBlocks,Sum, SEEK_SET);

			fscanf(fpReadSizeBlock, "%ld ", &sz1);
			//printf("%ld ", sz1);
			buffer = (char*)malloc(sz1*sizeof(char));
	        fread(buffer,sizeof(char),sz1,fpReadCodedBlocks);
	        FILE *fpWriteBlock;
	        strcpy(FileName,argv[1]);
	        strcat(FileName,"Block");
	        fpWriteBlock=fopen(FileName,"w");
	         if (fpWriteBlock == NULL) {
		     	    fprintf(stderr, "Can't open file %s!\n",FileName);
			        exit(1);
		     }
fwrite(buffer,sizeof(char),sz1,fpWriteBlock);
fclose(fpWriteBlock);
free(buffer);
int op;
fsplitRA(&op,argv);
decoder(argv);
DiffValSeq(argv);
DiffLoc1Seq(argv);
DiffLoc2Seq(argv);
De_RunLength(argv);
merge(argv);
to_wigRA_P(argv);

int Flag_start_file = 0;
char tmp;
long int Loc;
float Val;
char strhelp[35];
FILE  *fpReadBlock;

strcpy(FileName,argv[1]);
strcat(FileName,"Final");
fpReadBlock=fopen(FileName,"r");


while(!feof(fpReadBlock) && Flag_start_file == 0){
			        tmp=fgetc(fpReadBlock);
			        if(tmp >='0' && tmp<='9') {
				         ungetc(tmp,fpReadBlock);
				          fscanf(fpReadBlock,"%ld %f\n", &Loc, &Val);
				          if (Loc == StartLoc){
					            Flag_start_file = 1;
					            int value= Val * 1000;
				                 if(value % 1000 == 0) {
					                   fprintf(fpWriteWig,"%ld %d\n", Loc, value/1000);
				                   }
				                   else if(value % 100 == 0) {
					                 fprintf(fpWriteWig,"%ld %.1f\n", Loc, value/1000.0);
				                   }
				                   else if (value % 10 == 0)
   					                   fprintf(fpWriteWig,"%ld %.2f\n", Loc, value/1000.0);
   					               else
   					                  fprintf(fpWriteWig, "%ld %.3f\n", Loc, Val);

				              }
			         }
			       else{
			    	    ungetc(tmp,fpReadBlock);
			    	  // fscanf(fpReadBlock,"%s\n", strhelp);
				       fgets(strhelp,sizeof(strhelp),fpReadBlock);
    			       }
}
if(Flag_start_file == 1){
	while(!feof(fpReadBlock)){
		  tmp=fgetc(fpReadBlock);
		  if(tmp >='0' && tmp<='9')   {
			  ungetc(tmp,fpReadBlock);
			   fscanf(fpReadBlock,"%ld %f\n", &Loc, &Val);
			   int integ_value= Val * 1000;
				       if(integ_value % 1000 == 0)  {
					      fprintf(fpWriteWig,"%ld %d\n", Loc, integ_value/1000);
				           }
				       else if(integ_value % 100 == 0){
					      fprintf(fpWriteWig,"%ld %.1f\n", Loc, integ_value/1000.0);
				           }
					   else if(integ_value % 10 == 0){
					      fprintf(fpWriteWig,"%ld %.2f\n", Loc, integ_value/1000.0);
				           }
				         else
                             fprintf(fpWriteWig,"%ld %.3f\n", Loc, Val);
				   }
				   else{
					   ungetc(tmp,fpReadBlock);
					   //fscanf(fpReadBlock,"%s\n", strhelp);
					   //fprintf(fpWriteWig,"%s\n", strhelp);
					   fgets(strhelp,sizeof(strhelp),fpReadBlock);
					   //puts(strhelp);
					   fputs(strhelp,fpWriteWig);
				   }
				}
			}
}
}

///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////// 




else{

      i = BlockNumberChr;

	int flag1 = 0;
	long int Sum=0;
	long int j;
	int m=0;

	while(i <= NextBlockNumberChr && flag1 == 0){
		if(Start<StartLoc){
			printf("Wrong Chr Loc. Increase the first location!");
			flag1 = 1;
			return 1;
		}

		else if (Start < NextLoc && m==0 ){

			fseek(fpReadSizeBlock,0,SEEK_SET);
			Sum = 0;
			if (i==0){
				//fscanf(fpReadSizeBlock, "%ld ", &sz2);
				Sum = 0;
			}
			else{
                             for(j=0;j<i;++j){
				    fscanf(fpReadSizeBlock, "%ld ", &sz2);
				     Sum = Sum + sz2;
			      }
			 }

			fseek(fpReadCodedBlocks,Sum, SEEK_SET);

			fscanf(fpReadSizeBlock, "%ld ", &sz1);
			//printf("%ld ", sz1);
			buffer = (char*)malloc(sz1*sizeof(char));
	                fread(buffer,sizeof(char),sz1,fpReadCodedBlocks);
	                FILE *fpWriteBlock;
	                strcpy(FileName,argv[1]);
	                strcat(FileName,"Block");
	                fpWriteBlock=fopen(FileName,"w");
	                if (fpWriteBlock == NULL) {
		     	    fprintf(stderr, "Can't open file %s!\n",FileName);
			    exit(1);
		        }
	                fwrite(buffer,sizeof(char),sz1,fpWriteBlock);
                        fclose(fpWriteBlock);
	                free(buffer);
			int op;
		        fsplitRA(&op,argv);
		        decoder(argv);
		        DiffValSeq(argv);
                        DiffLoc1Seq(argv);
                        DiffLoc2Seq(argv);
		        De_RunLength(argv);
	                merge(argv);
	                to_wigRA_P(argv);

		       int Flag_start_file = 0;
		       char tmp;
		       long int Loc;
		       float Val;
		       char strhelp[35];
		       FILE  *fpReadBlock;

		        strcpy(FileName,argv[1]);
		        strcat(FileName,"Final");
		        fpReadBlock=fopen(FileName,"r");

		    	while(!feof(fpReadBlock) && Flag_start_file == 0){
			        tmp=fgetc(fpReadBlock);
			        if(tmp >='0' && tmp<='9') {
				         ungetc(tmp,fpReadBlock);
				          fscanf(fpReadBlock,"%ld %f\n", &Loc, &Val);
				          if (Loc == StartLoc){
					            Flag_start_file = 1;
					            int value= Val * 1000;
				                 if(value % 1000 == 0) {
					                   fprintf(fpWriteWig,"%ld %d\n", Loc, value/1000);
				                   }
				                   else if(value % 100 == 0) {
					                 fprintf(fpWriteWig,"%ld %.1f\n", Loc, value/1000.0);
				                   }
				                   else if (value % 10 == 0)
   					                   fprintf(fpWriteWig,"%ld %.2f\n", Loc, value/1000.0);
   					               else
   					                  fprintf(fpWriteWig, "%ld %.3f\n", Loc, Val);

				              }
			         }
			       else{
			    	    ungetc(tmp,fpReadBlock);
			    	  // fscanf(fpReadBlock,"%s\n", strhelp);
				    fgets(strhelp,sizeof(strhelp),fpReadBlock);
    			       }
			}
			if(Flag_start_file == 1){
				while(!feof(fpReadBlock)){
					tmp=fgetc(fpReadBlock);
			                if(tmp >='0' && tmp<='9')   {
					   ungetc(tmp,fpReadBlock);
					   fscanf(fpReadBlock,"%ld %f\n", &Loc, &Val);
					   int integ_value= Val * 1000;
				           if(integ_value % 1000 == 0)  {
					      fprintf(fpWriteWig,"%ld %d\n", Loc, integ_value/1000);
				           }
				           else if(integ_value % 100 == 0){
					      fprintf(fpWriteWig,"%ld %.1f\n", Loc, integ_value/1000.0);
				           }
					   else if(integ_value % 10 == 0){
					      fprintf(fpWriteWig,"%ld %.2f\n", Loc, integ_value/1000.0);
				           }
				           else
                                              fprintf(fpWriteWig,"%ld %.3f\n", Loc, Val);
				   }
				   else{
					   ungetc(tmp,fpReadBlock);
					   //fscanf(fpReadBlock,"%s\n", strhelp);
					   //fprintf(fpWriteWig,"%s\n", strhelp);
					   fgets(strhelp,sizeof(strhelp),fpReadBlock);
					   //puts(strhelp);
					   fputs(strhelp,fpWriteWig);
				   }
				}
			}
			++m;
			flag1=1;
			++i;
		}

	else if(Start<NextLoc && m!=0){
		fseek(fpReadSizeBlock,0,SEEK_SET);
		Sum = 0;
		if (i==0){
			//fscanf(fpReadSizeBlock, "%ld ", &sz2);
			Sum = 0;
			}
		else{
			for(j=0;j<i;++j){
				fscanf(fpReadSizeBlock, "%ld ", &sz2);
				//("%ld \n", sz2);
				Sum = Sum + sz2;
			  }
			}
			//printf(" %ld ", Sum);
		fseek(fpReadCodedBlocks,Sum, SEEK_SET);
		//	if(i==0)
			//	sz1=0;
			//else
			//{
		fscanf(fpReadSizeBlock, "%ld ", &sz1);
		//	}
		buffer = (char*)malloc(sz1*sizeof(char));
	        fread(buffer,sizeof(char),sz1,fpReadCodedBlocks);
	        FILE *fpWriteBlock;
	        strcpy(FileName,argv[1]);
	        strcat(FileName,"Block");
	        fpWriteBlock=fopen(FileName,"w");
	        if (fpWriteBlock == NULL) {
		     	fprintf(stderr, "Can't open file %s!\n",FileName);
			  exit(1);
		 }
	       fwrite(buffer,sizeof(char),sz1,fpWriteBlock);
               fclose(fpWriteBlock);
	       free(buffer);
	        int op;
		fsplitRA(&op,argv);
		decoder(argv);
		DiffValSeq(argv);
                DiffLoc1Seq(argv);
                DiffLoc2Seq(argv);
	        De_RunLength(argv);
	        merge(argv);
	       to_wigRA_P(argv);

                 int Flag_start_file = 0;
	         char tmp;
                 long int Loc;
	         float Val;
		 //char strhelp[50];
		 FILE  *fpReadBlock;

		  strcpy(FileName,argv[1]);
		  strcat(FileName,"Final");
		  fpReadBlock=fopen(FileName,"r");

			//fseek(fpReadBlock,0,SEEK_SET);
		  sz=fsize(fpReadBlock);
		  buffer = (char*)malloc(sz*sizeof(char));
	          fread(buffer,sizeof(char),sz,fpReadBlock);
	          fwrite(buffer,sizeof(char),sz,fpWriteWig);
                  fclose(fpReadBlock);
		  free(buffer);

		  flag1 = 1;
		  ++m;
		  ++i;
		}
	else {
		if(NextLoc!= 1000000000){
		     fscanf(fpReadFirstLoc, "%ld ", &NextLoc);
		    // printf("%ld ", NextLoc);
		 }
		else
			NextLoc = NextLoc+ 10000000;
	  // printf("%ld ",NextLoc);
	   ++i;
	   ++m;
	  }

	}
	//printf("%d", i);

	if(i == NextBlockNumberChr + 1){
		for(j=0;j<i-1;++j){
			fscanf(fpReadSizeBlock, "%ld ", &sz2);
			//("%ld \n", sz2);
			Sum = Sum + sz2;
		 }

					//printf(" %ld ", Sum);
		fseek(fpReadCodedBlocks,Sum, SEEK_SET);
                fscanf(fpReadSizeBlock, "%ld ", &sz1);
                buffer = (char*)malloc(sz1*sizeof(char));
	        fread(buffer,sizeof(char),sz1,fpReadCodedBlocks);
	        FILE *fpWriteBlock;
		strcpy(FileName,argv[1]);
		strcat(FileName,"Block");
		fpWriteBlock=fopen(FileName,"w");
	        if (fpWriteBlock == NULL) {
		        fprintf(stderr, "Can't open file %s!\n",FileName);
			 exit(1);
		 }
	        fwrite(buffer,sizeof(char),sz1,fpWriteBlock);
		fclose(fpWriteBlock);
	        free(buffer);

                 int op;
		fsplitRA(&op,argv);
		decoder(argv);
		DiffValSeq(argv);
	        DiffLoc1Seq(argv);
		DiffLoc2Seq(argv);
		De_RunLength(argv);
                merge(argv);
	        to_wigRA_P(argv);

                int Flag_start_file = 0;
		char tmp;
		long int Loc;
	        float Val;
		FILE  *fpReadBlock;
                strcpy(FileName,argv[1]);
		strcat(FileName,"Final");
		fpReadBlock=fopen(FileName,"r");
                //fseek(fpReadBlock,0,SEEK_SET);
		sz=fsize(fpReadBlock);
		buffer = (char*)malloc(sz*sizeof(char));
	        fread(buffer,sizeof(char),sz,fpReadBlock);
	        fwrite(buffer,sizeof(char),sz,fpWriteWig);
		fclose(fpReadBlock);
		free(buffer);
	  }

	///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////
       int flag2 = 0;
	while(i <= NextBlockNumberChr && flag2 == 0){
		if(End > NextLoc ){
			fseek(fpReadSizeBlock,0,SEEK_SET);
			Sum = 0;
			if (i==0){
					Sum = 0;
			         }
			else{
                            for(j=0;j<i;++j){
		     		fscanf(fpReadSizeBlock, "%ld ", &sz2);
		    		//("%ld \n", sz2);
		    		Sum = Sum + sz2;
		             }
		      	}
			//(" %ld ", Sum);
			fseek(fpReadCodedBlocks,Sum, SEEK_SET);
			fscanf(fpReadSizeBlock, "%ld ", &sz1);
			//("%ld ", sz1);
			buffer = (char*)malloc(sz1*sizeof(char));
	                fread(buffer,sizeof(char),sz1,fpReadCodedBlocks);
	                FILE *fpWriteBlock;
	                strcpy(FileName,argv[1]);
	                strcat(FileName,"Block");
	                fpWriteBlock=fopen(FileName,"w");
	                if (fpWriteBlock == NULL) {
		     	    fprintf(stderr, "Can't open file %s!\n",FileName);
			    exit(1);
		        }
	                fwrite(buffer,sizeof(char),sz1,fpWriteBlock);
                        fclose(fpWriteBlock);
	                free(buffer);
			int op;
		        fsplitRA(&op,argv);
		        decoder(argv);
		        DiffValSeq(argv);
                        DiffLoc1Seq(argv);
                        DiffLoc2Seq(argv);
	        	De_RunLength(argv);
	                merge(argv);
	                to_wigRA_P(argv);

		       FILE  *fpReadBlock;
                       strcpy(FileName,argv[1]);
		       strcat(FileName,"Final");
		       fpReadBlock=fopen(FileName,"r");
		       sz=fsize(fpReadBlock);
		       buffer = (char*)malloc(sz*sizeof(char));
	               fread(buffer,sizeof(char),sz,fpReadBlock);
	               fwrite(buffer,sizeof(char),sz,fpWriteWig);
                       fclose(fpReadBlock);
	               free(buffer);
		       fscanf(fpReadFirstLoc, "%ld ", &NextLoc);
		        ++i;
		 }
		else{
		   	flag2 = 1;
		}
	}
	}
	
	fclose(fpWriteWig);
	fclose(fpReadFirstLoc);
	fclose(fpReadSizeBlock);
	fclose(fpReadCodedBlocks);



	 //////////////////////////////////////////////////////////////////////////////////////////////
     /////////////////////////////////////////////////////////////////////////////////////////////
	//return exact locations and numbers between Start and End
        int Nd=18;
        int SetMaxDiff = exp2(Nd); //set max alphabet size
        long int ArrayLocations[SetMaxDiff]; //maps each consecutive integer to the actual alphabet
        memset(ArrayLocations,0,SetMaxDiff*sizeof(long int));
        char str3[1000];
        float ArrayValues[SetMaxDiff]; //maps each consecutive integer to the actual alphabet
        memset(ArrayValues,0,SetMaxDiff*sizeof(int));

   int j;
	FILE *fpReadWig;
	strcpy(FileName,argv[2]);
	strcat(FileName,"Seq");
	fpReadWig=fopen(FileName,"r");
	FILE *fpWriteSeq;
	strcpy(FileName,argv[2]);
	//strcat(FileName,"Seq");
	fpWriteSeq=fopen(FileName,"w");
	 flag=0;
	int start_index;
	int end_index;
	int flag_end=0;
	long int Location;
	float Value;
	int Size;
	char tmp;
	int jj;
	char *tmpChrmName;
	int NextChrom=0;
	char ChrmNames[12];
	while(!feof(fpReadWig) && flag == 0 && NextChrom==0){
		flag=0;
		i = 0;
		while(!feof(fpReadWig) && i<SetMaxDiff && NextChrom==0){
			tmp=fgetc(fpReadWig);
		       if  (tmp >= '0' && tmp <= '9') {
				ungetc(tmp,fpReadWig);
				fscanf(fpReadWig,"%ld %f\n", &Location,&Value);
				ArrayLocations[i] = Location;
				ArrayValues[i] = Value;
				++i;
		        }
		       else {
			   ungetc(tmp,fpReadWig);
			   fgets(str3,sizeof(str3),fpReadWig);
			   //puts(str3);
			   tmpChrmName = strstr(str3, "chrom=");
			    if (tmpChrmName == NULL){
					printf("Wrong annotation line: %s, must contain chromosome name!\n", str);
					exit(1);
				}
			    jj=6;
			    while ( jj<10 && (tmpChrmName[jj]>='0' && tmpChrmName[jj]<='9') || (tmpChrmName[jj]>='a' && tmpChrmName[jj]<='z') || (tmpChrmName[jj]>='A' && tmpChrmName[jj]<='Z')){
					ChrmNames[jj-6]=tmpChrmName[jj];
					jj++;
			     }
			     if(tmpChrmName[10]>='0' && tmpChrmName[10]<='9'){
				   ChrmNames[4]=tmpChrmName[10];
				   ChrmNames[5]='\0';
				}
				else
					ChrmNames[4]='\0';
				if(strcmp(ChrmNames,str)){
					NextChrom=1;
				}
		   }
		}
		 Size = i;

		start_index=binsearch(Size,ArrayLocations,Start);
		if (start_index != -1)
	    {
			flag = 1;
	       if(End>ArrayLocations[Size-1]) {
                     for(j=start_index;j<Size;++j){
				 int in_value= ArrayValues[j] * 1000;
				 if(in_value % 1000 == 0){
					 fprintf(fpWriteSeq,"%ld %d\n", ArrayLocations[j], in_value/1000);
				 }
				 else if(in_value % 100 == 0){
					 fprintf(fpWriteSeq,"%ld %.1f\n", ArrayLocations[j], in_value/1000.0);
				 }
		                 else if(in_value % 10 == 0) {
					 fprintf(fpWriteSeq,"%ld %.2f\n", ArrayLocations[j], in_value/1000.0);
				 }
		     
				 else
                                       fprintf(fpWriteSeq,"%ld %.3f\n", ArrayLocations[j], ArrayValues[j]);
		        }
		   }

		   else{
			   end_index=binsearch(Size,ArrayLocations,End);
			   flag_end=1;
			    for(j=start_index;j<=end_index;++j){
			       int in_value= ArrayValues[j] * 1000;
				   if(in_value % 1000 == 0){
					 fprintf(fpWriteSeq,"%ld %d\n", ArrayLocations[j], in_value/1000);
				   }
				    else if(in_value % 100 == 0){
					   fprintf(fpWriteSeq,"%ld %.1f\n", ArrayLocations[j], in_value/1000.0);
				   }
				     else if (in_value % 10 == 0){
						fprintf(fpWriteSeq,"%ld %.2f\n", ArrayLocations[j], in_value/1000.0);
				   }

				 else
                                      fprintf(fpWriteSeq,"%ld %.3f\n", ArrayLocations[j], ArrayValues[j]);
		                }
		       }
		   }
	}

	////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////
	        NextChrom=0;
		while(!feof(fpReadWig) && flag_end == 0 && NextChrom == 0){
		    flag_end = 0;
		    i = 0;
		    while(!feof(fpReadWig) && i<SetMaxDiff && NextChrom == 0) {
			  tmp=fgetc(fpReadWig);
		           if  (tmp >= '0' && tmp <= '9')  {
				 ungetc(tmp,fpReadWig);
				 fscanf(fpReadWig,"%ld %f\n", &Location,&Value);
				 ArrayLocations[i] = Location;
				 ArrayValues[i] = Value;
				 ++i;
		           }
		          else  {
			    ungetc(tmp,fpReadWig);
			    fgets(str3,sizeof(str3),fpReadWig);
			    tmpChrmName = strstr(str3, "chrom=");
			   if (tmpChrmName == NULL){
					printf("Wrong annotation line: %s, must contain chromosome name!\n", str);
					exit(1);
				}
				jj=6;
				while ( jj<10 && (tmpChrmName[jj]>='0' && tmpChrmName[jj]<='9') || (tmpChrmName[jj]>='a' && tmpChrmName[jj]<='z') || (tmpChrmName[jj]>='A' && tmpChrmName[jj]<='Z')){
					ChrmNames[jj-6]=tmpChrmName[jj];
					jj++;
				}
				if(tmpChrmName[10]>='0' && tmpChrmName[10]<='9'){
				   ChrmNames[4]=tmpChrmName[10];
				   ChrmNames[5]='\0';
				}
				else
					ChrmNames[4]='\0';

				if(strcmp(ChrmNames,str)){
					NextChrom=1;
					//puts(str);
					//puts(tmpChrmName);
					//puts(ChrmNames);
				}
		     }

		 Size = i;

		end_index=binsearch(Size,ArrayLocations,End);
		if (end_index != -1){
			flag_end = 1;
	        for(j=0;j<=end_index;++j) {
			   int in_value= ArrayValues[j] * 1000;
				 if(in_value % 1000 == 0){
					 fprintf(fpWriteSeq,"%ld %d\n", ArrayLocations[j], in_value/1000);
				 }
				 else if(in_value % 100 == 0){
					 fprintf(fpWriteSeq,"%ld %.1f\n", ArrayLocations[j], in_value/1000.0);
				 }
				 else if (in_value % 10 == 0){
					 fprintf(fpWriteSeq,"%ld %.2f\n", ArrayLocations[j], in_value/1000.0);
				 }
				else
                     fprintf(fpWriteSeq,"%ld %.3f\n", ArrayLocations[j], ArrayValues[j]);
		     }
		   }


		else
		{
		   for(j=0;j<Size;++j) {
			   int in_value= ArrayValues[j] * 1000;
				 if(in_value % 1000 == 0){
					 fprintf(fpWriteSeq,"%ld %d\n", ArrayLocations[j], in_value/1000);
				 }
				 else if(in_value % 100 == 0) {
					 fprintf(fpWriteSeq,"%ld %.1f\n", ArrayLocations[j], in_value/1000.0);
				 }
				 else if (in_value % 10 ==0){
					 fprintf(fpWriteSeq,"%ld %.2f\n", ArrayLocations[j], in_value/1000.0);
				 }

				 else
                                          fprintf(fpWriteSeq,"%ld %.3f\n", ArrayLocations[j], ArrayValues[j]);
		     }
	    }

	}
}

		fclose(fpReadWig);
		fclose(fpWriteSeq);
		///////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////


		FILE *fpStat;
		strcpy(FileName,argv[2]);
		fpStat=fopen(FileName,"r");
		if (fpStat == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}
		double Min_Value = 100000000;
		double Max_Value = 0;
		double SumValue = 0;
		long int NumberOfData=0;
		while(!feof(fpStat)){
			fscanf(fpStat,"%ld %f",&Location,&Value);
			++NumberOfData;
			if(Value < Min_Value)
			    Min_Value = Value;
			if(Value > Max_Value)
				Max_Value = Value;
	    	SumValue = SumValue + Value;
		}
		fclose(fpStat);
		double Mean= SumValue/NumberOfData;
		FILE *fpSS;
		strcpy(FileName,argv[2]);
		strcat(FileName,"SummarySequence");
		fpSS=fopen(FileName,"a");
		fprintf(fpSS, "Min_Value=%.3f, Max_Value= %.3f, Mean= %3f ", Min_Value , Max_Value , Mean);
		fclose(fpSS);

		 FILE *fpStat2;
		strcpy(FileName,argv[2]);
		fpStat2=fopen(FileName,"r");
		if (fpStat2 == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}

		NumberOfData=0;
		double std = 0;
		double Variance=0;
		while(!feof(fpStat2)){
			fscanf(fpStat2,"%ld %f",&Location,&Value);
			++NumberOfData;
			 Variance = Variance + (Value-Mean)*(Value-Mean);
		}
		fclose(fpStat2);
		Variance = Variance/(NumberOfData-1);
		std= sqrt(Variance);
		FILE *fpSS2;
		strcpy(FileName,argv[2]);
		strcat(FileName,"SummarySequence");
		fpSS2=fopen(FileName,"a");
		fprintf(fpSS2, " Variance=%lf, std= %lf\n ", Variance, std);
	        fclose(fpSS2);

		///////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////

		char T[34][40];//files to delete
		char Removelist[1][34][40]={
		   		{"buffer1","buffer2","DiffLocSeq1", "DiffLocSeq2","DiffValSeq","DiffLocSeqMatlab1", "DiffLocSeqMatlab2","DiffValSeqMatlab","DiffLocSeqMatlab1Decode", "DiffLocSeqMatlab2Decode","DiffValSeqMatlabDecode","ExceedLoc","ExceedVal","DiffLoc1","DiffLoc2","ChrmName","SpanName","DiffLocSeqDe_RunLength","DiffVal","DiffValSeqMatlabCode","DiffLocSeqMatlab2Code","DiffLocSeqMatlab1Code","DCoding2", "AllChrmName", "Block", "BlockNumber", "CodedBlocks","Final","fpFirstLoc","SizeCodedBlock","Summary","fpFirstLocChr"},
			};

		  for (i=0; i<34; i++){
				for (j=0; j<40; j++){
					T[i][j] = Removelist[0][i][j];
				}
			}

		   strcpy(FileName, argv[1]);
		   i=0;
	           while (i<34 && T[i][0]){
				strcpy(Removelist[0][i],FileName);
				strcat(Removelist[0][i],T[i]);
				remove(Removelist[0][i]);
				//printf("file %s removed\n",d[i]);
				i++;
			}

 return 1;
}
