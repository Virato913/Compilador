#pragma once
#include "SynState.h"

namespace compilerCore
{
	class synState_Statements : public synState
	{
	public:
		synState_Statements(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_Statements();
	};
}
