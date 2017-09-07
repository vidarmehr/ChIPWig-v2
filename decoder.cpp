/*
 * decoder.cpp
 * read a file and compress using rangemapper by bits
 *
 Created by Zhiying Wang June 2014
 Modified by Vida Ravanmehr Nov. 2016
 */


int decoder(char * argv[]) {

	char FileName[400];//name of processed Wig file
	char Type[40];
	char T[40];
	strcpy(FileName, argv[1]);


	char tmpFileName[400];
	//parameters that can be changed for testing
	//the RANGE_SIZE_IN_BITS depends on your alphabet size
	int alphabet_size;//256; //Please notice the size of the alphabet.
	//int data_size;// = 39432012;
	int RANGE_SIZE_IN_BITS=30;
	//ranges_in_bits<32, it cannot be more than sizeof(int), which is 4 bytes=32 bits, otherwise makeRanges does not work
	//range_in_bits is the number of bits used to represent the probabilities
	// L=64-range_in_bits is the number of bits used to store the current range of low and high
	//Need for any probability p of a symbol, p>= 1/2^(L-3). So L-3>=range_in_bits, or range_in_bits<=30
	//int *data;
	//double entropy;
	//int expected_size;
	//int cm_size;
	 int *cm;
	//int actual_size;
	//bool isOK;
	//int i=0;
	//int j=0;
	//long int underflow; //count number of times low and high are too close
    float totaltime=0;

	//write to summary result file
	FILE *fpResult=fopen("result","a");
	if (fpResult == NULL) {
		fprintf(stderr,"Can't open output result file!\n");
		exit(1);
	}

	//start decoding
	fprintf(fpResult,"====================\ndecoder.cpp start!\n");
	for (int type=0; type<=2; type++){

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

		alphabet_size = 0;
		//data_size=100000000;
		//data = (int*)malloc(data_size * sizeof(int));

		//decode
		clock_t start_decoding = clock();

		//read g_buffer from file
		strcpy(tmpFileName,FileName);
		strcat(tmpFileName,Type);
		strcat(tmpFileName,"Code");
		FILE *fpCode = fopen(tmpFileName, "rb");
		if (fpCode  == NULL) {
			fprintf(stderr, "Can't open file %s!\n",tmpFileName);
			exit(1);
		}
		//long int FileSize;
		long int buffer_size;
		fseek(fpCode, 0L, SEEK_END);
		buffer_size = ftell(fpCode);
		rewind(fpCode);
		g_buffer = (unsigned char*)malloc(buffer_size);
		fread(g_buffer,1,buffer_size,fpCode);
		/*for (j=0; j<10; j++)
			printf("%hhX ",g_buffer[j]);
		printf("\nabove is g_buffer from file\n");
		printf("actual_size %d and FileSize %ld\n", actual_size, FileSize);*/



		//load count table file
		strcpy(tmpFileName,FileName);
		strcat(tmpFileName,T);
		FILE *fpDiff = fopen(tmpFileName, "r");
		if (fpDiff  == NULL) {
			fprintf(stderr, "Can't open file %s!\n",tmpFileName);
			exit(1);
		}

		absize_txt(&alphabet_size, fpDiff);
		cm = (int*)malloc((alphabet_size+2)*sizeof(int));
		makeRanges_txt(cm, alphabet_size, RANGE_SIZE_IN_BITS,fpDiff);
		fclose(fpDiff);


		//write index to a file
		strcpy(tmpFileName,FileName);
		strcat(tmpFileName,Type);
		strcat(tmpFileName,"Decode");
		FILE *fpDecode = fopen(tmpFileName, "w+");
		if (fpDecode  == NULL) {
			fprintf(stderr, "Can't open file %s!\n",tmpFileName);
			exit(1);
		}


		RangeMapper* rm_decode = new RangeMapper(RANGE_SIZE_IN_BITS);
		current_byte = 0;
		TMPREAD_COUNT = 0;
		TMPREAD = 0x00;
		rm_decode->init();
		//printf("Begin to decode.\ndata[0]=%d,data[1]=%d,data[data_size-1]=%d\n",data[0],data[1],data[data_size-1]);
		while (current_byte<buffer_size+1) {
			int midpoint = rm_decode->getMidPoint();
			//next is binary search algorithm that does not need having lookup array
			int index = findInterval(cm, alphabet_size + 2, midpoint);
			//	printf("midpoint=%d,index=%d\n",midpoint,index);
			if (index == alphabet_size){
	/*			///////for test the tail of the code
				int tmpbitcount=0;
				printf("Finished! TMPWRITE_COUNT is %hhX\n",TMPWRITE_COUNT);
				while (current_byte<actual_size){
					readBit();
					tmpbitcount++;
				}
				printf("tail bit number is %d\n",tmpbitcount);
				///////for test the tail of the code
	*/			break; //end of data marker
			}
			fprintf(fpDecode,"%d ",index);
			rm_decode->decodeRange(cm[index], cm[index+1]);
		}


		delete rm_decode;
		//if (lookup) free(lookup);
		clock_t end_decoding = clock();
		//end decoding


		//write to summary result file
		fprintf(fpResult,"\n\n//decoder.cpp//File is %s%s\n", FileName, Type);
		fprintf(fpResult,"Time for decoding %2.3f sec.\n", (double)(end_decoding - start_decoding)/CLOCKS_PER_SEC);
         totaltime =totaltime + (double)(end_decoding - start_decoding)/CLOCKS_PER_SEC;


		free(g_buffer);
		free(cm);
		fclose(fpCode);
		fclose(fpDecode);
	}
	fprintf(fpResult,"Total Time for decoding %2.3f sec.\n", totaltime);
	fclose(fpResult);
	return 1;
}




