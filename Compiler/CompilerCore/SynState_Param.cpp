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

bool compilerCore::synState_Param::checkSyntax(string funcName)
{
	const token* t = nullptr;
	do
	{
	vector<string> tempID;
	nodeData data;
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
		} while (!t->getLex().compare(","));
		if (t->getLex().compare(":"))
		{
			//Error - Expected :
		}
		t = m_lexAnalyzer->getNextToken();
		if (!t->getLex().compare("int") || !t->getLex().compare("float") || !t->getLex().compare("string") || !t->getLex().compare("bool"))
		{
			data.dimen = 0;
			data.funcName = funcName;
			data.localNode = nullptr;
			data.scope = SCOPE::PARAM;
			data.type = t->getLex();
			//Cycle for adding found tokens to the symTable
			for (int i = 0; i < tempID.size(); i++)
			{
				m_symTable->addSymbol(tempID[i], data);
			}
		}
		else
		{
			//Error - No type declared or undefined type
		}
	} while (m_lexAnalyzer->peekToken()->getLex().compare(")"));
	return true;
}