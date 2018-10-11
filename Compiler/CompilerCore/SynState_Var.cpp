#include "stdafx.h"
#include "SynState_Var.h"


compilerCore::synState_Var::synState_Var(compilerCore::lexAnalyzer* lexAnalyzer, compilerCore::errorModule^ errorModule, compilerCore::symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_Var::~synState_Var()
{
	
}

bool compilerCore::synState_Var::checkSyntax()
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
		if (!t->getLex().compare("["))
		{
			//Keep track of current Dim
		}
		else
		{
			//Current ID Dim is 0
		}
		t = m_lexAnalyzer->getNextToken();
	} while (!t->getLex().compare(","));
	if (t->getLex().compare(":"))
	{
		//Error - Expected : but got something else
	}
	t = m_lexAnalyzer->getNextToken();
	if (!t->getLex().compare("int") || !t->getLex().compare("float") || !t->getLex().compare("string") || !t->getLex().compare("bool"))
	{
		//Cycle for adding found tokens to the symTable
	}
	else
	{
		//Error - No type declared or undefined type
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare(";"))
	{
		//Error - Expected ; but got something else
	}
	return true;
}