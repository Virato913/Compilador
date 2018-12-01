#pragma once

#include "ErrorModule.h"
#include "LexAnalyzer.h"
#include "SemAnalyzer.h"
#include "SymTable.h"
#include "SynState_Program.h"

using namespace System;

namespace compilerCore
{
	class synAnalyzer
	{
	private:
		lexAnalyzer* m_lexAnalyzer;
		semAnalyzer* m_semAnalyzer;
		gcroot<errorModule^> m_errorModule;
		symTable* m_symTable;
	public:
		synAnalyzer(lexAnalyzer* lexAnalyzer, semAnalyzer* semAnalyzer, errorModule^ errorModule);
		~synAnalyzer();
		bool checkSyntax();
		void getSymbols(map<string, globalNode>* symbols);
	};
}
