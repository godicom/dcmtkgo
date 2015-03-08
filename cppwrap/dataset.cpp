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

#include "dataset.h"
#include "errctx.h"

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
