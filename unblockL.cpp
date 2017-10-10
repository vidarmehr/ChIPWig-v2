int unblockL(char *argv[])
{

	int i, N;
	long int sz;
	char * buffer;
	char FileName[200];
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
	if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
	fread(buffer,sizeof(char),sz,fpRead);
	fwrite(buffer,sizeof(char),sz,fpWriteLocStart);
        fclose(fpWriteLocStart);
	free(buffer);


        strcpy(FileName,argv[1]);
	strcat(FileName,"fpFirstLocChr");
	fpWriteFirstLocChr=fopen(FileName,"w");
	if (fpWriteFirstLocChr == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}
	fscanf(fpRead,"%ld ",&sz);
	buffer = (char*)malloc(sz*sizeof(char));
	if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
	fread(buffer,sizeof(char),sz,fpRead);
	fwrite(buffer,sizeof(char),sz,fpWriteFirstLocChr);
        fclose(fpWriteFirstLocChr);
	free(buffer);

	strcpy(FileName,argv[1]);
	strcat(FileName,"AllChrmName");
	fpWriteAllName=fopen(FileName,"w");
	if (fpWriteAllName == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}
	fscanf(fpRead,"%ld ",&sz);
	buffer = (char*)malloc(sz*sizeof(char));
	if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
	fread(buffer,sizeof(char),sz,fpRead);
	fwrite(buffer,sizeof(char),sz,fpWriteAllName);
        fclose(fpWriteAllName);
	free(buffer);


	strcpy(FileName,argv[1]);
	strcat(FileName,"BlockNumber");
	fpWriteBlockNumber=fopen(FileName,"w");
	if (fpWriteBlockNumber == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}
	fscanf(fpRead,"%ld ",&sz);
	buffer = (char*)malloc(sz*sizeof(char));
	if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
	fread(buffer,sizeof(char),sz,fpRead);
	fwrite(buffer,sizeof(char),sz,fpWriteBlockNumber);
        fclose(fpWriteBlockNumber);
	free(buffer);

	strcpy(FileName,argv[1]);
	strcat(FileName,"SizeCodedBlock");
	fpWriteSizeCodedBlock=fopen(FileName,"w");
	 if (fpWriteSizeCodedBlock == NULL) {
	  			fprintf(stderr, "Can't open file %s!\n",FileName);
	  			exit(1);
	  		}
	 fscanf(fpRead,"%ld ",&sz);
	 buffer = (char*)malloc(sz*sizeof(char));
	if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
	 fread(buffer,sizeof(char),sz,fpRead);
	 fwrite(buffer,sizeof(char),sz,fpWriteSizeCodedBlock);
	 fclose(fpWriteSizeCodedBlock);
	 free(buffer);

	/* strcpy(FileName,argv[1]);
	 strcat(FileName,"MaxPeak");
	 FILE *fpWriteMax_Peak=fopen(FileName,"w");
	 if (fpWriteMax_Peak == NULL) {
	  			fprintf(stderr, "Can't open file %s!\n",FileName);
	  			exit(1);
	  		}
	  	//file size
	  fscanf(fpRead,"%ld ",&sz);
	  buffer = (char*)malloc(sz*sizeof(char));
	  fread(buffer,sizeof(char),sz,fpRead);
	  fwrite(buffer,sizeof(char),sz,fpWriteMax_Peak);
	  fclose(fpWriteMax_Peak);
	  free(buffer);

	  strcpy(FileName,argv[1]);
	  strcat(FileName,"Jump");
	  FILE *fpWriteJump=fopen(FileName,"w");
	  if (fpWriteJump == NULL) {
	  			fprintf(stderr, "Can't open file %s!\n",FileName);
	  			exit(1);
	  			}
	  					//file size
	  fscanf(fpRead,"%ld ",&sz);
	  buffer = (char*)malloc(sz*sizeof(char));
	  fread(buffer,sizeof(char),sz,fpRead);
	  fwrite(buffer,sizeof(char),sz,fpWriteJump);
	  fclose(fpWriteJump);
	  free(buffer);*/

	  strcpy(FileName,argv[1]);
	  strcat(FileName,"CodedBlocks");
	  fpWriteCodedBlocks=fopen(FileName,"w");
	  if (fpWriteCodedBlocks == NULL) {
	  			fprintf(stderr, "Can't open file %s!\n",FileName);
	  			exit(1);
	  		}
	  fscanf(fpRead,"%ld ",&sz);
	  buffer = (char*)malloc(sz*sizeof(char));
	 if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
	  fread(buffer,sizeof(char),sz,fpRead);
	  fwrite(buffer,sizeof(char),sz,fpWriteCodedBlocks);
	  fclose(fpWriteCodedBlocks);
	  free(buffer);

	  fclose(fpRead);


	FILE *fpReadCodedBlocks;
	strcpy(FileName,argv[1]);
	strcat(FileName,"CodedBlocks");
	fpReadCodedBlocks=fopen(FileName,"r");
	if (fpReadCodedBlocks == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}

		strcpy(FileName,argv[1]);
			  	strcat(FileName,"SizeCodedBlock");
			  	FILE *fpReadSizeBlock=fopen(FileName,"r");
			  	if (fpReadSizeBlock == NULL) {
			  			fprintf(stderr, "Can't open file %s!\n",FileName);
			  			exit(1);
	  		}


	FILE *fpWriteWig;
	strcpy(FileName,argv[2]);
	fpWriteWig=fopen(FileName,"w");
	if (fpWriteWig == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}
		//fclose(fpRead);

	while(!feof(fpReadSizeBlock)){
		fscanf(fpReadSizeBlock, "%ld ", &sz);
		buffer = (char*)malloc(sz*sizeof(char));
		if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
	    fread(buffer,sizeof(char),sz,fpReadCodedBlocks);
		FILE *fpWriteBlock;
	     strcpy(FileName,argv[1]);
	     strcat(FileName,"Block");
	     fpWriteBlock=fopen(FileName,"w");
	    if (fpWriteBlock == NULL) {
			fprintf(stderr, "Can't open file %s!\n",FileName);
			exit(1);
		}
	    fwrite(buffer,sizeof(char),sz,fpWriteBlock);
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
	        to_wig_LossyRA(argv);

		FILE  *fpReadBlock;

		strcpy(FileName,argv[1]);
		strcat(FileName,"Final");
		fpReadBlock=fopen(FileName,"r");
		sz=fsize(fpReadBlock);
		buffer = (char*)malloc(sz*sizeof(char));
		if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	          }
	        fread(buffer,sizeof(char),sz,fpReadBlock);
	        fwrite(buffer,sizeof(char),sz,fpWriteWig);
                fclose(fpReadBlock);
	       free(buffer);
     }
	fclose(fpWriteWig);
	fclose(fpReadSizeBlock);
	fclose(fpReadCodedBlocks);

 char T[34][40];//files to delete
   char Removelist[1][34][40]={
   		{"buffer1","buffer2","DiffLocSeq1", "DiffLocSeq2","DiffValSeq","DiffLocSeqMatlab1", "DiffLocSeqMatlab2","DiffValSeqMatlab","DiffLocSeqMatlab1Decode", "DiffLocSeqMatlab2Decode","DiffValSeqMatlabDecode","ExceedLoc","ExceedVal","DiffLoc1","DiffLoc2","ChrmName","SpanName","DiffLocSeqDe_RunLength","DiffVal","DiffValSeqMatlabCode","DiffLocSeqMatlab2Code","DiffLocSeqMatlab1Code","DCoding2", "AllChrmName", "Block", "BlockNumber", "CodedBlocks","Final","fpFirstLoc","SizeCodedBlock","Summary","fpFirstLocChr"},
	};
	int j;
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
