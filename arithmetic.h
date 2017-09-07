/*
 * arithmetic.h
 * bit by bit rangemapper, with underflow and overflow
 * The buffer that stores the range of low and high can be any bits_in_buffer=(64-range_in_bits).
 * So maximum range_in_bits can be 30.
 * the number of bits encoded is exactly the same as the number of bits read for decode
 * output step by step results
 * 
 *
 *
 *  Created on: Jun 28, 2014
 *      Author: Zhiying Wang
 */
//



//global data buffer for round trip of arithmetic
unsigned char* g_buffer = 0;
int current_byte = 0;
unsigned char TMPWRITE_COUNT = 7;
unsigned char TMPWRITE = 0x00;
unsigned char TMPREAD_COUNT = 0;
unsigned char TMPREAD = 0x00;

///////Data generation functions///////////////////////////////
template <class T>
double calculate_entropy(T* data, int data_size) {
	int min, max, counter, buffer_size;
	int* buffer;
	double entropy;
	double log2 = log(2.0);
	double prob;

	min = data[0];
	max = data[0];
	for (counter=0; counter<data_size; ++counter) {
		if (data[counter] < min)
			min = data[counter];
		if (data[counter] > max)
			max = data[counter];
	}

	buffer_size = max - min + 1;
	buffer = (int*)malloc(buffer_size * sizeof(int));
	memset(buffer, 0x00, buffer_size * sizeof(int));
	for (counter=0; counter<data_size; ++counter) {
		++buffer[data[counter]-min];
	}

	entropy = 0.0;
	for (counter=0; counter<buffer_size; ++counter) {
		if (buffer[counter] > 0) {
			prob = (double)(buffer[counter]);
			prob /= (double)(data_size);
			entropy += log(prob)/log2*prob;
		}
	}
	entropy *= -1.0;

	if (buffer)
		free(buffer);
	return  entropy;
}

__inline double round(double x) {
	if ((x - floor(x)) >= 0.5)
		return ceil(x);
	else
		return floor(x);
}

double makeData(int* data, int data_size, int min, int max, int redundancy_factor) {
	int counter, cnt, high, low;
	double buf;

	if (redundancy_factor <= 1)
		redundancy_factor = 1;

	if (max <= min)
		max = min + 1;

	srand((unsigned)(time(0)));
	for (counter=0; counter<data_size; counter++) {
		buf = 0;
		for (cnt=0; cnt<redundancy_factor; cnt++) {
			buf += (double)(rand());
		}
		data[counter] = ((int)(buf))/redundancy_factor;
	}
	low  = data[0];
	high = data[0];
	for (counter=0; counter<data_size; counter++) {
		if (data[counter] > high)
			high = data[counter];
		if (data[counter] < low)
			low = data[counter];
	}
	for (counter=0; counter<data_size; counter++) {
		buf = (double)(data[counter] - low);
		buf /= (double)(high - low);
		buf *= (double)(max - min);
		buf = round(buf);
		data[counter] = (int)(buf) + min;
	}
	return calculate_entropy(data, data_size);
}
//end of data generation functions



//input/output functions
static __inline void writeByte(unsigned char byte) {
	g_buffer[current_byte++] = byte;
	//printf("write %hhX ",byte);
}

static __inline void writeBit(unsigned char newbit) { //newbit = 0x00 or 0x01
	TMPWRITE ^= (newbit  << TMPWRITE_COUNT);
	//printf("newbit=%hhX, tmpwrite_count=%hhX, TMPWRITE=%hhX \n", newbit, TMPWRITE_COUNT,TMPWRITE);
	if (TMPWRITE_COUNT == 0){
		writeByte(TMPWRITE);
		TMPWRITE = 0x00;
	    TMPWRITE_COUNT = 7;
	}
	else
	    TMPWRITE_COUNT --;
}

static __inline unsigned char readByte() {
	//printf("read %hhX ",g_buffer[current_byte]);
	return g_buffer[current_byte++];
}

