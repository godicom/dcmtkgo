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

#endif // ERRCTX_H
