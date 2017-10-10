/*
 * comopress a ChIP-seq wig file
 * created by Vida Ravanmehr
 */


#include "parameters.h"
#include "arithmetic.h"
#include "encoder.cpp"
#include "encoderRA.cpp"
#include "GetChr.cpp"
#include "getseq.cpp"
#include "getseq2.cpp"
#include "fmerge.cpp"
#include "fmergeRA.cpp"
#include "DiffCoding2.cpp"
#include "DiffCoding2L.cpp"
#include "CountVal.cpp"
#include "CountLoc.cpp"
#include "Multiply1000.cpp"
#include "Multiply1000RA.cpp"
#include "RunLength.cpp"
#include "CountLoc1.cpp"
#include "CountLoc2.cpp"
#include "Loc1Matlab.cpp"
#include "Loc2Matlab.cpp"
#include "ValMatlab.cpp"
#include "getblock.cpp"
#include "getblockQ.cpp"
#include "NonUniQuantizer1.cpp"
#include "NonUniQuantizer2.cpp"
#include "NonUniQuantizer3.cpp"
#include "UniQuantizer.cpp"
#include "Multiply100UQ.cpp"
#include "Multiply100UQR.cpp"
#include "Multiply100NUQ.cpp"
#include "Multiply100NUQR.cpp"
#include "RecordValues.cpp"
#include "ProbabilityDist.cpp"




