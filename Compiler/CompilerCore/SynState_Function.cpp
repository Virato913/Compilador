#include "stdafx.h"
#include "SynState_Function.h"


compilerCore::synState_Function::synState_Function(compilerCore::lexAnalyzer* lexAnalyzer, compilerCore::errorModule^ errorModule, compilerCore::symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_Function::~synState_Function()
{

}

bool compilerCore::synState_Function::checkSyntax()
{
	const token* t = m_lexAnalyzer->getNextToken();
	if (t->getType() != TOKEN_TYPE::ID)
	{
		//Error - Expected a function ID but got something else
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getType() != TOKEN_TYPE::AGROUP_OP)
	{
		//Error - Expected ( or ) but got something else
	}
	if (m_lexAnalyzer->peekToken()->getType() != TOKEN_TYPE::AGROUP_OP)
	{
		synState_Param* p = new synState_Param(m_lexAnalyzer, m_errorModule, m_symTable);
		if (!p->checkSyntax())
			return false; //Max errors detected
	}
	t = m_lexAnalyzer->getNextToken();
	if (m_lexAnalyzer->peekToken()->getType() != TOKEN_TYPE::AGROUP_OP)
	{
		//Error - Expected ( or ) but got something else
	}
	t = m_lexAnalyzer->getNextToken();
	if (!t->getLex().compare(":"))
	{
		//Error - Expected : but got something else
	}
	t = m_lexAnalyzer->getNextToken();
	if (!t->getLex().compare("int") || !t->getLex().compare("float") || !t->getLex().compare("string") || !t->getLex().compare("bool"))
	{
		//Keep track of function type
	}
	else
	{
		//Error - No type declared or undefined type
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getType() != TOKEN_TYPE::AGROUP_OP)
	{
		//Error - Expected { or }
	}
	synState_FunctionBlock* fb = new synState_FunctionBlock(m_lexAnalyzer, m_errorModule, m_symTable);
	if (!fb->checkSyntax())
		return false; //Max errors detected
	return true;
}