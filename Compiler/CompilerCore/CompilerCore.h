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
		void lexAnalysis(String^);
		cli::array<String^>^ getCompilationDetails();
		cli::array<cli::array<String^>^, 2>^ getCompDetails();

	public:
		Manager();
		~Manager();
		cli::array<String^>^ compileProgram(String^ sourceCode);
		cli::array<cli::array<String^>^, 2>^ compile(String^ sourceCode);
	};
}
