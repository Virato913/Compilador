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
	bool returnFound = false;
	const token* t = m_lexAnalyzer->getNextToken();
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
			synState_If* s = new synState_If(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!s->checkSyntax())
				return false;
		}
		if (!t->getLex().compare("while"))
		{
			synState_While* s = new synState_While(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!s->checkSyntax())
				return false;
		}
		if (!t->getLex().compare("for"))
		{
			synState_For* s = new synState_For(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!s->checkSyntax())
				return false;
		}
		if (!t->getLex().compare("switch"))
		{
			synState_Switch* s = new synState_Switch(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!s->checkSyntax())
				return false;
		}
		if (t->getType() == TOKEN_TYPE::ID)
		{
			t = m_lexAnalyzer->getNextToken();
			if (!t->getLex().compare("("))
			{
				synState_FuncCall* s = new synState_FuncCall(m_lexAnalyzer, m_errorModule, m_symTable);
				if (!s->checkSyntax())
					return false;
			}
			else
			{
				if(!t->getLex().compare("["))
				{
					//Evaluate logical expression for the dimension
					while (t->getLex().compare("]"))
					{
						t = m_lexAnalyzer->getNextToken();
					}
					t = m_lexAnalyzer->getNextToken();
					if (!t->getLex().compare("="))
					{
						//Evaluate logical expresion for assignment
						while (t->getLex().compare(";"))
						{
							t = m_lexAnalyzer->getNextToken();
						}
					}
					else
					{
						//Assignment error
					}
				}
				else if (!t->getLex().compare("="))
				{
					synState_Assign* s = new synState_Assign(m_lexAnalyzer, m_errorModule, m_symTable);
					if (!s->checkSyntax())
						return false;
				}
				else
				{
					//Assignment error
				}
			}
		}
		if (!t->getLex().compare("read"))
		{
			synState_Read* s = new synState_Read(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!s->checkSyntax())
				return false;
		}
		if (!t->getLex().compare("print"))
		{
			synState_Print* s = new synState_Print(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!s->checkSyntax())
				return false;
		}
		if (!t->getLex().compare("return"))
		{

			synState_Return* s = new synState_Return(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!s->checkSyntax())
				return false;
			returnFound = true;
			break;
		}
	}
	if (!returnFound)
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_RETURN))
			return false;
	return true;
}