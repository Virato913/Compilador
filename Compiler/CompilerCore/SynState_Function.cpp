#include "stdafx.h"
#include "SynState_Function.h"


compilerCore::synState_Function::synState_Function(compilerCore::lexAnalyzer* lexAnalizer, compilerCore::errorModule^ errorModule)
{
	m_lexAnalizer = lexAnalizer;
	m_errorModule = errorModule;
}

compilerCore::synState_Function::~synState_Function()
{

}

bool compilerCore::synState_Function::checkSyntax()
{
	return true;
}