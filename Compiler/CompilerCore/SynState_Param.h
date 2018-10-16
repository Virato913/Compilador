#pragma once
#include "SynState.h"

using namespace System;

namespace compilerCore
{
	class synState_Param : public synState
	{
#define SYNTAX_ERROR_ID "Invalid ID | No ID found"
#define SYNTAX_ERROR_SEPARATOR "Expected :"
#define SYNTAX_ERROR_TYPE "Invalid type"
	public:
		synState_Param(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_Param();
		bool checkSyntax(string funcName);
	};
}