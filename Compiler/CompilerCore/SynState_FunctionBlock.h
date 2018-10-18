#pragma once
#include "SynState.h"
#include "SynState_Statements.h"
#include "SynState_Var.h"

using namespace System;

namespace compilerCore
{
	class synState_FunctionBlock : public synState
	{
#define SYNTAX_ERROR_RETURN "Expected return"
	public:
		synState_FunctionBlock(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_FunctionBlock();
		bool checkSyntax(string funcName);
	};
}