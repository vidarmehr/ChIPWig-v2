#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <math.h>
#include <string.h>

#include <sys/types.h>
//#include <sys/sysinfo.h>
//#include <sys/mman.h>
//#include <unistd.h>
//#define  __USE_GNU
////#include <sched.h>
#include <ctype.h>
////#include <sys/wait.h>

//for printing messages, 1--printf, 0--does nothing
#if 0
  #define SPAM(a) printf a
#else
  #define SPAM(a) (void)0
#endif
//for printing messages to "result" file
#if 0
  #define SPAMR(a) fprintf a
#else
  #define SPAMR(a) (void)0
#endif

//parameters for random access
int BlockSize=12; //number of diff that are encoded together is 2^BlockSize
//int FileSize=32; //assume compressed codesize is no more than 2^FileSize bytes
//int IndexSize=20; //A total of 2^IndexSize indices
//int ChrmSize=32; //assume chromosome locations is no more than 2^ChrmSize

double Threshold=50;
int Number_Levels=50;
//list of files for different options
char list[3][21][40]={
	//second row is not used
	{".swig","ChrmName","SpanName","ExceedLoc","ExceedVal","Extra", "DiffLoc1Ext", "DiffLoc1","DiffLoc2","DiffVal","DiffLocSeqMatlab1Code","DiffLocSeqMatlab2Code","DiffValSeqMatlabCode"}, //regular
		{".swig","ChrmName","Exceed","LenExceed","Diff","LenDiff","DiffSeqMatlablpaq","LenDiffSeqMatlablpaq"}, //lpaq
		{".swig","ChrmName","SpanName","ExceedLoc","ExceedVal","DiffLoc1Ext","DiffLoc1","DiffLoc2","DiffVal","DiffLocSeqMatlab1Code","DiffLocSeqMatlab2Code","DiffValSeqMatlabCode", "Summary"}
	};


__inline unsigned int mydiff(long int d){
//take an integer d and map it as nonnegtive integers:
//2d-1, d>0
//2*abs(d), d<=0
	unsigned int y;
	if (d>0)
		y = 2*d-1;
	else
		y = 2*abs(d);
	return(y);
};

__inline long int getdiff(unsigned int y){
	//inverse function of mydiff
	if (y & 0x01)
		return((y+1)>>1);
	else
		return(-((long int)y>>1));
};

//get file size from fp to the end of a file
//(fp need to point to the beginning of a file)
long int fsize(FILE *fp){
	fseek(fp, 0L, SEEK_END);
	long int sz;
	sz = (ftell(fp));
	rewind(fp);
	return(sz);
}

//search for the index i such that array[i]<=search<array[i+1]
//n is the array size
int binsearch(int n,long int *array, long int search){
	int first = 0;
	int last = n-1;
	int middle = (first+last)/2;

	while (first <= last) {
	  //printf("first %d,  middle %d, middle+1 %d, last %d, search %d\n",array[first],array[middle], array[middle+1],array[last],search);
	  if (array[middle+1] <= search)
		 first = middle + 1;
	  else if (array[middle] <= search && array[middle+1] > search)
		 return middle;
	  else
		 last = middle - 1;

	  middle = (first + last)/2;
	}
	if (first > last)
	  return -1;
}


//search for the index i such that array[i-1]<search<=array[i].
//n is the array size
//indicator=0, index=i, if array[i]==search;
//indicator=-1, index=i, if array[i-1]<search<array[i]
//indicator=-1, index=n, if array[n-1]<search;
//indicator=-1, index=0, if array[0] > search
__inline int binfind(int n,double *array, double search, int *indicator){
	int first = 0;
	int last = n-1;
	int middle;

	while (first <= last) {
		middle = (first + last)/2;
		//printf("first %d,  middle %d, middle+1 %d, last %d, search %d\n",array[first],array[middle], array[middle+1],array[last],search);
		if (array[middle] - search<1e-10
			&& array[middle] - search > -1e-10 ){//array[middle] == search
			*indicator = 0;
			return middle;
		}
		else if (array[middle] < search)
			first = middle + 1;
		else
			last = middle - 1;
	}
	if (first > last){
		*indicator = -1;
		return first;
	}
}
