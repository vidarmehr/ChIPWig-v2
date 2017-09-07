int ProbabilityDist(char *argv[])
 {

        char FileName[400];//name of processed Wig file
        long unsigned int Location=0;
	int Coeff = 100;
	char tmp;
	char str[1000];  //annotation line
	long unsigned int Value=0;
	unsigned int i=0;


	 int Nd=20;
         unsigned int SetMaxDiff = exp2(Nd);
	 float ProbabilityDistr[SetMaxDiff]; //maps each consecutive integer to the actual alphabet
	  memset(ProbabilityDistr,0,SetMaxDiff*sizeof(float));



	strcpy(FileName, argv[1]);
	strcat(FileName, "RecordVal");
	FILE *fpRead;
	fpRead = fopen(FileName, "r");
	if (fpRead == NULL) {
		fprintf(stderr, "Can't open input file %s!\n",FileName);
		exit(1);
	}

        float k;
        unsigned int m,j;
        strcpy(FileName, argv[1]);
	strcat(FileName, "Prob");
	FILE *fpWrite;
	fpWrite = fopen(FileName, "w");
	if (fpWrite == NULL) {
		fprintf(stderr, "Can't open input file %s!\n",FileName);
		exit(1);
	}
	fscanf(fpRead,"%u %u %f\n", &m, &j, &k);
	ProbabilityDistr [0] = k;
	fprintf(fpWrite,"%u %u %.8f %.8f\n",m, j, k, ProbabilityDistr[0]);
   // for(i=1;i<SetMaxDiff && !feof(fpRead);++i){
	   while(!feof(fpRead)){
		++i;
	       fscanf(fpRead,"%u %u %f\n", &m, &j, &k);
	       ProbabilityDistr [i] = ProbabilityDistr [i-1] + k;
	       fprintf(fpWrite,"%u %u %.8f %.8f\n",m, j, k, ProbabilityDistr[i]);
	    }

fclose(fpWrite);
fclose(fpRead);
strcpy(FileName, argv[1]);
strcat(FileName, "RecordVal");
remove(FileName);

 return 1;
}
