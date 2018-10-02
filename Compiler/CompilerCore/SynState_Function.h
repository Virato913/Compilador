#pragma once
#include "SynState.h"

using namespace System;

namespace compilerCore
{
	class synState_Function : public synState
	{
	public:
		synState_Function(lexAnalyzer* lexAnalizer, errorModule^ errorModule);
		~synState_Function();
		bool checkSyntax();
	};
}