#pragma once

#include "windows.h"
#include "vcclr.h"
#include "ErrorModule.h"
#include "Token.h"

using namespace System;

#include <map>
#include <vector>
#include <stack>

using msclr::gcroot;
using std::string;
using std::map;
using std::vector;

namespace compilerCore
{
#define LEX_ERROR_INVALID_CHARACTER         "Invalid character"
#define LEX_ERROR_STRING_NOT_CLOSED         "String constant not closed"
#define LEX_ERROR_COMMENT_NOT_CLOSED        "Comment not closed"
#define LEX_ERROR_INVALID_FLOAT             "Invalid floating point number. Digit expected"
#define LEX_ERROR_INVALID_LOGICAL_OP_AND    "Invalid logical 'AND' operator. "
#define LEX_ERROR_INVALID_LOGICAL_OP_OR     "Invalid logical 'OR' operator."
#define LEX_ERROR_INVALID_STATE             "Internal error. Invalid state."

	// LEX analyzer class
	class lexAnalyzer
	{
	private:
		gcroot<errorModule^> m_errorModule;
		map<string, string> m_Keywords;
		vector<token*> m_Tokens;

	public:
		lexAnalyzer(errorModule^);
		~lexAnalyzer();
		bool parseSourceCode(const char*);
		void reset();
		void getTokens(vector<token*>*) const;
	};
}