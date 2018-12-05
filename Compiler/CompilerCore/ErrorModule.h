#pragma once

#include "windows.h"

using namespace System;

namespace compilerCore
{
#define MAX_ERRORS 100

	public enum class ERROR_PHASE
	{
		UNDEFINED,
		LEXIC_ANALYZER,
		SYNTAX_ANALYZER,
		SEMANTIC_ANALYZER,
		CODE_GENERATION,
		SIZE
	};

	public ref class errorModule
	{
	private:
		int m_numErrors;
		cli::array<String^>^ m_errorsArray;

		bool addError(ERROR_PHASE errorPhase, int lineNumber, String^ errorDesc, String^ errorLine);

	public:

		errorModule();
		//~errorModule();

		void reset();
		bool addErrorLex(int lineNum, const char* desc, const char* line);
		bool addErrorSyn(int lineNum, const char* desc);
		bool addErrorSem(int lineNum, const char* desc);

		property cli::array<String^>^ Errors
		{
			cli::array<String^>^ get()
			{
				return m_errorsArray;
			}
		}
	};
}