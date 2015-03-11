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
#include <dcmtk/dcmdata/dcerror.h>

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

int saveDcmtkDatasetToMemory(unsigned long errorCtx, unsigned long dataSetCtx,
							 unsigned char *buf,
							 unsigned int bufSize,
							 unsigned long int * writtenLength,
							 int transfer)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	(void)errCtx;
	try
	{
		DatasetContext *ctx = (DatasetContext *)dataSetCtx;
		DcmDataset & ds = *ctx->ds.get();


		DcmOutputBufferStream stream(buf, bufSize);
		std::cout << "before write call\n";
		std::cout.flush();

		OFCondition cond = ds.write(stream, (E_TransferSyntax)transfer,
									EET_ExplicitLength, 0, EGL_withGL,
									EPD_withoutPadding);

		std::cout << "after write call\n";
		if (cond.bad())
			return errCtx->putError(cond.text());
		stream.flush();
		*writtenLength = stream.tell();
		std::cout << "after flush\n";
		std::cout.flush();
	}
	CHECK_EXCEPTION
	return 0;
}

int createDatasetFromMemory(unsigned long errorCtx, unsigned long *rvDatasetCtx, const unsigned char *buf, unsigned int bufSize, int transfer)
{
	ErrorCtx *errCtx = (ErrorCtx *)errorCtx;
	DatasetContext *ctx = 0;
	DcmDataset * ds = 0;
	try
	{
		DcmInputBufferStream stream;
		stream.setBuffer(buf, bufSize);
		stream.setEos();
		ds = new DcmDataset();
		ds->transferInit();
		OFCondition cond = ds->read(stream, (E_TransferSyntax)transfer, EGL_withGL, bufSize);
		ds->transferEnd();
		if (cond.bad())
			return errCtx->putError(cond.text());

		ctx = new DatasetContext();
		ctx->ds.reset(ds);
		*rvDatasetCtx = (unsigned long)ctx;
	}
	catch (const std::exception &ex)
	{
		if (ds) delete ds;
		if (ctx) delete ctx;
		return errCtx->putError(ex.what());
	}
	catch(...)
	{
		if (ds) delete ds;
		if (ctx) delete ctx;
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