static __inline unsigned char readBit() {
	unsigned char newbit;
	if (TMPREAD_COUNT == 0){
		TMPREAD = readByte();
		TMPREAD_COUNT = 7;
	}
	else
		TMPREAD_COUNT --;
	newbit = (TMPREAD & (1 << 7)) >> 7;
	TMPREAD <<= 1;
	//printf("read newbit %X, TMPREAD_COUNT=%hhX, TMPREAD=%hhX\n", newbit, TMPREAD_COUNT, TMPREAD);
	return newbit;
}

static __inline int findInterval(int* cm, int size, int point) {
	int index = -1;
	int left  = 0;
	int right = size-2;
	int cnt = 0;
	while (true) {
		int mid = (right + left)>>1;
		if (point >= cm[mid] && point < cm[mid+1]) {
			index = mid;
			break;
		}
		if (point >= cm[mid+1]) left = mid + 1;
		else right = mid;
		if (cnt++ >= size) break;
	}
	return index;
}

//This is the main class. It can be used in adaptive data
//processing. It processes ranges that passed to encoder and decoder.
//In adaptive coder the ranges can be computed dynamically and depend
//on the context.
//Class is written for generic case: alphabets from 2 up to 2^30-2 can be
//processed without changes in code. 
class RangeMapper {
public:
	RangeMapper(int range_size) {
		LOW = 0;
		MID = 0;
		RANGE_SIZE = range_size;
		RANGE_LIMIT = ((unsigned long long)(1) << RANGE_SIZE)-1;
		BITS_IN_BUFFER = (64 - RANGE_SIZE);
		SHIFT_IN_BITS = BITS_IN_BUFFER - 1; //number of bits to shift to get msb
		MASK  = ((long long)(1)<<BITS_IN_BUFFER) - 1;
        UMASK = (long long)(1)<<(SHIFT_IN_BITS-1); //underflow mask
		HIGH = MASK;
        UNDERFLOW_COUNT = 0;
        BITS_COUNT = 0;//count number of bits for current (or last) symbol. Used to control length of flush


	}
	~RangeMapper() {}
	void encodeRange(int cmin, int cmax);
	void decodeRange(int cmin, int cmax);
	int getMidPoint();
	void flush();
	void init();
	unsigned long long getLOW();
	unsigned long long getHIGH();

private:
	void updateModel(int cmin, int cmax);
	unsigned long long LOW, HIGH, MID, RANGE_LIMIT, MASK, UMASK, UNDERFLOW_COUNT;
	unsigned char RANGE_SIZE, BITS_IN_BUFFER, SHIFT_IN_BITS, BITS_COUNT;
};

unsigned long long RangeMapper::getLOW(){
	return (LOW);
}

unsigned long long RangeMapper::getHIGH(){
	return (HIGH);
}

void RangeMapper::updateModel(int cmin, int cmax) {
	unsigned long long range = HIGH - LOW;
	HIGH = LOW + ((range * cmax) >> RANGE_SIZE);
	LOW += ((range * cmin) >> RANGE_SIZE) + 1;
}

int RangeMapper::getMidPoint() {
	//printf("LOW=%016llX, HIGH=%016llX, MID=%016llX, midpoint=%f newmidpoint=%d \n", LOW, HIGH, MID, (((MID - LOW) << RANGE_SIZE)/ (double)(HIGH - LOW)), (int)(((MID - LOW) << RANGE_SIZE) / (double)(HIGH - LOW) + 0.5));

	//return  (int)(((MID - LOW) << RANGE_SIZE) / (double)(HIGH - LOW) + 0.5); //rounding
	return  (int)(((MID - LOW) << RANGE_SIZE) / (HIGH - LOW)); //truncating
}



