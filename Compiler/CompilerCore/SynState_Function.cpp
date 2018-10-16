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
	string name;
	nodeData data;
	const token* t = m_lexAnalyzer->getNextToken();
	if (t->getType() != TOKEN_TYPE::ID)
	{
		//Error - Expected a function ID but got something else
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_ID))
			return false;
	}
	name = t->getLex();
	t = m_lexAnalyzer->getNextToken();
	if (t->getType() != TOKEN_TYPE::AGROUP_OP)
	{
		//Error - Expected ( or ) but got something else
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_PAREN))
			return false;
	}
	if (m_lexAnalyzer->peekToken()->getType() != TOKEN_TYPE::AGROUP_OP)
	{
		synState_Param* p = new synState_Param(m_lexAnalyzer, m_errorModule, m_symTable);
		if (!p->checkSyntax(name))
			return false; //Max errors detected
	}
	t = m_lexAnalyzer->getNextToken();
	if (m_lexAnalyzer->peekToken()->getType() != TOKEN_TYPE::AGROUP_OP)
	{
		//Error - Expected ( or ) but got something else
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_PAREN))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (!t->getLex().compare(":"))
	{
		//Error - Expected : but got something else
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_SEPARATOR))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (!t->getLex().compare("int") || !t->getLex().compare("float") || !t->getLex().compare("string") || !t->getLex().compare("bool"))
	{
		//Keep track of function type
		data.type = t->getLex();
	}
	else
	{
		//Error - No type declared or undefined type
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_TYPE))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getType() != TOKEN_TYPE::AGROUP_OP)
	{
		//Error - Expected { or }
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_BRACKET))
			return false;
	}
	data.dimen = 0;
	data.funcName = "<GLOBAL SCOPE>";
	data.localNode = nullptr;
	data.scope = SCOPE::FUNC;
	m_symTable->addSymbol(name, data);
	synState_FunctionBlock* fb = new synState_FunctionBlock(m_lexAnalyzer, m_errorModule, m_symTable);
	if (!fb->checkSyntax(name))
		return false; //Max errors detected
	return true;
}