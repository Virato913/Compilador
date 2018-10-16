#pragma once
#include "SynState.h"
#include "SynState_Var.h"
#include "SynState_Function.h"
#include "SynState_FunctionBlock.h"

using namespace System;

namespace compilerCore
{
	class synState_Program : public synState
	{
#define SYNTAX_ERROR_MAIN_DECLARATION "Main declaration error | Suspending analysis"
#define SYNTAX_ERROR_BRACKET "Expected {"
#define SYNTAX_ERROR_PROGRAM "Unexpected error in the program code"
	public:
		synState_Program(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_Program();
		bool checkSyntax();
	};
}