#pragma once

#include "vcclr.h"
#include "ErrorModule.h"
#include "ExpLog.h"
#include "Token.h"

#include <vector>

using namespace System;

namespace compilerCore
{
	class semAnalyzer
	{
	private:
		msclr::gcroot<errorModule^> m_errorModule;
		std::vector<expLog*> m_expLogVec;
		
	public:
		semAnalyzer(errorModule^ errorModule);
		~semAnalyzer();
		void addExpLog(std::vector<token*> expLogVec);
		void checkExpressions();
	};
}
