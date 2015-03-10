#ifndef DATASET_H
#define DATASET_H

struct DataSetContext
{
	DcmFileFormat dsFile;
	DcmDataset *ds;
};

#endif // DATASET_H
