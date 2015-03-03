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

#include <map>
#include <memory>

extern "C"
{
	#include "export.h"
}

class ErrorCtx
{
public:

	std::string errorTextDesc(int errorId)
	{
		std::string buf;
		auto it = m_errors.find(errorId);
		if (it != m_errors.end())
		{
			//const ErrorDesc & desc = ;
			buf = (*it).second;
			m_errors.erase(it);
		}
		return buf;
	}

	int putError(const std::string desc)
	{
		m_errors[++m_errorId] = desc;
		return m_errorId;
	}
private:
	int m_errorId;
	std::map<int, std::string> m_errors;
};


int makeGetErrorCtx(unsigned long * errorCtx)
{
	try
	{
		ErrorCtx * ctx = new ErrorCtx();
		*errorCtx = (unsigned long)ctx;
		return true;
	}
	catch(...)
	{
		return false;
	}
}

void closeErrorCtx(unsigned long errorCtx)
{
	ErrorCtx * ctx = (ErrorCtx *)errorCtx;
	delete ctx;
}

int getError(unsigned long errorCtx, int errorId, char * buf, unsigned long bufSize)
{
	try
	{
		ErrorCtx * ctx = (ErrorCtx *)errorCtx;
		std::string desc = ctx->errorTextDesc(errorId);
		strncpy(buf, desc.c_str(), bufSize);
		return true;
	}
	catch(...)
	{
		return false;
	}
}

struct DataSetContext
{
	DcmFileFormat dsFile;

	DcmDataset * ds;
};

int openDcmtkDataSet(unsigned long errorCtx, const char * fileName, unsigned long * rvDataSetCtx)
{
	ErrorCtx * errCtx = (ErrorCtx *)errorCtx;
	DataSetContext * ctx = 0;
	try
	{
		ctx = new DataSetContext();
		OFCondition cond;
		cond = ctx->dsFile.loadFile(fileName, EXS_Unknown, EGL_noChange, DCM_MaxReadLength);
		if (cond.bad())
			return errCtx->putError(cond.text());

		ctx->ds = ctx->dsFile.getDataset();
		//DataSetContext * ctx = new DataSetContext();
		//ctx->dsFile.loadFile(fileName, EXS_Unknown, EGL_noChange, DCM_MaxReadLength);
		*rvDataSetCtx = (unsigned long)ctx;

	}
	catch(const std::exception & ex)
	{
		if (ctx) delete ctx;
		return errCtx->putError(ex.what());
	}

	return 0;
}

int testPrintTag(unsigned long errorCtx, unsigned long dataSetCtx, unsigned short g, unsigned short e)
{
	ErrorCtx * errCtx = (ErrorCtx *)errorCtx;
	try
	{
		DataSetContext * ctx = (DataSetContext*)dataSetCtx;
		DcmDataset * ds = ctx->ds;
		OFCondition cond;

		DcmElement* element=0;
		cond = ds->findAndGetElement(DcmTagKey(e, g), element);
		if (cond.bad())
			return errCtx->putError(cond.text());
		else
		{
			OFString str;
			cond = element->getOFString(str, 0, true);
			if (cond.bad())
				return errCtx->putError(cond.text());

			std::cout << str << "\n";
		}
	}
	catch(const std::exception & ex)
	{
		return errCtx->putError(ex.what());
	}
	return 0;
}

int closeDcmtkDataSet(unsigned long errorCtx, unsigned long dataSetCtx)
{
	ErrorCtx * errCtx = (ErrorCtx *)errorCtx;
	try
	{
		DataSetContext * ctx = (DataSetContext*)dataSetCtx;
		delete ctx;
	}
	catch(const std::exception & ex)
	{
		return errCtx->putError(ex.what());
	}
	return 0;
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


