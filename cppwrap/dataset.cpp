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
#include <dcmtk/dcmdata/dcistrmb.h>

#include <exception>

extern "C"
{
#include "export.h"
}

#include "dataset.h"
#include "errctx.h"

int createEmptyDcmtkDataSet(unsigned long errorCtx, unsigned long *rvDataSetCtx)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	DataSetContext *ctx = 0;
	try
	{
		ctx = new DataSetContext();
		ctx->ds.reset(new DcmDataset());
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

int openDcmtkDataSet(unsigned long errorCtx, const char *fileName, unsigned long *rvDataSetCtx)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	DataSetContext *ctx = 0;
	try
	{
		DcmFileFormat format;
		OFCondition cond = format.loadFile(fileName/*, EXS_Unknown, EGL_noChange, DCM_MaxReadLength*/);
		if (cond.bad())
			return errCtx->putError(cond.text());

		ctx = new DataSetContext();
		ctx->ds.reset(format.getAndRemoveDataset());
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

int createDatasetFromMemory(unsigned long errorCtx, unsigned long *rvDataSetCtx, const char * buf, unsigned int bufSize)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	DataSetContext *ctx = 0;
	try
	{
		DcmInputBufferStream stream;
		stream.setBuffer(buf, bufSize);
		DcmFileFormat format;

		OFCondition cond = format.read(stream);
		if (cond.bad())
			return errCtx->putError(cond.text());

		ctx = new DataSetContext();
		ctx->ds.reset(format.getAndRemoveDataset());
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

int saveDcmtkDataSet(unsigned long errorCtx, unsigned long dataSetCtx, const char * fileName, int transfer)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	(void)errCtx;
	try
	{
		DataSetContext *ctx = (DataSetContext *)dataSetCtx;
		ctx->ds->transferInit();
		DcmFileFormat format(ctx->ds.get());
		OFCondition cond = format.saveFile(fileName, (E_TransferSyntax)transfer);
		if (cond.bad())
			return errCtx->putError(cond.text());
		ctx->ds->transferEnd();
	}
	CHECK_EXCEPTION
	return 0;
}

int closeDcmtkDataSet(unsigned long errorCtx, unsigned long dataSetCtx)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	(void)errCtx;
	try
	{
		DataSetContext *ctx = (DataSetContext *)dataSetCtx;
		delete ctx;
	}
	CHECK_EXCEPTION
	return 0;
}
