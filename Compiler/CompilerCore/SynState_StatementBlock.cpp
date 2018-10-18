#include "stdafx.h"
#include "SynState_StatementBlock.h"

//compilerCore::synState_StatementBlock::synState_StatementBlock(compilerCore::lexAnalyzer* lexAnalyzer, compilerCore::errorModule^ errorModule, compilerCore::symTable* symTable)
//{
//	m_lexAnalyzer = lexAnalyzer;
//	m_errorModule = errorModule;
//	m_symTable = symTable;
//}
//
//compilerCore::synState_StatementBlock::~synState_StatementBlock()
//{
//
//}
//
//bool compilerCore::synState_StatementBlock::checkSyntax()
//{
//	const token* t = m_lexAnalyzer->getNextToken();
//	while (t->getLex().compare("}"))
//	{
//		t = m_lexAnalyzer->getNextToken();
//	}
//	return true;
//}