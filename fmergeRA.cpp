/*
 * merge files for compression
 * options:
 * 0--regular
 //* 1--lpaq
 * 2--random access
 //* 3--random access with parallel, but in this case opt=2 is written to compressed file
 */


int fmergeRA(int opt, char * argv[], int nproc) {
	char FileName[200];//name of processed Wig file

	clock_t start = clock();
	//SPAM(("=================\nfmerge.cpp start! opt=%d\n",opt));
	FILE *fpResult=fopen("result","a");
	if (fpResult == NULL) {
		fprintf(stderr,"Can't open output result file!\n");
		exit(1);
	}
	strcpy(FileName, argv[1]);


	int N=20;
	//list of files to delete given option index
	char dlist[4][20][40]={
		{"DiffLocSeq1", "DiffLocSeq2","DiffValSeq","DiffLocSeqMatlab1", "DiffLocSeqMatlab2","DiffValSeqMatlab"},
		{"DiffSeq","LenDiffSeq","DiffSeqMatlab","LenDiffSeqMatlab"},
		{"DiffLocSeq1", "DiffLocSeq2","DiffValSeq","DiffLocSeqMatlab1", "DiffLocSeqMatlab2","DiffValSeqMatlab"},
		{"DiffSeq","LenDiffSeq","DiffSeqMatlab","LenDiffSeqMatlab"},
		//{"DiffSeq","LenDiffSeq","DiffSeqMatlab","LenDiffSeqMatlab"},
	};

	char Type[21][40];//files to merge
	char T[21][40];//files to delete
	char c[21][10000];
	char d[21][10000];
	FILE *fp[21];
	FILE *fpout;
	long int sz[21];
	int i,j;
	char *buffer;
	char str[2],tmpchar[1000];

	for (i=0; i<21; i++){
		for (j=0; j<40; j++){
			Type[i][j] = list[opt][i][j];
			T[i][j] = dlist[opt][i][j];
		}
	}
	i=1;
	while (i<21 && Type[i][0]){
		strcpy(c[i],FileName);
		strcat(c[i],Type[i]);
		i++;
	}
	N = i;
	//printf("N=%d\n",N);

	//output file
	strcpy(c[0],argv[1]);
	strcat(c[0],"CodeBlock");
	fpout = fopen(c[0], "w");
	if (fpout  == NULL) {
		fprintf(stderr, "Can't open file %s!\n",c[0]);
		exit(1);
	}

	//compression option
	if (opt == 3)
		fprintf(fpout,"2 "); //prll is same as random access
	else
		fprintf(fpout,"%d ",opt);

	/*switch (opt){
		case 2://random access
			fprintf(fpout,"%d ",BlockSize);
			//fprintf(fpout,"%d ",int(log10(SetFloatSize)));
			break;
		/*case 3://random access and parallel
			fmergeadd(nproc,argv); //merge block address
			for (i=1;i<N;i++){//merge sub files
				if (i<2 || i>8) //except BlockAdd and Diff (Count) files
					fmergesub(nproc,c[i]);
			}
			fprintf(fpout,"%d ",BlockSize);
			//fprintf(fpout,"%d ",int(log10(SetFloatSize)));
			break;*/
	//}
	//file sizes in first line of output file
	for (i=1; i<N; i++){
		fp[i] = fopen(c[i], "r");
		if (fp[i] == NULL) {
			fprintf(stderr, "Can't open file %s!\n",c[i]);
			exit(1);
		}
		//file size
		sz[i]=fsize(fp[i]);
		fprintf(fpout,"%ld ",sz[i]);
		//printf("size i %ld\n",sz[i]);
	}

	//copy every file
	for (i=1; i<N; i++){
		buffer = (char*)malloc(sz[i]*sizeof(char));
		if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	       }
		fread(buffer,sizeof(char),sz[i],fp[i]);
		fwrite(buffer,sizeof(char),sz[i],fpout);
		fclose(fp[i]);
		free(buffer);
		//remove(c[i]);
	}
	//get compressed file size
	rewind(fpout);
	sz[0]=fsize(fpout);
	fprintf(fpResult,"output %s\nsize %ld\n",c[0],sz[0]);
	fclose(fpout);

	//remove useless file
	i=0;
	while (i<21 && T[i][0]){
		strcpy(d[i],FileName);
		strcat(d[i],T[i]);
		if (opt==3 || opt==5){
			for (j=0;j<nproc;j++){
				strcpy(tmpchar,d[i]);
				sprintf(str,"%02d",j);
				strcat(tmpchar,str);
				remove(tmpchar);
			}
		}
		else
			remove(d[i]);
		//printf("file %s removed\n",d[i]);
		i++;
	}

	clock_t end = clock();
	fprintf(fpResult,"fmerge takes %2.3f sec.\n", (double)(end - start)/CLOCKS_PER_SEC);

	fclose(fpResult);
	return 0;

}