void RangeMapper::encodeRange(int cmin, int cmax) {

	updateModel(cmin, cmax);
	
	BITS_COUNT = 0; //number of msb same + number of new underflow
	//printf("\nstart LOW=%016llX, HIGH=%016llX\n",LOW,HIGH);
	while (1) {
		if (((LOW ^ HIGH) >> SHIFT_IN_BITS) == 0){ //msb same
			writeBit((unsigned char)(LOW >> SHIFT_IN_BITS));
			//if ((unsigned long long)cmax == RANGE_LIMIT) //last symbol
			BITS_COUNT ++; 

			for (; UNDERFLOW_COUNT > 0; UNDERFLOW_COUNT--){
				writeBit((unsigned char)(!(LOW >> SHIFT_IN_BITS)));
				//BITS_COUNT ++;
			}

			LOW <<= 1;
			HIGH = (HIGH << 1) | 0x01;
			HIGH &= MASK;
			LOW  &= MASK;

		}
		else{ //msb different
			if ((LOW >> (SHIFT_IN_BITS - 1)) == 0x01 && (HIGH >> (SHIFT_IN_BITS - 1)) == 0x02) { //LOW=01, HIGH=10
				UNDERFLOW_COUNT ++;
				LOW ^= UMASK;
				HIGH |= UMASK;
				LOW <<= 1;
				HIGH = (HIGH << 1) | 0x01;
				HIGH &= MASK;
				LOW  &= MASK;
				BITS_COUNT ++;
			}
			else
				break;
		}
	}

	//printf("end   LOW=%016llX, HIGH=%016llX\n",LOW,HIGH);
	//printf("BITS_COUNT %d\n", BITS_COUNT);

}

void RangeMapper::decodeRange(int cmin, int cmax) {

	updateModel(cmin, cmax);

	//printf("\nstart LOW=%016llX, HIGH=%016llX\n",LOW,HIGH);
	while (1){
		if (((LOW ^ HIGH) >> SHIFT_IN_BITS) == 0){ //msb same
			LOW <<= 1;
			HIGH = (HIGH << 1) | 0x01;
			MID = (MID << 1) | readBit();
			HIGH &= MASK;
			LOW  &= MASK;
			MID  &= MASK;
		}
		else{ //msb different
			if ((LOW >> (SHIFT_IN_BITS - 1)) == 0x01 && (HIGH >> (SHIFT_IN_BITS - 1)) == 0x02) { //LOW=01, HIGH=10
				MID ^= UMASK;
				LOW ^= UMASK;
				HIGH |= UMASK;
				LOW <<= 1;
				HIGH = (HIGH << 1) | 0x01;
				MID = (MID << 1) | readBit();
				HIGH &= MASK;
				LOW  &= MASK;
				MID  &= MASK;
			}
			else
				break;
		}
	}
	//printf("end   LOW=%016llX, HIGH=%016llX\n",LOW,HIGH);

}

void RangeMapper::flush() {
	LOW += 1;
	//output msb and underflow times !msb
	writeBit((unsigned char)(LOW >> SHIFT_IN_BITS));
	for (; UNDERFLOW_COUNT > 0; UNDERFLOW_COUNT--){
		writeBit((unsigned char)(!(LOW >> SHIFT_IN_BITS)));
	}
	LOW <<= 1;
	LOW &= MASK;
	//output rest
	for (int i=1; i<BITS_IN_BUFFER-BITS_COUNT; i++) {
	//for (; i<BITS_IN_BUFFER-BITS_COUNT; i++) {
		writeBit((unsigned char)(LOW >> SHIFT_IN_BITS));
		LOW <<= 1;
		LOW &= MASK;
	}
	if (TMPWRITE_COUNT != 7)
		writeByte(TMPWRITE);
	//printf("tmpwrite_count=%x, flush finished\n",TMPWRITE_COUNT);
	//printf("BITS_IN_BUFFER %d, BITS_COUNT=%d\n",BITS_IN_BUFFER, BITS_COUNT);
}

void RangeMapper::init() {
	for (int i=0; i<BITS_IN_BUFFER; ++i) {
		MID = (MID << 1) + readBit();
	}
	//printf(" MID=%016llX \n",MID);
}

