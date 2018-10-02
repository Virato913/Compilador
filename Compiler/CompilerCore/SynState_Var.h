#pragma once
#include "SynState.h"

using namespace System;

namespace compilerCore
{
	class synState_Var : public synState
	{
	public:
		synState_Var(compilerCore::lexAnalyzer* lexAnalizer, compilerCore::errorModule^ errorModule);
		~synState_Var();
		bool checkSyntax();
	};
}