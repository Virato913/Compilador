#include "stdafx.h"
#include "SynState_Program.h"


compilerCore::synState_Program::synState_Program(compilerCore::lexAnalyzer* lexAnalyzer, compilerCore::errorModule^ errorModule, compilerCore::symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_Program::~synState_Program()
{

}

bool compilerCore::synState_Program::checkSyntax()
{
	const token* t = m_lexAnalyzer->getNextToken();
	while (t->getLex().compare("var") == 0)
	{
		synState_Var* v = new synState_Var(m_lexAnalyzer, m_errorModule, m_symTable);
		if (!v->checkSyntax(SCOPE::GLOBAL_VAR))
			return false; // Max errors reached
		t = m_lexAnalyzer->getNextToken();
	}
	while (t->getLex().compare("function") == 0)
	{
		synState_Function* f = new synState_Function(m_lexAnalyzer, m_errorModule, m_symTable);
		if (!f->checkSyntax())
			return false; // Max errors reached
		t = m_lexAnalyzer->getNextToken();
	}
	if (t->getLex().compare("main") == 0)
	{
		t = m_lexAnalyzer->getNextToken();
		if (t->getType() == m_lexAnalyzer->peekToken()->getType())
		{
			t = m_lexAnalyzer->getNextToken();
			t = m_lexAnalyzer->getNextToken();
			if (!t->getLex().compare("{"))
			{
				synState_FunctionBlock* fb = new synState_FunctionBlock(m_lexAnalyzer, m_errorModule, m_symTable);
				fb->checkSyntax("main");
			}
			else
			{
				//Error - { expected
			}
		}
		else
		{
			t = m_lexAnalyzer->getNextToken();
			// Error de declaración de main (?)
		}
	}
	else
	{
		// Error en el programa (?)
	}
	return true;
}