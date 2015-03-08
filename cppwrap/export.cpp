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
		std::cerr << "unknown exception " << e.what() << "\n";
	}
	catch (...)
	{
		std::cerr << "unknown exception\n";
	}
	return 1;
}

void closeErrorCtx(unsigned long errorCtx)
{
	ErrorCtx *ctx = (ErrorCtx *)errorCtx;
	delete ctx;
}

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
		*rvDataSetCtx = (unsigned long)ctx;

	}
	catch (const std::exception &ex)
	{
		if (ctx) delete ctx;
		return errCtx->putError(ex.what());
	}
	catch(...)
	{
		return errCtx->putError("unknown exception");
	}
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
	CallSwither(DcmDataset *, const DcmTagKey &, T & , OFCondition & )
	{
		assert(false);//must be never called
	}
};

template<> struct CallSwither<float>{
	CallSwither(DcmDataset *ds, const DcmTagKey & tag, float & value, OFCondition & cond)	{
		cond = ds->findAndGetFloat32(tag, value);
}};

template<> struct CallSwither<double>{
	CallSwither(DcmDataset *ds, const DcmTagKey & tag, double & value, OFCondition & cond)	{
		cond = ds->findAndGetFloat64(tag, value);
}};

template<> struct CallSwither<int>{
	CallSwither(DcmDataset *ds, const DcmTagKey & tag, int & value, OFCondition & cond)	{
		cond = ds->findAndGetSint32(tag, value);
}};

template<> struct CallSwither<unsigned int>{
	CallSwither(DcmDataset *ds, const DcmTagKey & tag, unsigned int & value, OFCondition & cond)	{
		cond = ds->findAndGetUint32(tag, value);
}};

template<> struct CallSwither<short>{
	CallSwither(DcmDataset *ds, const DcmTagKey & tag, short & value, OFCondition & cond)	{
		cond = ds->findAndGetSint16(tag, value);
}};

template<> struct CallSwither<unsigned short>{
	CallSwither(DcmDataset *ds, const DcmTagKey & tag, unsigned short & value, OFCondition & cond)	{
		cond = ds->findAndGetUint16(tag, value);
}};

template<> struct CallSwither<unsigned char>{
	CallSwither(DcmDataset *ds, const DcmTagKey & tag, unsigned char & value, OFCondition & cond)	{
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

		unsigned short e = g_e & 0xFFFF;
		unsigned short g = (g_e & 0xFFFF0000) >> 16;

		CallSwither<T>(ds, DcmTagKey(g, e), *rvValue, cond);
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

enum GetStringMode
{
	SimpleString,
	ArrayString
};

int getCustomString(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char *buf, int bufSize, GetStringMode mode)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	try
	{
		DataSetContext *ctx = (DataSetContext *)dataSetCtx;
		DcmDataset *ds = ctx->ds;
		OFCondition cond;

		unsigned short e = g_e & 0xFFFF;
		unsigned short g = (g_e & 0xFFFF0000) >> 16;

		OFString str;
		if (mode == SimpleString)
		{
			cond = ds->findAndGetOFString(DcmTagKey(g, e), str);
		}
		else if (mode == ArrayString)
		{
			cond = ds->findAndGetOFStringArray(DcmTagKey(g, e), str);
		}
		else
		{
			assert(false);
		}
		if (cond.bad())
			return errCtx->putError(cond.text());
		strncpy(buf, str.data(), bufSize);
	}
	catch (const std::exception &ex)
	{
		return errCtx->putError(ex.what());
	}
	catch(...)
	{
		return errCtx->putError("unknown exception");
	}
	return 0;
}

int getString(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char *buf, int bufSize)
{
	return getCustomString(errorCtx, dataSetCtx, g_e, buf, bufSize, SimpleString);
}

int getStringArray(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char * buf, int bufSize){
	return getCustomString(errorCtx, dataSetCtx, g_e, buf, bufSize, ArrayString);
//	return getArray(errorCtx, dataSetCtx, g_e, rvValueArray, rvCount);
}

template<class T>
struct ArrayCallSwitcher{
	ArrayCallSwitcher(DcmDataset *, const DcmTagKey &, T * , unsigned long * , OFCondition & )
	{
		assert(false);//must be never called
	}
};

template<> struct ArrayCallSwitcher<const unsigned short *>{
	ArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const unsigned short ** t, unsigned long * length, OFCondition & cond){
		cond = ds->findAndGetUint16Array(tag, *t, length);
}};

template<> struct ArrayCallSwitcher<const unsigned int *>{
	ArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const unsigned int ** t, unsigned long * length, OFCondition & cond){
		cond = ds->findAndGetUint32Array(tag, *t, length);
}};

template<> struct ArrayCallSwitcher<const unsigned char *>{
	ArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const unsigned char ** t, unsigned long * length, OFCondition & cond){
		cond = ds->findAndGetUint8Array(tag, *t, length);
}};

template<> struct ArrayCallSwitcher<const short *>{
	ArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const short ** t, unsigned long * length, OFCondition & cond){
		cond = ds->findAndGetSint16Array(tag, *t, length);
}};

template<> struct ArrayCallSwitcher<const int *>{
	ArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const int ** t, unsigned long * length, OFCondition & cond){
		cond = ds->findAndGetSint32Array(tag, *t, length);
}};

template<> struct ArrayCallSwitcher<const float *>{
	ArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const float ** t, unsigned long * length, OFCondition & cond){
		cond = ds->findAndGetFloat32Array(tag, *t, length);
}};

template<> struct ArrayCallSwitcher<const double *>{
	ArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const double ** t, unsigned long * length, OFCondition & cond){
		cond = ds->findAndGetFloat64Array(tag, *t, length);
}};

template<class T>
int getArray(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, T* rvValueArray, unsigned long * rvCount)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	try
	{
		DataSetContext *ctx = (DataSetContext *)dataSetCtx;
		DcmDataset *ds = ctx->ds;
		OFCondition cond;

		unsigned short e = g_e & 0xFFFF;
		unsigned short g = (g_e & 0xFFFF0000) >> 16;

		ArrayCallSwitcher<T>(ds, DcmTagKey(g, e), rvValueArray, rvCount, cond);
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

int getFloat32Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const float** rvValueArray, unsigned long * rvCount){
	return getArray(errorCtx, dataSetCtx, g_e, rvValueArray, rvCount);
}

int getFloat64Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const double** rvValueArray, unsigned long * rvCount){
	return getArray(errorCtx, dataSetCtx, g_e, rvValueArray, rvCount);
}

int getUint32Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const unsigned int** rvValueArray, unsigned long * rvCount){
	return getArray(errorCtx, dataSetCtx, g_e, rvValueArray, rvCount);
}

int getSint32Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const int** rvValueArray, unsigned long * rvCount){
	return getArray(errorCtx, dataSetCtx, g_e, rvValueArray, rvCount);
}

int getUint16Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const unsigned short** rvValueArray, unsigned long * rvCount){
	return getArray(errorCtx, dataSetCtx, g_e, rvValueArray, rvCount);
}

int getSint16Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const short** rvValueArray, unsigned long * rvCount){
	return getArray(errorCtx, dataSetCtx, g_e, rvValueArray, rvCount);
}

int getUint8Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const unsigned char** rvValueArray, unsigned long * rvCount){
	return getArray(errorCtx, dataSetCtx, g_e, rvValueArray, rvCount);
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
	catch(...)
	{
		return errCtx->putError("unknown exception");
	}
	std::cout << "end close dataset from lib\n";
	std::cout.flush();
	return 0;
}

