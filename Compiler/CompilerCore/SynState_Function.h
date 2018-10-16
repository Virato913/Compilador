#pragma once

#include "SynState.h"
#include "SynState_FunctionBlock.h"
#include "SynState_Param.h"

using namespace System;

namespace compilerCore
{
	class synState_Function : public synState
	{
#define SYNTAX_ERROR_PAREN "Expected ( or )"
#define SYNTAX_ERROR_BRACKET "Expected {"
	public:
		synState_Function(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_Function();
		bool checkSyntax();
	};
}