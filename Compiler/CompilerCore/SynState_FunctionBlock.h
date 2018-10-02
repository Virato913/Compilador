#pragma once
#include "SynState.h"

using namespace System;

namespace compilerCore
{
	class synState_FunctionBlock : public synState
	{
	public:
		synState_FunctionBlock(lexAnalyzer* lexAnalizer, errorModule^ errorModule);
		~synState_FunctionBlock();
		bool checkSyntax();
	};
}