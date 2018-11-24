#include "stdafx.h"
#include "SynState_ExpLog.h"


//compilerCore::synState_ExpLog::synState_ExpLog(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable)
//{
//	m_lexAnalyzer = lexAnalyzer;
//	m_errorModule = errorModule;
//	m_symTable = symTable;
//}
//
//compilerCore::synState_ExpLog::~synState_ExpLog()
//{
//
//}
//
//bool compilerCore::synState_ExpLog::checkSyntax()
//{
//	const token* t = m_lexAnalyzer->getNextToken();
//	if (t->getType == TOKEN_TYPE::UNARY_LOGICAL_OP)
//	{
//		t = m_lexAnalyzer->getNextToken();
//	}
//	if (!t->getLex().compare("("))
//	{
//		synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
//		if (!e->checkSyntax())
//			return false;
//		t = m_lexAnalyzer->getNextToken();
//		if (t->getLex().compare(")"))
//		{
//			//Error - Expected ")"
//			if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CPAREN))
//				return false;
//		}
//	}
//	else if (t->getType() == TOKEN_TYPE::INT || t->getType() == TOKEN_TYPE::FLOAT || t->getType() == TOKEN_TYPE::STRING || !t->getLex().compare("false") || !t->getLex().compare("true"))
//	{
//
//	}
//	else if (t->getType() == TOKEN_TYPE::ID)
//	{
//		if (!m_lexAnalyzer->peekToken()->getLex().compare("["))
//		{
//			t = m_lexAnalyzer->getNextToken();
//			synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
//			if (!e->checkSyntax())
//				return false;
//			t = m_lexAnalyzer->getNextToken();
//			if (t->getLex().compare("]"))
//			{
//				//Error - Expected "]"
//				if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CBRACKET))
//					return false;
//			}
//		}
//		else if (!m_lexAnalyzer->peekToken()->getLex().compare("("))
//		{
//			t = m_lexAnalyzer->getNextToken();
//			synState_FuncCall* f = new synState_FuncCall(m_lexAnalyzer, m_errorModule, m_symTable);
//			if (!f->checkSyntax())
//				return false;
//		}
//	}
//	if (m_lexAnalyzer->peekToken()->getType() == TOKEN_TYPE::ARIT_OP || m_lexAnalyzer->peekToken()->getType() == TOKEN_TYPE::LOGICAL_OP || m_lexAnalyzer->peekToken()->getType() == TOKEN_TYPE::REL_OP)
//	{
//		synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
//		if (!e->checkSyntax())
//			return false;
//	}
//	return true;
//}