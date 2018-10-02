#pragma once
#include "SynState.h"

using namespace System;

namespace compilerCore
{
	class synState_Param : public synState
	{
	public:
		synState_Param(lexAnalyzer* lexAnalizer, errorModule^ errorModule);
		~synState_Param();
		bool checkSyntax();
	};
}