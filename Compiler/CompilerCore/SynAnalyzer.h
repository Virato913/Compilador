#pragma once

#include "ErrorModule.h"
#include "LexAnalyzer.h"
#include "SymTable.h"
#include "SynState_Program.h"

using namespace System;

namespace compilerCore
{
	class synAnalyzer
	{
	private:
		lexAnalyzer* m_lexAnalyzer;
		gcroot<errorModule^> m_errorModule;
		symTable* m_symTable;
	public:
		synAnalyzer(lexAnalyzer* lexAnalyzer, errorModule^ errorModule);
		~synAnalyzer();
		bool checkSyntax();
	};
}
