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
	const token* t = nullptr;
	do
	{
		t = m_lexAnalyzer->getNextToken();
		if (t->getType() != TOKEN_TYPE::ID)
		{
			//Error - No ID found
		}
		else
		{
			//Keep track of current ID
		}
		t = m_lexAnalyzer->getNextToken();
	} while (!t->getLex().compare(","));
	return true;
}