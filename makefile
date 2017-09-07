all: parameters.h arithmetic.h ChIPWig2Wig.cpp ProbabilityDist.cpp UniQuantizer.cpp NonUniQuantizer1.cpp NonUniQuantizer2.cpp NonUniQuantizer3.cpp GetChr.cpp Multiply100UQ.cpp Multiply100UQR.cpp Multiply100NUQ.cpp Multiply100NUQR.cpp CountLoc.cpp CountLoc1.cpp CountLoc2.cpp CountVal.cpp De_RunLength.cpp decoder.cpp DiffCoding2.cpp DiffCoding2L.cpp DiffLoc1Seq.cpp DiffLoc2Seq.cpp  encoder.cpp encoderRA.cpp fmerge.cpp fmergeRA.cpp fsplit.c fsplitRA.cpp getblock.cpp getblockQ.cpp getseq.cpp getseq2.cpp  merge.cpp Multiply1000.cpp Multiply1000RA.cpp partial_unblock.cpp partial_unblockL.cpp RecordValues.cpp  RunLength.cpp to_wig.cpp to_wigRA.cpp to_wig_Lossy.cpp to_wigRA_P.cpp to_wig_LossyRA_P.cpp to_wig_LossyRA.cpp unblock.cpp unblockL.cpp ValMatlab.cpp Wig2ChIPWig.cpp
	g++ -o  wig2chipwig Wig2ChIPWig.cpp -lm -g -w
	g++ -o  chipwig2wig ChIPWig2Wig.cpp -lm -g -w
	

