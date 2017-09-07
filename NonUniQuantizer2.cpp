int NonUniQuantizer2 (char *argv[])
{

	char tmp;
	char str[200];
        char tmpFileName[400];
        fpos_t position1;
        long unsigned int Location=0;
	float Exp=0;
	int flag=0;
	long unsigned int PreLocation = 0;
	char Prestr[200];
	strcpy(Prestr,"empty");
	long unsigned int PreExp = 0;
        int i;



	char FileName[400];//name of processed Wig file 1
	strcpy(FileName, argv[1]);

	FILE *fpRead = fopen(FileName, "r");
	if (fpRead == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}

        char stri[100];
        long int TotalNumbers=10;
	float Max=0;
	float Min=0;
	strcpy(FileName, argv[1]);
        strcat(FileName, "Maximum");
	FILE *fpReadMax;
	fpReadMax = fopen(FileName, "r");
	if (fpReadMax == NULL) {
		fprintf(stderr, "Can't open input file %s!\n",FileName);
		exit(1);
	}
	fgets(stri, 100, fpReadMax);
        //puts(stri);

	fscanf(fpReadMax,"%ld %f %f", &TotalNumbers, &Max, &Min);
        //printf("%ld %f %f", TotalNumbers, Max, Min);
        fclose(fpReadMax);
       

	strcpy(FileName, argv[1]);
	strcat(FileName,"Non_UniformQuan");
	FILE *fpWrite = fopen(FileName, "w");
	if (fpWrite == NULL) {
		fprintf(stderr, "Can't open file %s!\n",FileName);
		exit(1);
	}
        double Quantized2 = 0;
        float Threshold = 0.7 * Max;
        double SetFixValue = 0.8 * Max;
        //printf(" %f %f", SetFixValue, Max);

          float d1=0.25;
          float d2=0.25;
          float d3=0.33;
          float d4=0.33;
          float d5=0.33;
          float d6 = 11.3; //d6 = (Threshold - 5) /(M_1+M_2+...+M_5)


       while(!feof(fpRead)){
	   tmp = fgetc(fpRead);
	   if  (tmp >= '0' && tmp <= '9'){
		ungetc(tmp,fpRead);
	        fscanf(fpRead,"%lu %f\n", &Location,&Exp);
		if(Exp>0 && Exp<1.0)
		      Quantized2=d1*floor(Exp/d1)+ d1/2;
		else if (Exp>=1.0 && Exp<2.0)
		      Quantized2=d2*floor(Exp/d2)+ d2/2;
		else if (Exp>=2.0 && Exp<3.0)
		      Quantized2=d3*floor(Exp/d3)+ d3/2;
		else if (Exp>=3.0 && Exp<4.0)
		      Quantized2=d4*floor(Exp/d4)+ d4/2;
		else if (Exp>=4.0 && Exp<5.0)
		      Quantized2=d5*floor(Exp/d5)+ d5/2;
		else if(Exp>=5.0 && Exp <=Threshold)
		      Quantized2=d6*floor(Exp/d6)+ d6/2;
                 else
                      Quantized2 = SetFixValue;
		  fprintf(fpWrite, "%lu \t %.2f\n", Location, Quantized2);
	           }
	      else{
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










