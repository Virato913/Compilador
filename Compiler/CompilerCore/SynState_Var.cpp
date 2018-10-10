#include "stdafx.h"
#include "SynState_Var.h"


compilerCore::synState_Var::synState_Var(compilerCore::lexAnalyzer* lexAnalizer, compilerCore::errorModule^ errorModule)
{
	m_lexAnalizer = lexAnalizer;
	m_errorModule = errorModule;
}

compilerCore::synState_Var::~synState_Var()
{
	
}

bool compilerCore::synState_Var::checkSyntax()
{

	return true;
}