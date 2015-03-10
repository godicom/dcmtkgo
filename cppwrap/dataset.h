#ifndef DATASET_H
#define DATASET_H

#include <memory>

struct DataSetContext
{
	DcmFileFormat dsFile;
	std::unique_ptr<DcmDataset> ds;
};

#endif // DATASET_H
