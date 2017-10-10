/*
 * encoder.cpp
 * read a file and compress using rangemapper by bits
 *
 *
 *  Created on: Jun 28, 2014
 *      Author: Zhiying Wang
        Modified by Vida Ravanmehr Nov. 2016
 */



int encoderRA(char * argv[]) {

	char FileName[200];//name of processed Wig file
	char Type[40];
	char T[40];

	SPAM(("=================\nencoder.cpp start!\n"));

	strcpy(FileName, argv[1]);


	char tmpFileName[400];
	//parameters that can be changed for testing
	//the RANGE_SIZE_IN_BITS depends on your alphabet size
	int alphabet_size;//256; //Please notice the size of the alphabet.
	 int data_size;// = 39432012;
	int RANGE_SIZE_IN_BITS=30;
	//ranges_in_bits<32, it cannot be more than sizeof(int), which is 4 bytes=32 bits, otherwise makeRanges does not work
	//range_in_bits is the number of bits used to represent the probabilities
	// L=64-range_in_bits is the number of bits used to store the current range of low and high
	//Need for any probability p of a symbol, p>= 1/2^(L-3). So L-3>=range_in_bits, or range_in_bits<=30
	 int *data;
	double entropy;
	int expected_size;
	//int cm_size;
	 int *cm;
	int actual_size;
	//bool isOK;
	long unsigned int i=0;
	//int j=0;
	int tmp;
	FILE *fpDiffSeqMatlab;
	//long int underflow; //count number of times low and high are too close
    float totaltime=0;

	//write to summary result file
	FILE *fpResult=fopen("result","a");
	if (fpResult == NULL) {
		fprintf(stderr,"Can't open output result file!\n");
		exit(1);
	}

	//start encoding
 //clock_t start_encoding = clock();
       for (int type=0; type<3; type++){
		   clock_t start_encoding = clock();
			if (type==0){
			strcpy(Type,"DiffLocSeqMatlab1");
			strcpy(T,"DiffLoc1");
			//alphabet_size = 6134;
		}
		else if (type==1)
		{
			strcpy(Type,"DiffLocSeqMatlab2");
			strcpy(T,"DiffLoc2");
			//alphabet_size = 6134;
		}
		else
		{
			strcpy(Type,"DiffValSeqMatlab");
			strcpy(T,"DiffVal");
			//alphabet_size = 67955;
		}


		//load data from file
		strcpy(tmpFileName,FileName);
		strcat(tmpFileName,Type);
		fpDiffSeqMatlab = fopen(tmpFileName, "r");
		if (fpDiffSeqMatlab  == NULL) {
			fprintf(stderr, "Can't open file %s!\n",tmpFileName);
			exit(1);
		}


		alphabet_size = 0;
		data_size=1000000000;
		data = ( int*)malloc(data_size * sizeof(int));
	       if(data == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	       }
		i=0;
		while (!feof(fpDiffSeqMatlab) && i<data_size){
			fscanf(fpDiffSeqMatlab,"%d ", &data[i]);
			/*if (data[i]<0){
				printf("Wrong range! data[%d]=%d\n",i,data[i]);
				exit(1);
			}
			if (data[i]+1>alphabet_size)
				alphabet_size = data[i]+1;*/
			i++;
		}
		if (i==data_size){
			printf("Too large data set! Need to increase data_size!\n");
			exit(1);
		}
		data_size = i;



		entropy = calculate_entropy(data,data_size);
		expected_size = (int)(entropy * (double)(data_size) / 8.0);


		//printf("\n--------\ndata[3]=%d,data[5]=%d,data[6]=%d data_size=%d\n",data[3],data[5],data[6],data_size);

		//make ranges for data
		//printf("start makeranges\n");
		//load count table file
		strcpy(tmpFileName,FileName);
		strcat(tmpFileName,T);
		FILE *fpDiff = fopen(tmpFileName, "r");
		if (fpDiff  == NULL) {
			fprintf(stderr, "Can't open file %s!\n",tmpFileName);
			exit(1);
		}
		absize_txt(&alphabet_size,fpDiff);
		cm = ( int*)malloc((alphabet_size+2)*sizeof( int));
	       if(cm == NULL){
		       printf("Error! Allocation was not successful.\n");
		       exit(1);
	       }
		makeRanges_txt(cm, alphabet_size, RANGE_SIZE_IN_BITS,fpDiff);
		fclose(fpDiff);


		//encode
		//int extra_folds = 2;
         int extra_folds = 100;

		g_buffer = (unsigned char*)malloc(expected_size * extra_folds);
		//memset(g_buffer,0x00,expected_size * extra_folds);
		current_byte = 0;
		TMPWRITE = 0x00;
		TMPWRITE_COUNT = 7;
		//underflow = 0;

		RangeMapper* rm_encode = new RangeMapper(RANGE_SIZE_IN_BITS);
		for (i=0; i<data_size; ++i) {
			rm_encode->encodeRange(cm[data[i]], cm[data[i]+1]);
		}
		rm_encode->encodeRange(cm[alphabet_size], cm[alphabet_size+1]); //end of data marker
		rm_encode->flush();
		if (current_byte>expected_size * extra_folds){
			printf("Code longer than expected! Increase extra_folds in encoderRA.cpp!\n");
			exit(1);
		}
		delete rm_encode;
		actual_size = current_byte;
		/*printf("RANGE_SIZE_IN_BITS=%d, Entropy=%f,data_size=%d, Expected size %d\n", RANGE_SIZE_IN_BITS, entropy, data_size, expected_size);
		printf("Actual size   %d, \n", actual_size);
		*/

		//write to a file
		strcpy(tmpFileName,FileName);
		strcat(tmpFileName,Type);
		strcat(tmpFileName,"Code");
		FILE *fpCode = fopen(tmpFileName, "wb");
		if (fpCode  == NULL) {
			fprintf(stderr, "Can't open file %s!\n",tmpFileName);
			exit(1);
		}
		fwrite(g_buffer,1,actual_size,fpCode); //binary file write
		/*for (j=0; j<10; j++)
			printf("%hhX ",g_buffer[j]);
		printf("\nabove is g_buffer written to file\n");*/


		free(g_buffer);
		free(cm);
		free(data);
		fclose(fpCode);
		fclose(fpDiffSeqMatlab);
		//end encoding

		clock_t end_encoding = clock();

		fprintf(fpResult,"\n//encoder.cpp//File is %s%s\n", FileName, Type);
		fprintf(fpResult,"Time for encoding %2.3f sec.\n", (double)(end_encoding - start_encoding)/CLOCKS_PER_SEC);
		totaltime= totaltime + (double)(end_encoding - start_encoding)/CLOCKS_PER_SEC;
		fprintf(fpResult,"Diff Seq length is %d, entropy is %2.3f, non-zero-count alphabet_size is %d, \
		RANGE_SIZE_IN_BITS is %d.\n",\
		data_size, entropy, alphabet_size,RANGE_SIZE_IN_BITS);
		fprintf(fpResult,"Expected size %d bytes\nActual size   %d bytes.\n", expected_size,actual_size);
	}
	fprintf(fpResult,"Total Encoding time= %f\n", totaltime);
	fclose(fpResult);

	return 1;

}




