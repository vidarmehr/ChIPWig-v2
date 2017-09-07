
int Multiply1000RA(char * argv[])
{

char FileName[400];//name of processed Wig file
long unsigned int Location=0;
int Coeff = 100;
char tmp;
char str[1000];  //annotation line
char LocValue[100];
double Value=0;
long unsigned int IntValue=0;

strcpy(FileName, argv[1]);
//strcat(FileName,"New")
FILE *fp;
fp = fopen(FileName, "r");
if (fp == NULL) {
		fprintf(stderr, "Can't open input file %s!\n",FileName);
		exit(1);
	}
strcpy(FileName, argv[1]);
strcat(FileName, "Mult1000");
FILE *fpWrite;
fpWrite = fopen(FileName, "w");
if (fpWrite == NULL) {
		fprintf(stderr, "Can't open input file %s!\n",FileName);
		exit(1);
	}
int i;
long unsigned int C1=0;

	 /*strcpy(FileName, argv[1]);
		strcat(FileName, "Extra");
		FILE *fpWriteExt;
		fpWriteExt = fopen(FileName, "w");
		if (fpWriteExt == NULL) {
			fprintf(stderr, "Can't open input file %s!\n",FileName);
			exit(1);
	}*/

while (!feof(fp)){
		tmp = fgetc(fp);
		if  (tmp >= '0' && tmp <= '9'){
			ungetc(tmp,fp);
			fscanf(fp,"%lu %lf\n", &Location,&Value);
			IntValue = (int) (ceil)(10000*Value);
			/*C1= IntValue/10;

                   if(IntValue % 10 != 0 && C1 % 10 != 0  ){
					fprintf(fpWriteExt,"%.4f ",Value );
				    printf(fpWrite, "%lu %d\n", Location,0);
					}
					else{*/
			IntValue= IntValue/10;
			fprintf(fpWrite, "%lu %lu\n", Location,IntValue);
						//}
		}
		else{
			ungetc(tmp,fp);
			fgets(str,sizeof(str),fp);
			fputs(str,fpWrite);
		}
 }
fclose(fp);
fclose(fpWrite);
//fclose(fpWriteExt);
return 1;
}