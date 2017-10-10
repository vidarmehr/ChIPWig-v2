/*
 * decomopress to a ChIPwig file
 * created by Vida Ravanmehr
 */


#include "parameters.h"
#include "arithmetic.h"
#include "decoder.cpp"
#include "fsplit.c"
#include "fsplitRA.cpp"
#include "DiffValSeq.cpp"
#include "DiffLoc1Seq.cpp"
#include "DiffLoc2Seq.cpp"
#include "merge.cpp"
#include "to_wig.cpp"
#include "to_wigRA.cpp"
#include "to_wigRA_P.cpp"
#include "to_wig_Lossy.cpp"
#include "to_wig_LossyRA.cpp"
#include "to_wig_LossyRA_P.cpp"
#include "De_RunLength.cpp"
#include "unblock.cpp"
#include "unblockL.cpp"
#include "partial_unblock.cpp"
#include "partial_unblockL.cpp"







int main(int argc, char * argv[]){

	clock_t start = clock();
	FILE *fpResult=fopen("result","a");
		if (fpResult == NULL) {
			fprintf(stderr,"Can't open output result file!\n");
			exit(1);
	}

	//int m = 0; //indicate if -m is enabled
	int s = 0; //indicate if -s is enalbed
	int b = 0; //indicate if -b is enabled
	int l = 0;//indicate if -l is enabled to decompress quantized files
	int qb = 0;//indicate if -qb is enabled to decmpress blockwise compressed quantized files
	int sl = 0;//indicate if -sl is enabled to have random access subsequent of blockwise compressed quantized files
	int opt; //indicate which functions to use
	bool isOK = true; //indicate if argv format is OK
	int i,j;
	int Qstart, Qend;
	char ChrmName[8];
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

		if (strcmp(argv[i], "-s") == 0 ){
			s = 1;
			if ((argc==7) && i+3 <= argc){
				i++;
				strcpy(ChrmName, argv[i]);
				i++;
				Qstart = atoi(argv[i]);
				i++;
				Qend = atoi(argv[i]);
			}
			else
				isOK=false;
		}


        else if (strcmp(argv[i], "-b") == 0)
			b = 1;
		else if (strcmp(argv[i], "-l") == 0)
		        l = 1;
	    else if (strcmp(argv[i], "-qb") == 0)
	              qb = 1;
	     else if (strcmp(argv[i], "-sl") == 0){
			 sl=1;
			 if ((argc==7) && i+3 <= argc){
			 		i++;
			 		strcpy(ChrmName, argv[i]);
			 		i++;
			 		Qstart = atoi(argv[i]);
			 		i++;
			 		Qend = atoi(argv[i]);
			 	}
			 else
			    isOK=false;
		}

		else{
			strcpy(targv[j],argv[i]);
			j++;
	}
	}
	if (j!=3){//targv should only left two arguments: path, filename
		isOK = false;
	}
	if (isOK){
		if (s == 0 && b == 0 && l ==0 && qb == 0 && sl == 0){ //decode whole file
		    	fsplit(&opt,targv);
		        decoder(targv);
		    	DiffValSeq(targv);
                        DiffLoc1Seq(targv);
                        DiffLoc2Seq(targv);
		        De_RunLength(targv);
	                merge(targv);
		        to_wig(targv);
            }
           else if (s == 0 && b == 1 && l == 0 && qb == 0 && sl == 0)
			  unblock(targv);

		   else if ( s == 1 && b == 0 && l == 0 && qb == 0 && sl == 0) //subsequence access
		           partial_unblock(targv,ChrmName,Qstart,Qend);
		   else if (s == 0 && b == 0 && l == 1 && qb == 0 && sl ==0) {// lossy decompression (standard)
			   fsplit(&opt,targv);
			   decoder(targv);
			    DiffValSeq(targv);
			    DiffLoc1Seq(targv);
			    DiffLoc2Seq(targv);
			    De_RunLength(targv);
			   merge(targv);
			   to_wig_Lossy(targv);
		 }
            else if (s == 0 && b == 0 && l == 0 && qb == 1 && sl == 0)
               unblockL(targv);
             else if (s == 0 && b == 0 && l == 0 && qb == 0 && sl == 1)
                  partial_unblockL(targv,ChrmName,Qstart,Qend);

		else
			isOK = false;
}
	if (isOK==false)
		printf("To use:\n chipwig2wig [InputFile] [OutputFile] \n"
			"options: \n"
			"-b \n"
			"-s [ChrmName (e.g. chr1)] [Query Start (integer)] [Query End (integer)] \n"
			"	subsequence query \n"
			"-l \n "
			"-qb \n"
			"-sl [ChrmName (e.g. chr1)] [Query Start (integer)] [Query End (integer)] \n"
			"	subsequence query \n");

       else{
		clock_t end = clock();
		fprintf(fpResult,"Decompressing time in seconds\n%2.3f\n", (double)(end-start)/CLOCKS_PER_SEC);
		if (s==1)
			fprintf(fpResult,"query time per bp %e\n", ((double)(end-start)/CLOCKS_PER_SEC)/(Qend-Qstart+1));
	}

    for(i = 0; i < 10; i++){
		free(targv[i]);
		free(targv2[i]);
	}
free(targv);
free(targv2);

return 0;

}

