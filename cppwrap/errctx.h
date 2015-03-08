#ifndef ERRCTX_H
#define ERRCTX_H

#include <string>
#include <map>

class ErrorCtx
{
public:

	std::string errorTextDesc(int errorId);

	int putError(const std::string desc);
private:
	int m_errorId;
	std::map<int, std::string> m_errors;
};

int makeGetErrorCtx(unsigned long *errorCtx);

void closeErrorCtx(unsigned long errorCtx);

int getError(unsigned long errorCtx, int errorId, char *buf, unsigned long bufSize);

#endif // ERRCTX_H
