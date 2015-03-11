#ifndef ERRCTX_H
#define ERRCTX_H

#include <string>
#include <map>

class ErrorCtx
{
public:
	ErrorCtx();

	std::string errorTextDesc(int errorId);

	int putError(const std::string desc);
private:
	int m_errorId;
	std::map<int, std::string> m_errors;
};

#define CHECK_EXCEPTION \
	catch (const std::exception &ex) \
	{ \
		return errCtx->putError(ex.what()); \
	} \
	catch(...) \
	{ \
		return errCtx->putError("unknown exception"); \
	}


#endif // ERRCTX_H
