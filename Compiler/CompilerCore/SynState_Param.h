#pragma once
#include "SynState.h"

using namespace System;

namespace compilerCore
{
	class synState_Param : public synState
	{
	public:
		synState_Param(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_Param();
		bool checkSyntax();
	};
}