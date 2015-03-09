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

#include "dataset.h"
#include "errctx.h"

template<class T>
struct GetArrayCallSwitcher{
	GetArrayCallSwitcher(DcmDataset *, const DcmTagKey &, T * , unsigned long * , OFCondition & )
	{
		assert(false);//must be never called
	}
};

template<> struct GetArrayCallSwitcher<const unsigned short *>{
	GetArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const unsigned short ** t, unsigned long * length, OFCondition & cond){
		cond = ds->findAndGetUint16Array(tag, *t, length);
}};

template<> struct GetArrayCallSwitcher<const unsigned int *>{
	GetArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const unsigned int ** t, unsigned long * length, OFCondition & cond){
		cond = ds->findAndGetUint32Array(tag, *t, length);
}};

template<> struct GetArrayCallSwitcher<const unsigned char *>{
	GetArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const unsigned char ** t, unsigned long * length, OFCondition & cond){
		cond = ds->findAndGetUint8Array(tag, *t, length);
}};

template<> struct GetArrayCallSwitcher<const short *>{
	GetArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const short ** t, unsigned long * length, OFCondition & cond){
		cond = ds->findAndGetSint16Array(tag, *t, length);
}};

template<> struct GetArrayCallSwitcher<const int *>{
	GetArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const int ** t, unsigned long * length, OFCondition & cond){
		cond = ds->findAndGetSint32Array(tag, *t, length);
}};

template<> struct GetArrayCallSwitcher<const float *>{
	GetArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const float ** t, unsigned long * length, OFCondition & cond){
		cond = ds->findAndGetFloat32Array(tag, *t, length);
}};

template<> struct GetArrayCallSwitcher<const double *>{
	GetArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const double ** t, unsigned long * length, OFCondition & cond){
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

		GetArrayCallSwitcher<T>(ds, DcmTagKey(g, e), rvValueArray, rvCount, cond);
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
