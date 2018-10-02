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
	public:
		synState_Program(lexAnalyzer* lexAnalizer, errorModule^ errorModule);
		~synState_Program();
		bool checkSyntax();
	};
}