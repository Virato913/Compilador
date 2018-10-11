#include "stdafx.h"
#include "SynState_Param.h"


compilerCore::synState_Param::synState_Param(compilerCore::lexAnalyzer* lexAnalyzer, compilerCore::errorModule^ errorModule, compilerCore::symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_Param::~synState_Param()
{

}

bool compilerCore::synState_Param::checkSyntax()
{
	return true;
}