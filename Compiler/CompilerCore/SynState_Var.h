#pragma once
#include "SynState.h"

using namespace System;

namespace compilerCore
{
	class synState_Var : public synState
	{
#define SYNTAX_ERROR_ID "Invalid ID | No ID found"
#define SYNTAX_ERROR_DIMEN "Invalid lenght"
#define SYNTAX_ERROR_DIMEN_OP "Open dimen operator"
#define SYNTAX_ERROR_SEPARATOR "Expected :"
#define SYNTAX_ERROR_TYPE "Invalid type"
#define SYNTAX_ERROR_END "Expected ;"
	public:
		synState_Var(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_Var();
		bool checkSyntax(SCOPE scope, string funcName = "");
	};
}