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
	while (t->getLex().compare("}"))
	{
		t = m_lexAnalyzer->getNextToken();
		while (t->getLex().compare("var") == 0)
		{
			synState_Var* v = new synState_Var(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!v->checkSyntax(SCOPE::LOCAL_VAR, funcName))
				return false; // Max errors reached
			t = m_lexAnalyzer->getNextToken();
		}
	}
	return true;
}