//find alphabet size from fpDiff in text format
void absize_txt(int *alphabet_size, FILE *fp){
	*alphabet_size=0;
	char ch;
	char tmpchar[1000];	
	fgets(tmpchar,1000,fp);//skip first row
	while(!feof(fp))
	{
	  ch = fgetc(fp);
	  if(ch == '\n')
	  {
		(*alphabet_size) ++;
	  }
	}
	rewind(fp);
}

//find alphabet size from fpDiff in binary format
void absize(int *alphabet_size, FILE *fp){
	*alphabet_size=0;
	char tmpchar[1000];	
	long int sz1, sz2;
	fgets(tmpchar,1000,fp);//skip first row
	sz1 = (ftell(fp));	
	fseek(fp, 0L, SEEK_END);
	sz2 = (ftell(fp));
	*alphabet_size = (sz2 - sz1)/(sizeof(double)+sizeof(int));
	rewind(fp);
}



//get freq from count file fp in binary format, assume first row of fp is annotation
//pass *cm as reference (only for c++), so can modify its value: int * &cm
//but since allocate inside the function, pass int **cm
void makeRanges(int* cm, int alphabet_size, int PRECISION, FILE *fp) {
	
	//printf("alphabetsize=%d\n",alphabet_size);
	
	char tmpchar[1000];	
	fgets(tmpchar,1000,fp);//skip first row
	
	//we make ranges for data
	int* freq = (int*)malloc(alphabet_size * sizeof(int));
	memset(freq, 0x00, alphabet_size * sizeof(int));
	//int tmp;
	int i=0;
	double tmpdouble;
	while (i < alphabet_size) {
		//fscanf(fp,"%*f\t%d\n",&freq[i]);
		fread(&tmpdouble,sizeof(double),1,fp);
		fread(&freq[i],sizeof(int),1,fp);
		i++;
	}
	/*for (int j=0; j<i; j++)
		printf("%d ",freq[j]);*/
	
	cm[0] = 0;
	for (int i=0; i<alphabet_size; ++i) {
		cm[i+1] = cm[i] + freq[i];
	}
	
	int total = cm[alphabet_size];
	int upper_limit = (1<<PRECISION) - 2;
	//printf("total=%d,upper limit=%d\n",total,upper_limit);
	for (int i=0; i<alphabet_size + 1; ++i) {
		cm[i] = (int)((long long)(cm[i]) * (long long)(upper_limit) / (long long)(total));
	}
	cm[alphabet_size+1] = (1<<PRECISION) - 1;
	//ranges are ready

	//correction of ranges
	for (int i=0; i<alphabet_size; ++i) {
		if (cm[i+1] <= cm[i]) cm[i+1] = cm[i] + 1;
	}
	for (int i=alphabet_size; i>=0; --i) {
		if (cm[i] >= cm[i+1]) cm[i] = cm[i+1] - 1;
	}
	int j=0;
	for (j=1; j<alphabet_size; j++){
		if (cm[j]<0){			
			printf("Got an wrong cumulative probability, increase bits_in_range! cm[%d]=%d\n",j,cm[j]);
			exit(1);
		}
	}
	//end of correction
	if (freq) free(freq);
}

