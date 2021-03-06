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
struct GetCallSwither{
	GetCallSwither(DcmDataset *, const DcmTagKey &, T & , OFCondition & )
	{
		assert(false);//must be never called
	}
};

template<> struct GetCallSwither<float>{
	GetCallSwither(DcmDataset *ds, const DcmTagKey & tag, float & value, OFCondition & cond)	{
		cond = ds->findAndGetFloat32(tag, value);
}};

template<> struct GetCallSwither<double>{
	GetCallSwither(DcmDataset *ds, const DcmTagKey & tag, double & value, OFCondition & cond)	{
		cond = ds->findAndGetFloat64(tag, value);
}};

template<> struct GetCallSwither<int>{
	GetCallSwither(DcmDataset *ds, const DcmTagKey & tag, int & value, OFCondition & cond)	{
		cond = ds->findAndGetSint32(tag, value);
}};

template<> struct GetCallSwither<unsigned int>{
	GetCallSwither(DcmDataset *ds, const DcmTagKey & tag, unsigned int & value, OFCondition & cond)	{
		cond = ds->findAndGetUint32(tag, value);
}};

template<> struct GetCallSwither<short>{
	GetCallSwither(DcmDataset *ds, const DcmTagKey & tag, short & value, OFCondition & cond)	{
		cond = ds->findAndGetSint16(tag, value);
}};

template<> struct GetCallSwither<unsigned short>{
	GetCallSwither(DcmDataset *ds, const DcmTagKey & tag, unsigned short & value, OFCondition & cond)	{
		cond = ds->findAndGetUint16(tag, value);
}};

template<> struct GetCallSwither<unsigned char>{
	GetCallSwither(DcmDataset *ds, const DcmTagKey & tag, unsigned char & value, OFCondition & cond)	{
		cond = ds->findAndGetUint8(tag, value);
}};

template<class T>
int getValue(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, T *rvValue)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	try
	{
		DatasetContext *ctx = (DatasetContext *)dataSetCtx;
		OFCondition cond;

		unsigned short e = g_e & 0xFFFF;
		unsigned short g = (g_e & 0xFFFF0000) >> 16;

		GetCallSwither<T>(ctx->ds.get(), DcmTagKey(g, e), *rvValue, cond);
		if (cond.bad())
			return errCtx->putError(cond.text());
	}
	CHECK_EXCEPTION
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
