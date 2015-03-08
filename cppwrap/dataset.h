#ifndef DATASET_H
#define DATASET_H

struct DataSetContext
{
	DcmFileFormat dsFile;
	DcmDataset *ds;
};

int openDcmtkDataSet(unsigned long errorCtx, const char *fileName, unsigned long *rvDataSetCtx);

int closeDcmtkDataSet(unsigned long errorCtx, unsigned long dataSetCtx);

#endif // DATASET_H