int main(int argc, char * argv[]){

	clock_t start = clock();
        FILE *fpResult=fopen("result","a");
	if (fpResult == NULL) {
		fprintf(stderr,"Can't open output result file!\n");
		exit(1);
	}


	//printf("compress start!\n");

	int r = 0; //indicate if -r(block-wise coding) is enalbed
	int u = 0; //indicate if -u(uniform quatizer) is enabled
	int n1 = 0; // indicate if -n1 (non-uniform quantizer with M=50, tau=50) is enabled
        int n2 = 0; // indicate if -n2 (non-uniform quantizer with M=100, tau=70 percent of maximum value) is enabled
        int n3 = 0; // indicate if -n3 (non-uniform quantizer with M=50, tau=70 percent of maximum value) is enabled
	int ur = 0; // blockwise encoding for uniformly quantized file
	int nr1 = 0; // blockwise encoding for nonuniformly quantized file with M=50, tau=50
        int nr2 = 0; // blockwise encoding for nonuniformly quantized file with M=100, tau=70 percent of maximum value
        int nr3 = 0; // blockwise encoding for nonuniformly quantized file with M=50, tau=70 percent of maximum value



	//int opt = 0; //indicate which functions to use
	bool isOK = true; //indicate if argv format is OK
	int i,j;
	char N[10];
	char **targv; //tmp argv to put to subsequent functions, if format correct, only stores two strings: path, filename
	char **targv2;
	targv = (char **)malloc(10 * sizeof(char *));
	if(targv == NULL){
		       printf("Error! Allocation was not successful.\n");
		       return(-1);
	          }
	targv2 = (char **)malloc(10 * sizeof(char *));
	if(targv2 == NULL){
		       printf("Error! Allocation was not successful.\n");
		       return(-1);
	          }
	for(i = 0; i < 10; i++){
		targv[i] = (char *)malloc(10000 * sizeof(char));
		if(targv[i] == NULL){
		       printf("Error! Allocation was not successful.\n");
		       return(-1);
	          }
		targv2[i] = (char *)malloc(10000 * sizeof(char));
		if(targv2[i] == NULL){
		       printf("Error! Allocation was not successful.\n");
		       return(-1);
	          }
	}
	j=1;
	for (i = 1; i<10 && i < argc && isOK; i++){ //should argc<10
        if (strcmp(argv[i], "-r") == 0){
			r = 1;
			if ((argc==5 ) && i+1 <= argc){
				i++;
				BlockSize = atoi(argv[i]);
				//printf("blocksize %d\n",BlockSize);
			}
			else
			isOK = false;
		}
		else if(strcmp(argv[i], "-u") == 0){
				u = 1;
				if((argc == 6) && i+1 <= argc){
					++i;
					Threshold = atof(argv[i]);
					++i;
				    Number_Levels = atoi(argv[i]);
				}
				else
				isOK=false;
			}
		   else if(strcmp(argv[i], "-n1") == 0){
				n1 = 1;
				if((argc != 4) || i+1 > argc){
				   isOK=false;
	             }
			 }

                    else if(strcmp(argv[i], "-n2") == 0){
				n2 = 1;
				if((argc != 4) || i+1 > argc){
				   isOK=false;
	             }
			 }

                      else if(strcmp(argv[i], "-n3") == 0){
				n3 = 1;
				if((argc != 4) || i+1 > argc){
				   isOK=false;
	               }
			  }


			 else if(strcmp(argv[i], "-ur") == 0){
				 ur = 1;
				 if((argc == 7) && i+1 <= argc){
				 	++i;
				 	Threshold = atof(argv[i]);
				 	++i;
				 	Number_Levels = atoi(argv[i]);
				    ++i;
				    BlockSize = atoi(argv[i]);
				 	}
				 else
				 	isOK=false;
			}
			else if (strcmp(argv[i], "-nr1") == 0){
				nr1 = 1;
				if((argc == 5) || i+1 <= argc){
					++i;
					BlockSize = atoi(argv[i]);
				 	}
				 else
				 isOK=false;
			 }
                     else if (strcmp(argv[i], "-nr2") == 0){
				nr2 = 1;
				if((argc == 5) || i+1 <= argc){
					++i;
					BlockSize = atoi(argv[i]);
				 	}
				 else
				 isOK=false;
			 }
                      else if (strcmp(argv[i], "-nr3") == 0){
				nr3 = 1;
				if((argc == 5) || i+1 <= argc){
					++i;
					BlockSize = atoi(argv[i]);
				 	}
				 else
				 isOK=false;
			 }





		else{
			  strcpy(targv[j],argv[i]);
			  j++;
		    }
	}
	if (isOK){
		if  (r==0  && u==0 && n1==0 && n2==0 && n3==0 && ur == 0 && nr1 == 0 && nr2 == 0 && nr3 == 0 && argc==3){//regular compression
		//GetChr(targv);
               Multiply1000(targv);
		DiffCoding2(targv);
        	getseq(targv);
		CountVal(targv);
		ValMatlab(targv);
                RunLength(targv);
               CountLoc1(targv);
		Loc1Matlab(targv);
                CountLoc2(targv);
		Loc2Matlab(targv);
		encoder(targv);
		fmerge(0,targv,-1);
	}
		else if ( r == 1 && u == 0 && n1 == 0 && n2 == 0 && n3 == 0 && ur == 0 && nr1 == 0 && nr2 == 0 && nr3 == 0 && argc == 5 ){ //random access
			//printf("random access!\n");
			Multiply1000RA(targv);
			getblock(targv);
		}
		else if (u == 1 && r == 0 & n1 == 0 && n2 == 0 && n3 == 0  && ur == 0 && nr1 == 0 && nr2 == 0 && nr3 == 0 && argc == 6){
			RecordValues(targv);
			ProbabilityDist(targv);
			UniQuantizer(targv);
			Multiply100UQ(targv);
			DiffCoding2L(targv);
			getseq(targv);
		        CountVal(targv);
			ValMatlab(targv);
			RunLength(targv);
			CountLoc1(targv);
			Loc1Matlab(targv);
			CountLoc2(targv);
			Loc2Matlab(targv);
			encoder(targv);
		       fmerge(0,targv,-1);
		}
		else if (n1 == 1 && n2 == 0 && n3 == 0 && u==0 && r==0 && ur == 0 && nr1 == 0 && nr2 == 0 && nr3 == 0 && argc == 4){
                      //GetChr(targv);
			RecordValues(targv);
			ProbabilityDist(targv);
			NonUniQuantizer1(targv);
			Multiply100NUQ(targv);
			DiffCoding2L(targv);
			getseq(targv);
			CountVal(targv);
			ValMatlab(targv);
			RunLength(targv);
			CountLoc1(targv);
			Loc1Matlab(targv);
			CountLoc2(targv);
			Loc2Matlab(targv);
			encoder(targv);
		        fmerge(0,targv,-1);
		}
               else if (n2 == 1 && n1 == 0 && n3 == 0 && u==0 && r==0 && ur == 0 && nr1 == 0 && nr2 == 0 && nr3 == 0 && argc == 4){
                      //GetChr(targv);
			RecordValues(targv);
			ProbabilityDist(targv);
			NonUniQuantizer2(targv);
			Multiply100NUQ(targv);
			DiffCoding2L(targv);
			getseq(targv);
			CountVal(targv);
			ValMatlab(targv);
			RunLength(targv);
			CountLoc1(targv);
			Loc1Matlab(targv);
			CountLoc2(targv);
			Loc2Matlab(targv);
			encoder(targv);
		        fmerge(0,targv,-1);
		}
               else if (n3 == 1 && n2 == 0 && n1 == 0 && u==0 && r==0 && ur == 0 && nr1 == 0 && nr2 == 0 && nr3 == 0 && argc == 4){
                      //GetChr(targv);
			RecordValues(targv);
			ProbabilityDist(targv);
			NonUniQuantizer3(targv);
			Multiply100NUQ(targv);
			DiffCoding2L(targv);
			getseq(targv);
			CountVal(targv);
			ValMatlab(targv);
			RunLength(targv);
			CountLoc1(targv);
			Loc1Matlab(targv);
			CountLoc2(targv);
			Loc2Matlab(targv);
			encoder(targv);
		        fmerge(0,targv,-1);
		}

		else if (n1 == 0 && n2 == 0 && n3 == 0  && u ==0 && r == 0 && nr1 == 0 && nr2 == 0 && nr3 == 0 && ur == 1 && argc == 7){
			RecordValues(targv);
			ProbabilityDist(targv);
			UniQuantizer(targv);
			Multiply100UQR(targv);
			getblockQ(targv);
		}
		else if (n1 == 0 && n2 == 0 && n3 == 0 && u ==0 && r == 0 && ur ==0 && nr1 == 1 && nr2 == 0 && nr3 == 0 && argc == 5){
			RecordValues(targv);
			ProbabilityDist(targv);
			NonUniQuantizer1(targv);
			Multiply100NUQR(targv);
			getblockQ(targv);
		}
                else if (n1 == 0 && n2 == 0 && n3 == 0 && u == 0 && r == 0 && ur == 0 && nr2 == 1 && nr1 == 0 &&  nr3 == 0 && argc == 5){
			RecordValues(targv);
			ProbabilityDist(targv);
			NonUniQuantizer2(targv);
			Multiply100NUQR(targv);
			getblockQ(targv);
		}
               else if (n1 == 0 && n2 == 0 && n3 == 0 && u == 0 && r == 0 && ur == 0 && nr3 == 1 && nr1 == 0 && nr2 == 0 && argc == 5){
			RecordValues(targv);
			ProbabilityDist(targv);
			NonUniQuantizer3(targv);
			Multiply100NUQR(targv);
			getblockQ(targv);
		}


		else
			isOK = false;
	}
	if (isOK==false)
		printf("To use:\nwig2ChIPwig InputFile OutputFile \n"
			"options: \n"

			"-r [B, encode block size from 12 to 18]\n"
			"	random access and encode by blocks of size 2^B\n"
			"-u [Threhold, Number of Quantization levels]\n"
			"-n1 (the file is compressed with non-uniform quantization using default parameters M=50, T=50)\n"
                        "-n2 (the file is compressed with non-uniform quantization using default parameters M=100, T=70 percent of the max value)\n"
                        "-n3 (the file is compressed with non-uniform quantization using default parameters M=50, T=70 percent of the max value)\n"
			"-ur [T, M, B, (encode block size from 12 to 18)]\n"
			"-nr1 [B, encode block size from 12 to 18](the file is compressed with non-uniform quantization using default parameters M=50, T=50)\n"
                        "-nr2 [B, encode block size from 12 to 18](the file is compressed with non-uniform quantization using default parameters M=100, T=70 percent of the max value)\n"
                        "-nr3 [B, encode block size from 12 to 18](the file is compressed with non-uniform quantization using default parameters M=50, T=70 percent of the max value)\n");

    else{
		clock_t end = clock();
		fprintf(fpResult,"Compressing time in seconds\n%2.3f\n", (double)(end-start)/CLOCKS_PER_SEC);
	}
    for(i = 0; i < 10; i++){
		free(targv[i]);
		free(targv2[i]);
	}
free(targv);
free(targv2);
fclose(fpResult);
return 0;

}
