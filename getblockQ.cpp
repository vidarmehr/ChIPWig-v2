//
//  getblock.cpp
//
//  Created by Vida Ravanmehr.
//  Copyright (c) 2016 Vida Ravanmehr. All rights reserved.
//
//  Support random access, encode blocks of 2^BlockSize
//
//  fpFirstLocChr stores the starting location of each chr
//  fpFirstLoc stores the first location in each block
//  fpSmry stores min, max, mean, std of values
//  fpBlockNumber stores the accumulated number of code blocks so far before each chrm (first item=0, last item=total # blocks, #items = #chrm+1)



int getblockQ(char *argv[])
{
        char FileName[200];
	long int NumberOfData;
	long int NumberOfActualData = 0;
	fpos_t position;
	char tmp;
	int j;
	long int Value;
	long unsigned int Location;
	long int sz;
	char *buffer;
	FILE *fp_1;
	FILE *fp_2;
	char str[1000];
	char Prestr[1000];
	int ChrmCount=0;
	long unsigned int IntValue=0;
	long unsigned int C1=0;

	int Nd=18;
	int SetMaxDiff = exp2(Nd); //set max alphabet size
	float Map[SetMaxDiff]; //maps each consecutive integer to the actual alphabet
	memset(Map,0,SetMaxDiff*sizeof(float));


	char ChrmNames[8*32]; //every chrm has a name less than 8 characters, assume no more than 32 chrm
	memset(ChrmNames,0,8*32*sizeof(char));
	char *tmpChrmName;

	strcpy(FileName, argv[1]);
	strcat(FileName, "Mult100");
	FILE *fpRead = fopen(FileName, "r");
	if (fpRead == NULL) {
		 fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
	}

	strcpy(FileName, argv[1]);
	strcat(FileName, "fpFirstLoc");
	FILE *fpWriteFirstLoc = fopen(FileName, "w");
	if (fpWriteFirstLoc == NULL) {
		 fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
	}



	strcpy(FileName, argv[1]);
	strcat(FileName, "fpFirstLocChr");
	FILE *fpWriteFirstLocChr = fopen(FileName, "w");
	if (fpWriteFirstLocChr == NULL) {
		 fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
	}

	//which block involves the next chromosome
	strcpy(FileName, argv[1]);
	strcat(FileName, "BlockNumber");
	FILE *fpWriteBlockNumber = fopen(FileName, "w");
	if (fpWriteBlockNumber == NULL) {
		 fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
	}

	strcpy(FileName, argv[1]);
	strcat(FileName,"CodedBlocks");
	FILE *fpWriteCodedBlocks = fopen(FileName, "w");
	if (fpWriteCodedBlocks == NULL) {
		 fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
	}

	strcpy(FileName, argv[1]);
	strcat(FileName, "SizeCodedBlock");
	FILE *fpWriteSizeCodedBlock = fopen(FileName, "w");
	if (fpWriteSizeCodedBlock == NULL) {
		 fprintf(stderr, "Can't open file %s!\n",FileName);
		 exit(1);
	}

	strcpy(Prestr, "empty");
	long int NumberOfBlocks=0;
	int Flag = 0;
	int Flag2=0;
       while(!feof(fpRead)){
		NumberOfData = 0;
		NumberOfActualData = 0;
		strcpy(FileName, argv[1]);
	        strcat(FileName, "New");
	        FILE *fpWrite = fopen(FileName, "w");
	        if (fpWrite == NULL) {
		    fprintf(stderr, "Can't open file %s!\n",FileName);
		     exit(1);
	        }
	    /* strcpy(FileName, argv[1]);
		 	strcat(FileName, "Extra");
		 	FILE *fpWriteExt;
		 	fpWriteExt = fopen(FileName, "w");
		 	if (fpWriteExt == NULL) {
		 		fprintf(stderr, "Can't open input file %s!\n",FileName);
		 		exit(1);
		 	}*/

		long int Min_Value = 100000000;
		long int Max_Value = 0;
		double SumValue = 0;
		double SumSquaredValue = 0;
		while(NumberOfData<exp2(BlockSize) && !feof(fpRead) ){

		   tmp = fgetc(fpRead);
		   if  (tmp >= '0' && tmp <= '9'){
				ungetc(tmp,fpRead);
				//fscanf(fpRead,"%lu %lf\n", &Location,&Value);
				/*IntValue = (int) (ceil)(10000*Value);
				C1= IntValue/10;
				if(IntValue % 10 != 0 && C1 % 10 != 0  ){
					fprintf(fpWriteExt,"%.4f ",Value );
				    fprintf(fpWrite, "%lu %d\n", Location,0);
					}
				else{
					IntValue= IntValue/10;
					fprintf(fpWrite, "%lu %lu\n", Location,IntValue);
					}*/

				fscanf(fpRead,"%lu %ld\n", &Location,&Value);
		                fprintf(fpWrite,"%lu %ld\n", Location , Value);
				if(NumberOfData == 0){
					fprintf(fpWriteFirstLoc, "%lu \n", Location);
                                }
				else if (NumberOfData == 1 && Flag == 1){
					fprintf(fpWriteFirstLoc, "%lu \n", Location);
				        Flag = 0;
				}
				if(Flag2==1){
					fprintf(fpWriteFirstLocChr, "%lu \n", Location);
					Flag2=0;
				}
				Map[NumberOfActualData] = (Value*1.0) /100;
			        ++NumberOfData;
				++NumberOfActualData;
				if(Value < Min_Value)
			    	Min_Value = Value;
				if(Value > Max_Value)
			    	Max_Value = Value;
				SumValue = SumValue + ((Value*1.0) /100);
				//SumSquaredValue = SumSquaredValue + ((Value * Value *1.00)/10000);

		   }
		   else if (tmp >='a' && tmp <='z'){
			   ungetc(tmp,fpRead);
			   fgets(str,sizeof(str),fpRead);
			   fputs(str,fpWrite);
			   if(strcmp(str,Prestr) && strcmp(Prestr,"empty")){
				   //new
				        char *tmpChrmName0 = strstr(str, "chrom=");
				   		if (tmpChrmName0 == NULL){
				   		   printf("Wrong annotation line: %s, must contain chromosome name!\n", str);
				   		    exit(1);
				   		 }

				   		 char tmp0[6];
						 memset(tmp0,0,6*sizeof(char));
				   		  j=6;
						 while (tmpChrmName0[j]!=' ' && j<14){
						 	tmp0[j-6]=tmpChrmName0[j];
						 	j++;
				         }

				            char *tmpChrmName1 = strstr(Prestr, "chrom=");
				   		    if (tmpChrmName1 == NULL ){
				   		       printf("Wrong annotation line: %s, must contain chromosome name!\n", Prestr);
				   			    exit(1);
				              }
				           char tmp1[6];
				            memset(tmp1,0,6*sizeof(char));
					   j=6;
					   while (tmpChrmName1[j]!=' ' && j<14){
					   	tmp1[j-6]=tmpChrmName1[j];
					   	j++;
				           }
				   if( strcmp(tmp0,tmp1)){
				    	fprintf(fpWriteBlockNumber, "%ld \n", NumberOfBlocks );
				        Flag2 =1;
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
				       ++ChrmCount;
				       }
			          strcpy(Prestr,str);
			          //if(NumberOfData == 0) {
				         // Flag=1;
			           // }
			         ++NumberOfData;
			   }
			   else if(strcmp(str,Prestr) && !strcmp(Prestr,"empty") ){
                                   fprintf(fpWriteBlockNumber, "%ld \n", NumberOfBlocks );
				   Flag2 =1;
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
				    ++ChrmCount;
                                   strcpy(Prestr,str);
			           if(NumberOfData == 0){
				      Flag=1;
			            }
			          ++NumberOfData;
			      }

			 }
           }
		++NumberOfBlocks;
		fclose(fpWrite);
		//fclose(fpWriteExt);

		double Mean = 0;
		double std = 0;
		Mean= SumValue/NumberOfActualData;
		double Variance=0;
		int index;
		for(index=0;index<NumberOfActualData;++index){
			Variance = Variance + (Map[index]-Mean)*(Map[index]-Mean);
		}
		Variance = Variance/(NumberOfActualData-1);
		std= sqrt(Variance);


		strcpy(FileName, argv[1]);
	        strcat(FileName, "Summary");
	        FILE *fpWriteSummary = fopen(FileName, "w");
	        if (fpWriteSummary == NULL) {
		    fprintf(stderr, "Can't open file %s!\n",FileName);
		     exit(1);
	     }
		fprintf(fpWriteSummary, "%.3f %.3f %.4lf %.4lf ", (Min_Value *1.00)/100, (Max_Value *1.00)/100, Mean, std);
		//fclose(fpWriteSummary);

         /* strcpy(FileName, argv[1]);
		   strcat(FileName, "MaxPeak");
		  	FILE *fpWriteMax_Peak = fopen(FileName, "a");
		  	if (fpWriteMax_Peak == NULL) {
		  	         fprintf(stderr, "Can't open file %s!\n",FileName);
		  		     exit(1);
	     }
          fprintf(fpWriteMax_Peak,"%.3f ", (Max_Value *1.00)/1000);
          fclose(fpWriteMax_Peak);*/
		  DiffCoding2L(argv);

		   float Min_Peak;
		   float Max_Peak;
		   strcpy(FileName,argv[1]);
		   strcat(FileName,"Jump");
		   FILE *fpJump = fopen(FileName,"r");
		   if (fpJump == NULL) {
		   	   fprintf(stderr,"Can't open output file!\n");
		   		exit(1);
		    }
		    fscanf(fpJump, "%f %f \n ", &Min_Peak, &Max_Peak);
                    fclose(fpJump);
                    fprintf(fpWriteSummary, "%.3f %.3f  \n", Min_Peak, Max_Peak);
		    fclose(fpWriteSummary);
		    getseq(argv);
		    CountVal(argv);
		   ValMatlab(argv);
                   RunLength(argv);
                   getseq2(argv);
                   CountLoc1(argv);
		   Loc1Matlab(argv);
                   CountLoc2(argv);
		   Loc2Matlab(argv);
		   encoderRA(argv);
		   fmergeRA(2,argv,-1);

	          strcpy(FileName, argv[1]);
	          strcat(FileName, "CodeBlock");
		  fp_2=fopen(FileName , "r");
		  sz=fsize(fp_2);
		  buffer = (char*)malloc(sz*sizeof(char));
	          if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
		  fread(buffer,sizeof(char),sz,fp_2);
		  fwrite(buffer,sizeof(char),sz,fpWriteCodedBlocks);
		  fclose(fp_2);
		  free(buffer);
		  fprintf(fpWriteSizeCodedBlock, "%ld ", sz);
	}
	fclose(fpRead);
	fclose(fpWriteFirstLocChr);
	fclose(fpWriteFirstLoc);
	fclose(fpWriteBlockNumber);
	fclose(fpWriteCodedBlocks);
	fclose(fpWriteSizeCodedBlock);

	int i;
	strcpy(FileName,argv[1]);
	strcat(FileName,"AllChrmName");
	FILE *fpName = fopen(FileName,"w");
	if (fpName == NULL) {
		fprintf(stderr,"Can't open output file!\n");
		exit(1);
	}
    for (i=0; i<ChrmCount; i++){
		fprintf(fpName,"%s ",&ChrmNames[8*i]);
		fprintf(fpName,"\n");
    }
	fclose(fpName);


	strcpy(FileName, argv[2]);

	FILE *fpswig=fopen(FileName,"w");


	strcpy(FileName, argv[1]);
	strcat(FileName,"fpFirstLoc");
	FILE *fpLoc=fopen(FileName,"r");
	sz=fsize(fpLoc);
	fprintf(fpswig, "%ld ", sz);
	buffer = (char*)malloc(sz*sizeof(char));
	if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
	fread(buffer,sizeof(char),sz,fpLoc);
	fwrite(buffer,sizeof(char),sz,fpswig);
        fclose(fpLoc);
	free(buffer);


	strcpy(FileName, argv[1]);
	strcat(FileName,"fpFirstLocChr");
	FILE *fpLocChr=fopen(FileName,"r");
	sz=fsize(fpLocChr);
	fprintf(fpswig, "%ld ", sz);
	buffer = (char*)malloc(sz*sizeof(char));
	if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
	fread(buffer,sizeof(char),sz,fpLocChr);
	fwrite(buffer,sizeof(char),sz,fpswig);
        fclose(fpLocChr);
	free(buffer);

	strcpy(FileName, argv[1]);
	strcat(FileName,"AllChrmName");
	FILE *fpAllName=fopen(FileName,"r");
	sz=fsize(fpAllName);
	fprintf(fpswig, "%ld ", sz);
	buffer = (char*)malloc(sz*sizeof(char));
	if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
	fread(buffer,sizeof(char),sz,fpAllName);
	fwrite(buffer,sizeof(char),sz,fpswig);
        fclose(fpAllName);
	free(buffer);

	strcpy(FileName, argv[1]);
	strcat(FileName,"BlockNumber");
	FILE *fpBN=fopen(FileName,"r");
	sz=fsize(fpBN);
	fprintf(fpswig, "%ld ", sz);
	buffer = (char*)malloc(sz*sizeof(char));
	if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
	fread(buffer,sizeof(char),sz,fpBN);
	fwrite(buffer,sizeof(char),sz,fpswig);
        fclose(fpBN);
	free(buffer);

	strcpy(FileName, argv[1]);
	strcat(FileName,"SizeCodedBlock");
	FILE *fpSCB=fopen(FileName,"r");
	sz=fsize(fpSCB);
	fprintf(fpswig, "%ld ", sz);
	buffer = (char*)malloc(sz*sizeof(char));
	if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
	fread(buffer,sizeof(char),sz,fpSCB);
	fwrite(buffer,sizeof(char),sz,fpswig);
        fclose(fpSCB);
	free(buffer);



	/*strcpy(FileName, argv[1]);
	strcat(FileName,"MaxPeak");
	FILE *fpPeak=fopen(FileName,"r");
	sz=fsize(fpPeak);
	fprintf(fpswig, "%ld ", sz);
	buffer = (char*)malloc(sz*sizeof(char));
	fread(buffer,sizeof(char),sz,fpPeak);
	fwrite(buffer,sizeof(char),sz,fpswig);
	fclose(fpPeak);
	free(buffer);

	strcpy(FileName, argv[1]);
	strcat(FileName,"Jump");
	FILE *fpJump=fopen(FileName,"r");
	sz=fsize(fpJump);
	fprintf(fpswig, "%ld ", sz);
	buffer = (char*)malloc(sz*sizeof(char));
	fread(buffer,sizeof(char),sz,fpJump);
	fwrite(buffer,sizeof(char),sz,fpswig);
	fclose(fpJump);
	free(buffer);*/


        strcpy(FileName, argv[1]);
	strcat(FileName,"CodedBlocks");
	FILE *fpCB=fopen(FileName,"r");
	sz=fsize(fpCB);
	fprintf(fpswig, "%ld ", sz);
	buffer = (char*)malloc(sz*sizeof(char));
	if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
	fread(buffer,sizeof(char),sz,fpCB);
	fwrite(buffer,sizeof(char),sz,fpswig);
        fclose(fpCB);
	free(buffer);
	fclose(fpswig);


   char T[28][40];//files to delete
   char Removelist[1][28][40]={
   		{"AllChrmName","BlockNumber","Summary","CodeBlock", "CodedBlocks", "fpFirstLoc", "fpFirstLocChr", "SizeCodedBlock","DiffLocSeq2","DiffValSeq","DiffLocSeqMatlab1", "DiffLocSeqMatlab2","DiffValSeqMatlab", "ExceedLoc","ExceedVal","DiffLoc1","DiffLoc2","ChrmName","SpanName","DiffVal","DiffValSeqMatlabCode","DiffLocSeqMatlab2Code","DiffLocSeqMatlab1Code", "Mult1000", "DiffLocSeq","DiffLocRunLength", "Jump"},
	};

     for (i=0; i<28; i++){
		for (j=0; j<40; j++){
			T[i][j] = Removelist[0][i][j];
		}
	}

   strcpy(FileName, argv[1]);
   i=0;
	while (i<28 && T[i][0]){
		strcpy(Removelist[0][i],FileName);
		strcat(Removelist[0][i],T[i]);
		remove(Removelist[0][i]);
		//printf("file %s removed\n",d[i]);
		i++;
	}
  strcpy(FileName, argv[1]);
  strcat(FileName, "Mult100");
  remove(FileName);

return 1;
}
