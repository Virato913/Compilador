#pragma once

#include "Token.h"
#include "LexAnalyzer.h"
#include "ErrorModule.h"

using namespace System;

namespace compilerCore
{
	class synState
	{
	protected:
		lexAnalyzer* m_lexAnalizer;
		gcroot<errorModule^> m_errorModule;

	public:
		synState();
		~synState();
	};
}