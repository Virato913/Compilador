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

bool compilerCore::synState_Var::checkSyntax(compilerCore::SCOPE scope, string funcName)
{
	vector<string> tempID;
	vector<int> tempDim;
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
			tempID.push_back(t->getLex());
		}
		t = m_lexAnalyzer->getNextToken();
		if (!t->getLex().compare("["))
		{
			t = m_lexAnalyzer->getNextToken();
			if (t->getType() == TOKEN_TYPE::INT)
			{
				//Keep track of current Dim
				tempDim.push_back(atoi(t->getLex().c_str()));
			}
			else
			{
				//Error - Invalid dimen
			}
			t = m_lexAnalyzer->getNextToken();
			if (!t->getLex().compare("]"))
			{
				//Error - Open dimension operator
			}
			t = m_lexAnalyzer->getNextToken();
		}
		else
		{
			//Current ID Dim is 0
			tempDim.push_back(0);
		}
	} while (!t->getLex().compare(","));
	if (t->getLex().compare(":"))
	{
		//Error - Expected : but got something else
	}
	t = m_lexAnalyzer->getNextToken();
	if (!t->getLex().compare("int") || !t->getLex().compare("float") || !t->getLex().compare("string") || !t->getLex().compare("bool"))
	{
		nodeData data;
		if (scope == SCOPE::GLOBAL_VAR)
			data.funcName = "<GLOBAL SCOPE>";
		else
			data.funcName = funcName;
		data.localNode = nullptr;
		data.scope = scope;
		data.type = t->getLex();
		//Cycle for adding found tokens to the symTable
		for (int i = 0; i < tempID.size(); i++)
		{
			data.dimen = tempDim[i];
			m_symTable->addSymbol(tempID[i], data);
		}
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