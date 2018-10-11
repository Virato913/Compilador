#pragma once
#include "SynState.h"

using namespace System;

namespace compilerCore
{
	class synState_FunctionBlock : public synState
	{
	public:
		synState_FunctionBlock(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_FunctionBlock();
		bool checkSyntax();
	};
}