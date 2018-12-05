#pragma once

#include "vcclr.h"
#include "ErrorModule.h"
#include "ExpLog.h"
#include "Token.h"
#include "ExpLog.h"

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
		void addExpLog(int lineNum, string funcName, std::vector<const token*> expLogVec, string symbolToUpdate = "");
		void checkExpressions();
	};
}
