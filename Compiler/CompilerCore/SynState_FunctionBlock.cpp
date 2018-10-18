#include "stdafx.h"
#include "SynState_FunctionBlock.h"


compilerCore::synState_FunctionBlock::synState_FunctionBlock(compilerCore::lexAnalyzer* lexAnalyzer, compilerCore::errorModule^ errorModule, compilerCore::symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}


compilerCore::synState_FunctionBlock::~synState_FunctionBlock()
{

}

bool compilerCore::synState_FunctionBlock::checkSyntax(string funcName)
{
	const token* t = m_lexAnalyzer->getNextToken();
	bool returnFound = false;
	while (t->getLex().compare("var") == 0)
	{
		synState_Var* v = new synState_Var(m_lexAnalyzer, m_errorModule, m_symTable);
		if (!v->checkSyntax(SCOPE::LOCAL_VAR, funcName))
			return false; // Max errors reached
		t = m_lexAnalyzer->peekToken();
	}
	while (t->getLex().compare("}"))
	{
		t = m_lexAnalyzer->getNextToken();
		if (!t->getLex().compare("if"))
		{
			
		}
		if (!t->getLex().compare("while"))
		{

		}
		if (!t->getLex().compare("for"))
		{

		}
		if (!t->getLex().compare("switch"))
		{

		}
		if (t->getType() == TOKEN_TYPE::ID)
		{

		}
		if (!t->getLex().compare("read"))
		{

		}
		if (!t->getLex().compare("print"))
		{

		}
		if (!t->getLex().compare("return"))
		{
			returnFound = true;
		}
	}
	if (!returnFound)
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_RETURN))
			return false;
	return true;
}