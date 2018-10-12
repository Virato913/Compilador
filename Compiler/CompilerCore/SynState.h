#pragma once

#include "ErrorModule.h"
#include "LexAnalyzer.h"
#include "SymTable.h"
#include "Token.h"

using namespace System;

namespace compilerCore
{
	//#define ERROR_ 
	//#define ERROR_ 
	//#define ERROR_ 
	//#define ERROR_ 
	//#define ERROR_ 
	//#define ERROR_ 
	//#define ERROR_ 
	//#define ERROR_ 

	class synState
	{
	protected:
		lexAnalyzer* m_lexAnalyzer;
		gcroot<errorModule^> m_errorModule;
		symTable* m_symTable;

	public:
		synState();
		~synState();
	};
}