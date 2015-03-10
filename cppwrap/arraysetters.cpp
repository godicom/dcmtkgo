
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
	SetArrayCallSwitcher(DcmElement *, T * , unsigned long , OFCondition & )
	{
		assert(false);//must be never called
	}
};

template<> struct SetArrayCallSwitcher<const unsigned short *>{
	SetArrayCallSwitcher(DcmElement * e, const unsigned short * t, unsigned long length, OFCondition & cond){
		cond = e->putUint16Array(t, length);
}};

template<> struct SetArrayCallSwitcher<const unsigned char *>{
	SetArrayCallSwitcher(DcmElement * e, const unsigned char * t, unsigned long length, OFCondition & cond){
		cond = e->putUint8Array(t, length);
}};

template<> struct SetArrayCallSwitcher<const short *>{
	SetArrayCallSwitcher(DcmElement * e, const short * t, unsigned long length, OFCondition & cond){
		cond = e->putSint16Array(t, length);
}};

template<> struct SetArrayCallSwitcher<const int *>{
	SetArrayCallSwitcher(DcmElement * e, const int * t, unsigned long length, OFCondition & cond){
		cond = e->putSint32Array(t, length);
}};

template<> struct SetArrayCallSwitcher<const unsigned int *>{
	SetArrayCallSwitcher(DcmElement * e, const unsigned int * t, unsigned long length, OFCondition & cond){
		cond = e->putUint32Array(t, length);
}};

template<> struct SetArrayCallSwitcher<const float *>{
	SetArrayCallSwitcher(DcmElement * e, const float * t, unsigned long length, OFCondition & cond){
		cond = e->putFloat32Array(t, length);
}};

template<> struct SetArrayCallSwitcher<const double *>{
	SetArrayCallSwitcher(DcmElement * e, const double * t, unsigned long length, OFCondition & cond){
		cond = e->putFloat64Array(t, length);
}};


template<class T>
int setArray(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, T* array, unsigned long length)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	try
	{
		DatasetContext *ctx = (DatasetContext *)dataSetCtx;

		OFCondition cond;

		unsigned short e = g_e & 0xFFFF;
		unsigned short g = (g_e & 0xFFFF0000) >> 16;

		DcmElement * element = 0;
		cond = newDicomElement(element, DcmTagKey(g, e));
		if (cond.bad())
			return errCtx->putError(cond.text());
		SetArrayCallSwitcher<T>(element, array, length, cond);
		if (cond.bad())
			return errCtx->putError(cond.text());
		cond = ctx->ds->insert(element, true);
		if (cond.bad())
			return errCtx->putError(cond.text());
	}
	CHECK_EXCEPTION
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

int setFloat32Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const float* array, unsigned long length){
	return setArray(errorCtx, dataSetCtx, g_e, array, length);
}

int setFloat64Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const double* array, unsigned long length){
	return setArray(errorCtx, dataSetCtx, g_e, array, length);
}

int setUint32Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const unsigned int* array, unsigned long length){
	return setArray(errorCtx, dataSetCtx, g_e, array, length);
}

int setSint32Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const int* array, unsigned long length){
	return setArray(errorCtx, dataSetCtx, g_e, array, length);
}
