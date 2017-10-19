# ChIPWig-v2
The ChIPWig tool provides compression/decompression for the ChIP-seq Wig files. 

Copyright by Vida Ravanmehr, 2017.

Please contact milenkov@illinois.edu or vidarm@illinois.edu for any questions.



                                                      Lossless ChIPWig:
						  
To compress a file, please use:

 wig2chipwig [InputFile] [OutputFile] 
 
options: 

-r [B, encode block size from 12 to 18]
	for random access and encode by blocks of size 2^B 

===========

To decompress a file, please use:

 chipwig2wig [InputFile] [OutputFile] 
 
options:

-b 
decompresses a whole file that has been compressed by encoding block-by-block.

 Note: The input file must be a block-wise compressed ChIP-seq file. If the file has been compressed in a standard mode, please use the first command to decompress the file.
 
-s [ChrmName (e.g. chr1)] [Query Start (integer)] [Query End (integer)] 
	subsequence query 

Note: The output of this command is 3 files:

1. Outputfile which contains the information of chromosome ChrName for locations between Query Start and Query End.

2. OutpufileSeq which is the decompressed file of the block(s) containing the information of chromosome ChrName for locations between Query Start and Query End.

3. OutputileSummarySequence is the file consisting of summary statistics (min, max, mean, std) of the average read densities of chromosome ChrName for locations between Query Start and Query End.

=================

                                            example(lossless)
		   
1. Compress a file using standard setup:

$ wig2chipwig in.wig out.chipwig

2. Compress a file allowing random query in the future with block size 16:

$ wig2chipwig in.wig out.chipwig -r 16

3. Decompress a file in standard mode: 

$ chipwig2wig in.chipwig out.wig

4. Decompress a whole file that has been compressed blockwise (random access mode):

$  chipwig2wig in.chipwig out.wig -b

5. Decompress a subsequence of a file:  chr1, start location 10001, end location 11051:

$ chipwig2wig in.chipwig out.wig -s chr1 10001 11051

===============================

                                                     Lossy ChIPWig:

1. Compress a file using nonuniform quantization:

By default, in the nonuniform quantization, \lambda(x) has been obtained for our running example. The number of quantization levels M=50 for the threshold \tau=50. For \tau=70% of the largest average read density, we considered M=50 and M=100 and all values greater than \tau are mapped to 80% of the maximum average read density.

The file "inputfileMaximum" returns the total number of average read densities in the file, in addition to the maximum and minimum average read denisities.

The file "inputfileProb", provides the cumulative probability distribution of the average read densitites. This file has 4 columns:

  1st column: average read density (after multiplying by 100)
  
  2nd column: the total number of appearance of the average read density
  
  3rd column: the probability of appearance of each average read density
  
  4th column: the cumulative probaility distribution
  
This file then can be used in Matlab, estimating the cumulative probability distributions F_X(x), taking derivates and finding density function f_X(x).  Then, \lambda(x) is obtained as explained in the paper. The number of quantization levels in each interval (a,b) is then derived using the equation (4) in the paper. 

Compress a file using nonuniform quantization with \tau=50 and M=50:

wig2chipwig [InputFile] [OutputFile] -n1

Compress a file using nonuniform quantization with \tau=70% of the largest average read density and M=50:

wig2chipwig [InputFile] [OutputFile] -n2

Compress a file using nonuniform quantization with \tau=70% of the largest average read density and M=100:

wig2chipwig [InputFile] [OutputFile] -n3

2. Compress a file in a random access mode (blockwise) using nonuniform quantization:

We have also enabled random access in the lossy mode. By default, in the nonuniform quantization, \lambda(x) has been obtained for our running example. 

Compress a file in a random access mode (blockwise) using nonuniform quantization, M=50, \tau=50:

wig2chipwig [InputFile] [OutputFile] -nr1 [B, encode block size from 12 to 18]
	                                 for random access and encode by blocks of size 2^B 
					 
