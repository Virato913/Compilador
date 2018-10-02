#pragma once

#include "LexAnalyzer.h"
#include "ErrorModule.h"

using namespace System;

namespace compilerCore
{
	class synAnalyzer
	{
	private:
		lexAnalyzer* m_lexAnalyzer;
		gcroot<errorModule^> m_errorModule;
	public:
		synAnalyzer(lexAnalyzer* lexAnalyzer, errorModule^ errorModule);
		~synAnalyzer();
		bool checkSyntax();
	};
}