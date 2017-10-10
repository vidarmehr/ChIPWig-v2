/*split file for decompress
 * options:
 * 0--regular
 //* 1--lpaq not used
 * 2--random access
 */


int fsplitRA(int *opt, char * argv[]) {

	char FileName[400];//name of processed Wig file

	clock_t start = clock();
        FILE *fpResult=fopen("result","a");
	if (fpResult == NULL) {
		fprintf(stderr,"Can't open output result file!\n");
		exit(1);
	}
	fprintf(fpResult,"=================\nfsplit.cpp start!\n");

	strcpy(FileName, argv[1]);


	int N=21;

	char Type[21][40];
	char c[21][10000];
	FILE *fp[21];
	FILE *fpout;
	long int sz[21];
	int i,j,tmp;
	char *buffer;

	//output file
	strcpy(FileName, argv[1]);
	strcat(FileName,"Block");
	i=0;
	strcpy(c[i],FileName);
	fpout = fopen(c[0], "r");
	if (fpout  == NULL) {
		fprintf(stderr, "Can't open file %s!\n",c[0]);
		exit(1);
	}

	fscanf(fpout,"%d ",opt);
	//printf("%d ", *opt);

	for (i=0; i<21; i++){
		for (j=0; j<40; j++){
			Type[i][j] = list[*opt][i][j];
		}
	}

	strcpy(FileName, argv[1]);
	i=0;
	while (i<21 && Type[i][0]){
		strcpy(c[i],FileName);
		strcat(c[i],Type[i]);
		i++;
	}
	N = i;


	//file sizes in first line of output file
	for (i=1; i<N; i++){
		fp[i] = fopen(c[i], "w");
		if (fp[i] == NULL) {
			fprintf(stderr, "Can't open file %s!\n",c[i]);
			exit(1);
		}
		//file size
		fscanf(fpout,"%ld ",&sz[i]);
	}


	//copy every file
	for (i=1; i<N; i++){
		buffer = (char*)malloc(sz[i]*sizeof(char));
		if(buffer == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	       }
		fread(buffer,sizeof(char),sz[i],fpout);
		fwrite(buffer,sizeof(char),sz[i],fp[i]);
		fclose(fp[i]);
		free(buffer);
	}
	fclose(fpout);


	clock_t end = clock();
	fprintf(fpResult,"fsplit takes %2.3f sec.\n", (double)(end - start)/CLOCKS_PER_SEC);


	return 1;

}


