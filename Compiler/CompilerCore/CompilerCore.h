// CompilerCore.h

#pragma once

#pragma once

#include "windows.h"

using namespace System;

#include "LexAnalyzer.h"
#include "ErrorModule.h"

using namespace System;

namespace compilerCore {

	public ref class Manager
	{
		// TODO: Add your methods for this class here.
	private:
		lexAnalyzer* m_lexAnalyzer;     // LEX ANALYZER INSTANCE
		errorModule^ m_errorModule;		// ERRORS MODULE
		void lexAnalysis(String ^ sourceCode);
		cli::array<String ^> ^ getCompilationDetails();

	public:
		Manager();
		~Manager();
		cli::array<String^>^ compileProgram(String^ sourceCode);
	};
}
