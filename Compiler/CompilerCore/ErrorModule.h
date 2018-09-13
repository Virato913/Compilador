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

		bool addError(ERROR_PHASE, int, String^, String^);

	public:

		errorModule();
		~errorModule();

		void reset();
		bool addErrorLex(int, const char*, const char*);

		property cli::array<String^>^ Errors
		{
			cli::array<String^>^ get()
			{
				return m_errorsArray;
			}
		}
	};
}