Compress a file in a random access mode (blockwise) using nonuniform quantization, M=50, \tau=70% of the alargest average read density:

wig2chipwig [InputFile] [OutputFile] -nr2 [B, encode block size from 12 to 18]
	                                 for random access and encode by blocks of size 2^B 					 

Compress a file in a random access mode (blockwise) using nonuniform quantization, M=100, \tau=70% of the alargest average read density:

wig2chipwig [InputFile] [OutputFile] -nr3 [B, encode block size from 12 to 18]
	                                 for random access and encode by blocks of size 2^B 
					 
=============

3. Compress a file with uniform quantization:

wig2chipwig [InputFile] [OutputFile] -u [Threshold (float)] [Number of quantization leveles (integer)]


4. Compress a file in a random access mode (blockwise) with uniform quantization:

wig2chipwig [InputFile] [OutputFile] -ur [Threshold (float)] [Number of quantization leveles (integer) ] [B, encode block size from 12 to 18] for random access and encode by blocks of size 2^B 

 ===================
 
 5. Decompress a file that has been first quantized in a standard mode:
 
chipwig2wig [InputFile] [OutputFile] -l

6.  Decompress the whole file that has been quantized in a random access mode:
 
chipwig2wig [InputFile] [OutputFile] -qb

7. Decompress a subsequence of a file that has been quantized in a random access mode:

chipwig2wig [InputFile] [OutputFile] -sl chr1 10001 11051

Similar to the random access in the lossless mode, this command returns 3 files:

1. Outputfile which contains the information of chromosome ChrName for locations between Query Start and Query End.

2. OutpufileSeq which is the decompressed file of the block(s) containing the information of chromosome ChrName for locations between Query Start and Query End.

3. OutputileSummarySequence is the file consisting of summary statistics (min, max, mean, std) of the average read densities of chromosome ChrName for locations between Query Start and Query End.
 
                 
                                         example(lossy)

1. Compress a file using non-uniform quantization in standard mode. The threshold is 50 and the number of quantization levels M is 50.

$ wig2chipwig in.wig out.chipwig -n1

2. Compress a file using uniform quantization in standard mode, with threshold 50 and 50 quantization levels. 

$ wig2chipwig in.wig out.chipwig -u 50 50

3. Compress a file allowing random query in the future with nonuniform quantization and the block size 16. The threshold is 50 and the number of quantization levels is 50:

$ wig2chipwig in.wig out.chipwig -nr1 16

4. Compress a file allowing random query in the future with uniform quantization: threshold=50, number of quantization levels=50 and the block size 16:

$ wig2chipwig in.wig out.chipwig -ur 50 50 16

5. Decompress a file that has been compressed in the standard lossy mode (i.e. the original file has been quantized by nonuniform or uniform quantization in a standard mode):

$ chipwig2wig in.chipwig out.wig -l

6. Decompress a file that has been compressed in the random access lossy mode (i.e. the original file has been quantized by nonuniform or uniform quantization in a random access mode):

$ chipwig2wig in.chipwig out.wig -qb

7. Decompress a subsequence of file that has been compressed in the random access lossy mode (i.e. the original file has been quantized by nonuniform or uniform quantization and randm access was enabled):

$ chipwig2wig in.chipwig out.wig -sl chr1 10001 11051



                                                       Notes:

1. ChIPWig in the lossless standard mode preserves 4 digits after the decimal point. If your Wig file contains numerical values with more than three decimal digits, there may be rare rounding errors when compressed in the random query mode. No rounding errors occur during decompression when the precision of the values is less than four digits. In the lossy mode, quantized data are represented in 2 digits after the decimal point and henece, ChIPWig preservs 2 digits after the decimal point.

2. Some Wig files may appear in single column format in which case it is recommended to add a regular (or custom) location column.

3. Note that in order to have random access to a subsequence in the compressed file, the original chIP-seq file has to be compressed in a random access mode (block-wise) not in a standard mode.
