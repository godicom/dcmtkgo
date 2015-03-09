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
struct PutCallSwither{
	PutCallSwither(DcmDataset *, const DcmTagKey &, T , OFCondition & )
	{
		assert(false);//must be never called
	}
};

template<> struct PutCallSwither<float>{
	PutCallSwither(DcmDataset *ds, const DcmTagKey & tag, float value, OFCondition & cond){
		cond = ds->putAndInsertFloat32(tag, value);
}};

template<> struct PutCallSwither<double>{
	PutCallSwither(DcmDataset *ds, const DcmTagKey & tag, double value, OFCondition & cond){
		cond = ds->putAndInsertFloat64(tag, value);
}};

template<> struct PutCallSwither<int>{
	PutCallSwither(DcmDataset *ds, const DcmTagKey & tag, int value, OFCondition & cond){
		cond = ds->putAndInsertSint32(tag, value);
}};

template<> struct PutCallSwither<unsigned int>{
	PutCallSwither(DcmDataset *ds, const DcmTagKey & tag, unsigned int value, OFCondition & cond){
		cond = ds->putAndInsertUint32(tag, value);
}};

template<> struct PutCallSwither<short>{
	PutCallSwither(DcmDataset *ds, const DcmTagKey & tag, short value, OFCondition & cond){
		cond = ds->putAndInsertSint16(tag, value);
}};

template<> struct PutCallSwither<unsigned short>{
	PutCallSwither(DcmDataset *ds, const DcmTagKey & tag, unsigned short value, OFCondition & cond){
		cond = ds->putAndInsertUint16(tag, value);
}};

template<class T>
int setValue(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, T value)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	try
	{
		DataSetContext *ctx = (DataSetContext *)dataSetCtx;
		DcmDataset *ds = ctx->ds;
		OFCondition cond;

		unsigned short e = g_e & 0xFFFF;
		unsigned short g = (g_e & 0xFFFF0000) >> 16;

		PutCallSwither<T>(ds, DcmTagKey(g, e), value, cond);
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

int setFloat32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, float value){
	return setValue(errorCtx, dataSetCtx, g_e, value);
}

int setFloat64(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, double value){
	return setValue(errorCtx, dataSetCtx, g_e, value);
}

int setUint32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned int value){
	return setValue(errorCtx, dataSetCtx, g_e, value);
}

int setSint32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, int value){
	return setValue(errorCtx, dataSetCtx, g_e, value);
}

int setUint16(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned short value){
	return setValue(errorCtx, dataSetCtx, g_e, value);
}

int setSint16(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, short value){
	return setValue(errorCtx, dataSetCtx, g_e, value);
}
