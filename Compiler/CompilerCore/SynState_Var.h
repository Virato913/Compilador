#pragma once
#include "SynState.h"

using namespace System;

namespace compilerCore
{
	class synState_Var : public synState
	{
	public:
		synState_Var(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_Var();
		bool checkSyntax();
	};
}