//get freq from count file fp in text format, assume first row of fp is annotation
//pass *cm as reference (only for c++), so can modify its value: int * &cm
//but since allocate inside the function, pass int **cm
void makeRanges_txt(int* cm, int alphabet_size, int PRECISION, FILE *fp) {
	
	char tmpchar[1000];	
	fgets(tmpchar,1000,fp);//skip first row
	
	//we make ranges for data
	int* freq = (int*)malloc(alphabet_size * sizeof(int));
	memset(freq, 0x00, alphabet_size * sizeof(int));
	//int tmp;
	int i=0;
	while (!feof(fp)) {
		fscanf(fp,"%*f\t%d\n",&freq[i]);
		i++;
	}
	/*for (int j=0; j<i; j++)
		printf("%d ",freq[j]);*/
	
	cm[0] = 0;
	for (int i=0; i<alphabet_size; ++i) {
		cm[i+1] = cm[i] + freq[i];
	}
	
	int total = cm[alphabet_size];
	int upper_limit = (1<<PRECISION) - 2;
	//printf("total=%d,upper limit=%d\n",total,upper_limit);
	for (int i=0; i<alphabet_size + 1; ++i) {
		cm[i] = (int)((long long)(cm[i]) * (long long)(upper_limit) / (long long)(total));
	}
	cm[alphabet_size+1] = (1<<PRECISION) - 1;
	//ranges are ready

	//correction of ranges
	for (int i=0; i<alphabet_size; ++i) {
		if (cm[i+1] <= cm[i]) cm[i+1] = cm[i] + 1;
	}
	for (int i=alphabet_size; i>=0; --i) {
		if (cm[i] >= cm[i+1]) cm[i] = cm[i+1] - 1;
	}
	int j=0;
	for (j=1; j<alphabet_size; j++){
		if (cm[j]<0){			
			printf("Got an wrong cumulative probability, increase bits_in_range! cm[%d]=%d\n",j,cm[j]);
			exit(1);
		}
	}
	//end of correction
	if (freq) free(freq);
}

//get freq from the seq
void makeRanges0(int* data, int data_size, int* cm, int alphabet_size, int PRECISION) {
	//we make ranges for data
	int* freq = (int*)malloc(alphabet_size * sizeof(int));
	memset(freq, 0x00, alphabet_size * sizeof(int));
	for (int i=0; i<data_size; ++i) {
		++freq[data[i]];
	}
	for (int i=0; i<20; i++)
		printf("%d ",freq[i]);
	printf("\n");

	cm[0] = 0;
	for (int i=0; i<alphabet_size; ++i) {
		cm[i+1] = cm[i] + freq[i];
	}
	//printf("0th round: cm[0]=%d,cm[1]=%d,cm[alphabet_size]=%d,cm[alphabets_zize+1]=%d\n",cm[0],cm[1],cm[alphabet_size],cm[alphabet_size+1]);

	int total = cm[alphabet_size];
	int upper_limit = (1<<PRECISION) - 2;
	//printf("total=%d,upper limit=%d\n",total,upper_limit);
	for (int i=0; i<alphabet_size + 1; ++i) {
		cm[i] = (int)((long long)(cm[i]) * (long long)(upper_limit) / (long long)(total));
	}
	cm[alphabet_size+1] = (1<<PRECISION) - 1;
	//printf("1st round: cm[0]=%d,cm[1]=%d,cm[alphabet_size]=%d,cm[alphabets_zize+1]=%d\n",cm[0],cm[1],cm[alphabet_size],cm[alphabet_size+1]);
	//ranges are ready

	//correction of ranges
	for (int i=0; i<alphabet_size; ++i) {
		if (cm[i+1] <= cm[i]) cm[i+1] = cm[i] + 1;
	}
	//printf("2st round: cm[0]=%d,cm[1]=%d,cm[alphabet_size]=%d,cm[alphabets_zize+1]=%d\n",cm[0],cm[1],cm[alphabet_size],cm[alphabet_size+1]);
	for (int i=alphabet_size; i>=0; --i) {
		if (cm[i] >= cm[i+1]) cm[i] = cm[i+1] - 1;
	}
	int j=0;
	//printf("3rd round: cm[0]=%d ",cm[0]);
	for (j=1; j<alphabet_size; j++){
		if (cm[j]<0){			
			printf("Got an wrong cumulative probability, increase bits_in_range! cm[%d]=%d\n",j,cm[j]);
			exit(1);
		}
	}
	//printf("cm[%d]=%d cm[%d]=%d\n",j,cm[j],j+1,cm[j+1]);
	//end of correction
	if (freq) free(freq);
}

void makeLookupTable(int* cm, int size, int* lookup) {
	for (int i=0; i<size-1; ++i) {
		for (int j=cm[i]; j<cm[i+1]; ++j) {
			lookup[j] = i;
		}
	}
}
