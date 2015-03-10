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

enum StringMode
{
	SimpleString,
	ArrayString
};

int getCustomString(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char *buf, int bufSize, StringMode mode)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	try
	{
		DataSetContext *ctx = (DataSetContext *)dataSetCtx;
		DcmDataset *ds = ctx->ds.get();
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
	CHECK_EXCEPTION
	return 0;
}

int getString(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char *buf, int bufSize)
{
	return getCustomString(errorCtx, dataSetCtx, g_e, buf, bufSize, SimpleString);
}

int getStringArray(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char * buf, int bufSize){
	return getCustomString(errorCtx, dataSetCtx, g_e, buf, bufSize, ArrayString);
}

int setCustomString(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char *buf, int bufSize, StringMode mode)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	try
	{
		DataSetContext *ctx = (DataSetContext *)dataSetCtx;
		DcmDataset *ds = ctx->ds.get();
		OFCondition cond;

		unsigned short e = g_e & 0xFFFF;
		unsigned short g = (g_e & 0xFFFF0000) >> 16;

		if (mode == SimpleString)
		{
			cond = ds->putAndInsertString(DcmTagKey(g, e), buf);
		}
		else if (mode == ArrayString)
		{
			OFString str;
			str.assign(buf, bufSize);
			cond = ds->findAndGetOFStringArray(DcmTagKey(g, e), str);
		}
		else
		{
			assert(false);
		}
		if (cond.bad())
			return errCtx->putError(cond.text());
	}
	CHECK_EXCEPTION
	return 0;
}

int setStringArray(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char * buf, int bufSize){
	return setCustomString(errorCtx, dataSetCtx, g_e, buf, bufSize, ArrayString);
}

int setString(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char * buf, int bufSize)
{
	return setCustomString(errorCtx, dataSetCtx, g_e, buf, bufSize, SimpleString);
}
