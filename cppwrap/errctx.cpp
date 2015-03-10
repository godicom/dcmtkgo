#include <iostream>
#include "errctx.h"

extern "C"
{
#include "export.h"
}

int getError(unsigned long errorCtx, int errorId, char *buf, unsigned long bufSize)
{
	try
	{
		ErrorCtx *ctx = (ErrorCtx *)errorCtx;
		std::string desc = ctx->errorTextDesc(errorId);
		strncpy(buf, desc.c_str(), bufSize);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

void closeErrorCtx(unsigned long errorCtx)
{
	ErrorCtx *ctx = (ErrorCtx *)errorCtx;
	delete ctx;
}

int makeGetErrorCtx(unsigned long *errorCtx)
{
	try
	{
		ErrorCtx *ctx = new ErrorCtx();
		*errorCtx = (unsigned long)ctx;
		return 0;
	}
	catch (std::exception &e)
	{
		std::cerr << "unknown exception " << e.what() << "\n";
	}
	catch (...)
	{
		std::cerr << "unknown exception\n";
	}
	return 1;
}

std::string ErrorCtx::errorTextDesc(int errorId)
{
	std::string buf;
	auto it = m_errors.find(errorId);
	if (it != m_errors.end())
	{
		buf = (*it).second;
		m_errors.erase(it);
	}
	return buf;
}

int ErrorCtx::putError(const std::string desc)
{
	m_errors[++m_errorId] = desc;
	return m_errorId;
}
