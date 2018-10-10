#pragma once

#include "ErrorModule.h"
#include "LexAnalyzer.h"
#include "SymTable.h"

using namespace System;

namespace compilerCore
{
	class synAnalyzer
	{
	private:
		lexAnalyzer* m_lexAnalyzer;
		gcroot<errorModule^> m_errorModule;
		symTable* symTable;
	public:
		synAnalyzer(lexAnalyzer* lexAnalyzer, errorModule^ errorModule);
		~synAnalyzer();
		bool checkSyntax();
	};
}
