
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
struct SetArrayCallSwitcher{
	SetArrayCallSwitcher(DcmDataset *, const DcmTagKey &, T * , unsigned long , OFCondition & )
	{
		assert(false);//must be never called
	}
};

template<> struct SetArrayCallSwitcher<const unsigned short *>{
	SetArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const unsigned short * t, unsigned long length, OFCondition & cond){
		cond = ds->putAndInsertUint16Array(tag, t, length);
}};

template<> struct SetArrayCallSwitcher<const unsigned char *>{
	SetArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const unsigned char * t, unsigned long length, OFCondition & cond){
		cond = ds->putAndInsertUint8Array(tag, t, length);
}};

template<> struct SetArrayCallSwitcher<const short *>{
	SetArrayCallSwitcher(DcmDataset * ds, const DcmTagKey & tag, const short * t, unsigned long length, OFCondition & cond){
		cond = ds->putAndInsertSint16Array(tag, t, length);
}};


template<class T>
int setArray(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, T* array, unsigned long length)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	try
	{
		DataSetContext *ctx = (DataSetContext *)dataSetCtx;
		DcmDataset *ds = ctx->ds;
		OFCondition cond;

		unsigned short e = g_e & 0xFFFF;
		unsigned short g = (g_e & 0xFFFF0000) >> 16;

		SetArrayCallSwitcher<T>(ds, DcmTagKey(g, e), array, length, cond);
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

int setUint16Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const unsigned short* array, unsigned long length){
	return setArray(errorCtx, dataSetCtx, g_e, array, length);
}

int setSint16Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const short* array, unsigned long length){
	return setArray(errorCtx, dataSetCtx, g_e, array, length);
}

int setUint8Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const unsigned char* array, unsigned long length){
	return setArray(errorCtx, dataSetCtx, g_e, array, length);
}
