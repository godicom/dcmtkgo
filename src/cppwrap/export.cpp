#include <iostream>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcfilefo.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcerror.h>
#include <dcmtk/dcmdata/dcelem.h>
#include <dcmtk/dcmdata/dcxfer.h>
#include <dcmtk/dcmdata/dctypes.h>
#include <dcmtk/dcmdata/dcobject.h>
#include <dcmtk/ofstd/ofcond.h>

extern "C"
{
	#include "export.h"
}

int openDcmtkDataSet(const char * fileName, int64_t * rvDataSetCtx)
{
	return 0;
}

int closeDcmtkDataSet(int dataSetCtx)
{
	return 0;
}

void getErrorDescription(int errorId, char * buf, size_t bufSize)
{

}

void printDCMTags(const char * fileName)
{
	std::cout << "filepath" << fileName << "\n";
	DcmDataset * ds = 0;
	DcmFileFormat dsFile;
	OFCondition cond;
	std::cout << "before open file\n";
	cond = dsFile.loadFile(fileName, EXS_Unknown, EGL_noChange, DCM_MaxReadLength);
	if (cond.bad())
	{
		std::cout << "fail open\n";
		std::cout << cond.text();
	}
	else
	{
		ds = dsFile.getDataset();
		std::cout << "load done\n";
		DcmElement* element=0;
		cond = ds->findAndGetElement(DCM_SOPClassUID,element);
		if (cond.bad())
		{
			std::cout << "fail get element\n";
			std::cout << cond.text();
		}
		else
		{
			std::cout << "find and get done\n";
			OFString str;
			cond = element->getOFString(str, 0, true);
			if (cond.bad())
			{
				std::cout << "fail get string\n";
				std::cout << cond.text();
			}
			else
			{
				std::cout << "DCM_SOPClassUID" << str << "\n";
			}
		}
	}
	std::cout.flush();
}
