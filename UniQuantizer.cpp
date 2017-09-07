int UniQuantizer (char *argv[])
{
     char tmp;
     char str[200];
     char tmpFileName[400];
     fpos_t position1;
     long unsigned int Location=0;
	double Exp=0;
	int flag=0;
	long unsigned int PreLocation = 0;
	char Prestr[200];
	strcpy(Prestr,"empty");
	long unsigned int PreExp = 0;
     int i;
  char stri[100];


	char FileName[400];//name of processed Wig file 1
	strcpy(FileName, argv[1]);

	FILE *fpRead = fopen(FileName, "r");
	if (fpRead == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

	long int TotalNumbers;
	float Max;
	float Min;
	strcpy(FileName, argv[1]);
		strcat(FileName, "Maximum");
		FILE *fpReadMax;
		fpReadMax = fopen(FileName, "r");
		if (fpReadMax == NULL) {
			fprintf(stderr, "Can't open input file %s!\n",FileName);
			exit(1);
		}
	fgets(stri, sizeof(stri), fpReadMax);
	fscanf(fpReadMax,"%ld %f %f ", &TotalNumbers, &Max , &Min);
    fclose(fpReadMax);

   // printf("%ld %f %f ", TotalNumbers, Max ,Min);

	strcpy(FileName, argv[1]);
	strcat(FileName,"Uniform_Quantized");
	FILE *fpWrite = fopen(FileName, "w");
	if (fpWrite == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}
     float Quantized2 = 0;
     float d = Threshold/Number_Levels;
     //double FixLargeValue = 0.8 * Max;
double FixLargeValue = 960;
    //double FixLargeValue = 1000.0;

     //printf(" %lf %lf ",Threshold, FixLargeValue);

     if(Threshold > FixLargeValue){
		 printf("Threshold is greater than FixLargeValue, either increase the FixLargeValue or decrease the threshold");
         exit(1);
	 }


	while (!feof(fpRead))
	{
		tmp = fgetc(fpRead);
		if  (tmp >= '0' && tmp <= '9')
		{
			ungetc(tmp,fpRead);
	        fscanf(fpRead,"%lu %lf\n", &Location,&Exp);


	     if(Exp <= Threshold)
	      Quantized2 = d* floor(Exp/d)+ d/2;
	      else
	      Quantized2 = FixLargeValue;

		fprintf(fpWrite, "%lu \t %.2f\n", Location, Quantized2);
		}
		else
		{
			ungetc(tmp,fpRead);
		    fgets(str,sizeof(str),fpRead);
	        strcpy(Prestr,str);
			fputs(str,fpWrite);
		}
	}

	fclose(fpRead);
	fclose(fpWrite);
	return 1;
}










