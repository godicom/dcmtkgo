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
#include <dcmtk/dcmdata/dcostrmb.h>

#include <exception>

extern "C"
{
#include "export.h"
}

#include "dataset.h"
#include "errctx.h"

int createEmptyDcmtkDataset(unsigned long errorCtx, unsigned long *rvDatasetCtx)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	DatasetContext *ctx = 0;
	try
	{
		ctx = new DatasetContext();
		ctx->ds.reset(new DcmDataset());
		*rvDatasetCtx = (unsigned long)ctx;

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

int openDcmtkDataset(unsigned long errorCtx, const char *fileName, unsigned long *rvDatasetCtx)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	DatasetContext *ctx = 0;
	try
	{
		DcmFileFormat format;
		OFCondition cond = format.loadFile(fileName/*, EXS_Unknown, EGL_noChange, DCM_MaxReadLength*/);
		if (cond.bad())
			return errCtx->putError(cond.text());

		ctx = new DatasetContext();
		ctx->ds.reset(format.getAndRemoveDataset());
		*rvDatasetCtx = (unsigned long)ctx;
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

int saveDcmtkDatasetToMemory(unsigned long errorCtx, unsigned long dataSetCtx, char * buf, unsigned int bufSize, int transfer)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	(void)errCtx;
	try
	{
		DatasetContext *ctx = (DatasetContext *)dataSetCtx;

		DcmFileFormat format(ctx->ds.get());
		DcmOutputBufferStream stream(buf, bufSize);

		OFCondition cond = format.write(stream, (E_TransferSyntax)transfer, EET_ExplicitLength, 0);
		if (cond.bad())
			return errCtx->putError(cond.text());

		stream.flush();

	}
	CHECK_EXCEPTION
	return 0;
}

int createDatasetFromMemory(unsigned long errorCtx, unsigned long *rvDatasetCtx, const unsigned char *buf, unsigned int bufSize)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	DatasetContext *ctx = 0;
	try
	{
		DcmInputBufferStream stream;
		stream.setBuffer(buf, bufSize);
		DcmFileFormat format;

		OFCondition cond = format.read(stream);
		if (cond.bad())
			return errCtx->putError(cond.text());

		ctx = new DatasetContext();
		ctx->ds.reset(format.getAndRemoveDataset());
		*rvDatasetCtx = (unsigned long)ctx;
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

int saveDcmtkDataset(unsigned long errorCtx, unsigned long dataSetCtx, const char * fileName, int transfer)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	(void)errCtx;
	try
	{
		DatasetContext *ctx = (DatasetContext *)dataSetCtx;

		DcmFileFormat format(ctx->ds.get());
		OFCondition cond = format.saveFile(fileName, (E_TransferSyntax)transfer);
		if (cond.bad())
			return errCtx->putError(cond.text());

	}
	CHECK_EXCEPTION
	return 0;
}

int closeDcmtkDataset(unsigned long errorCtx, unsigned long dataSetCtx)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	(void)errCtx;
	try
	{
		DatasetContext *ctx = (DatasetContext *)dataSetCtx;
		delete ctx;
	}
	CHECK_EXCEPTION
	return 0;
}
