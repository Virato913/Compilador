#include "stdafx.h"
#include "SynState_Program.h"


compilerCore::synState_Program::synState_Program(compilerCore::lexAnalyzer* lexAnalizer, compilerCore::errorModule^ errorModule)
{
	m_lexAnalizer = lexAnalizer;
	m_errorModule = errorModule;
}

compilerCore::synState_Program::~synState_Program()
{

}

bool compilerCore::synState_Program::checkSyntax()
{
	const token* t = m_lexAnalizer->getNextToken();
	while (t->getLex().compare("var") == 0)
	{
		synState_Var* v = new synState_Var(m_lexAnalizer, m_errorModule);
		if (!v->checkSyntax())
			return false; // Max errors reached
		t = m_lexAnalizer->getNextToken();
	}
	while (t->getLex().compare("function") == 0)
	{
		synState_Function* f = new synState_Function(m_lexAnalizer, m_errorModule);
		if (!f->checkSyntax())
			return false; // Max errors reached
		t = m_lexAnalizer->getNextToken();
	}
	if (t->getLex().compare("main") == 0)
	{
		t = m_lexAnalizer->getNextToken();
		if (t->getType() == m_lexAnalizer->peekToken()->getType())
		{
			t = m_lexAnalizer->getNextToken();
			t = m_lexAnalizer->getNextToken();
			synState_FunctionBlock* fb = new synState_FunctionBlock(m_lexAnalizer, m_errorModule);
			fb->checkSyntax();
		}
		else
		{
			t = m_lexAnalizer->getNextToken();
			// Error de declaración de main (?)
		}
	}
	else
	{
		// Error en el programa (?)
	}
	return true;
}