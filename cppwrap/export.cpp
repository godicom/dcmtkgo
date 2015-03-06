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
#include <exception>

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



int makeGetErrorCtx(unsigned long *errorCtx)
{
	try
	{
		ErrorCtx *ctx = new ErrorCtx();
		*errorCtx = (unsigned long)ctx;
		return 0;
	}
	catch (std::exception &e)
	{
		std::cout << "unknown exception " << e.what() << "\n";
	}
	catch (...)
	{
		std::cout << "unknown exception\n";
	}
	return 1;
}

void closeErrorCtx(unsigned long errorCtx)
{
	ErrorCtx *ctx = (ErrorCtx *)errorCtx;
	delete ctx;
}

// int getUint32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned int * rvValue)
// {
//  return 0;
// }

int getError(unsigned long errorCtx, int errorId, char *buf, unsigned long bufSize)
{
	try
	{
		ErrorCtx *ctx = (ErrorCtx *)errorCtx;
		std::string desc = ctx->errorTextDesc(errorId);
		strncpy(buf, desc.c_str(), bufSize);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

struct DataSetContext
{
	DcmFileFormat dsFile;
	DcmDataset *ds;
};

int openDcmtkDataSet(unsigned long errorCtx, const char *fileName, unsigned long *rvDataSetCtx)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	DataSetContext *ctx = 0;
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
	catch (const std::exception &ex)
	{
		if (ctx) delete ctx;
		return errCtx->putError(ex.what());
	}

	std::cerr << "Open ds done" << std::endl;
	return 0;
}
static int i = 0;

int dummySum(int a, int b)
{
	return a + b + ++i;
}

enum DCMItemsTypes
{
	DCMfloat,
	DCMdouble,
	DCMUint32,
	DCMSint32,
	DCMUint16,
	DCMSint16,
	DCMSint8
};

template<class T>
struct CallSwither{
	CallSwither(DcmDataset *,DcmTagKey &, T & , OFCondition & )
	{
		assert(false);//must be nvere called
	}
};

template<> struct CallSwither<float>{
	CallSwither(DcmDataset *ds, DcmTagKey & tag, float & value, OFCondition & cond)	{
		cond = ds->findAndGetFloat32(tag, value);
}};

template<> struct CallSwither<double>{
	CallSwither(DcmDataset *ds, DcmTagKey & tag, double & value, OFCondition & cond)	{
		cond = ds->findAndGetFloat64(tag, value);
}};

template<> struct CallSwither<int>{
	CallSwither(DcmDataset *ds, DcmTagKey & tag, int & value, OFCondition & cond)	{
		cond = ds->findAndGetSint32(tag, value);
}};

template<> struct CallSwither<unsigned int>{
	CallSwither(DcmDataset *ds, DcmTagKey & tag, unsigned int & value, OFCondition & cond)	{
		cond = ds->findAndGetUint32(tag, value);
}};

template<> struct CallSwither<short>{
	CallSwither(DcmDataset *ds, DcmTagKey & tag, short & value, OFCondition & cond)	{
		cond = ds->findAndGetSint16(tag, value);
}};

template<> struct CallSwither<unsigned short>{
	CallSwither(DcmDataset *ds, DcmTagKey & tag, unsigned short & value, OFCondition & cond)	{
		cond = ds->findAndGetUint16(tag, value);
}};

template<> struct CallSwither<unsigned char>{
	CallSwither(DcmDataset *ds, DcmTagKey & tag, unsigned char & value, OFCondition & cond)	{
		cond = ds->findAndGetUint8(tag, value);
}};

template<class T>
int getValue(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, T *rvValue)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	try
	{
		DataSetContext *ctx = (DataSetContext *)dataSetCtx;
		DcmDataset *ds = ctx->ds;
		OFCondition cond;

		// TODO: check order
		unsigned short e = g_e & 0xFFFF;
		unsigned short g = (g_e & 0xFFFF0000) >> 16;

		DcmTagKey tag(g, e);

		CallSwither<T>(ds, tag, *rvValue, cond);
		if (cond.bad())
			return errCtx->putError(cond.text());
	}
	catch (const std::exception &ex)
	{
		return errCtx->putError(ex.what());
	}
	catch (...)
	{
		return errCtx->putError("unknown exception");
	}
	return 0;
}

int getFloat32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, float * rvValue) {
	return getValue(errorCtx, dataSetCtx, g_e, rvValue);
}

int getFloat64(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, double * rvValue) {
	return getValue(errorCtx, dataSetCtx, g_e, rvValue);
}

int getUint32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned int *rvValue) {
	return getValue(errorCtx, dataSetCtx, g_e, rvValue);
}

int getSint32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, int *rvValue) {
	return getValue(errorCtx, dataSetCtx, g_e, rvValue);
}

int getUint16(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned short *rvValue) {
	return getValue(errorCtx, dataSetCtx, g_e, rvValue);
}

int getSint16(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, short *rvValue) {
	return getValue(errorCtx, dataSetCtx, g_e, rvValue);
}

int getUint8(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned char *rvValue) {
	return getValue(errorCtx, dataSetCtx, g_e, rvValue);
}

int getSint8(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char *rvValue) {
	return getValue(errorCtx, dataSetCtx, g_e, rvValue);
}

int getString(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char *buf, int bufSize)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	try
	{
		DataSetContext *ctx = (DataSetContext *)dataSetCtx;
		DcmDataset *ds = ctx->ds;
		OFCondition cond;

		DcmElement *element = 0;
		// TODO: check order
		unsigned short e = g_e & 0xFFFF;
		unsigned short g = (g_e & 0xFFFF0000) >> 16;

		cond = ds->findAndGetElement(DcmTagKey(g, e), element);
		if (cond.bad())
			return errCtx->putError(cond.text());
		else
		{
			OFString str;
			cond = element->getOFString(str, 0, true);
			if (cond.bad())
				return errCtx->putError(cond.text());

			strncpy(buf, str.data(), bufSize);
		}
	}
	catch (const std::exception &ex)
	{
		return errCtx->putError(ex.what());
	}
	return 0;
}

int testPrintTag(unsigned long errorCtx, unsigned long dataSetCtx, unsigned short g, unsigned short e)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	try
	{
		DataSetContext *ctx = (DataSetContext *)dataSetCtx;
		DcmDataset *ds = ctx->ds;
		OFCondition cond;

		DcmElement *element = 0;
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
	catch (const std::exception &ex)
	{
		return errCtx->putError(ex.what());
	}
	return 0;
}

int closeDcmtkDataSet(unsigned long errorCtx, unsigned long dataSetCtx)
{
	std::cout << "begin close dataset from lib\n";
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	try
	{
		DataSetContext *ctx = (DataSetContext *)dataSetCtx;
		delete ctx;
	}
	catch (const std::exception &ex)
	{
		return errCtx->putError(ex.what());
	}
	std::cout << "end close dataset from lib\n";
	return 0;
}


void printDCMTags(const char *fileName)
{
	std::cout << "filepath" << fileName << "\n";
	DcmDataset *ds = 0;
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
		DcmElement *element = 0;
		cond = ds->findAndGetElement(DCM_SOPClassUID, element);
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


