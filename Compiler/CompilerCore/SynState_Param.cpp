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
				if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_ID))
					return false;
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
			if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_SEPARATOR))
				return false;
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
			if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_TYPE))
				return false;
		}
		//if (!m_lexAnalyzer->peekToken()->getLex().compare(";"))
		//	t = m_lexAnalyzer->getNextToken();
		//else
		//{
		//	if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_MULTIPLE_TYPES))
		//		return false;
		//}
	} while (m_lexAnalyzer->peekToken()->getLex().compare(")"));
	return true;
}