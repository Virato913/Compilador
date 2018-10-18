#include "stdafx.h"
#include "SynAnalyzer.h"


compilerCore::synAnalyzer::synAnalyzer(lexAnalyzer* lexAnalyzer, errorModule^ errorModule)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = new symTable();
}


compilerCore::synAnalyzer::~synAnalyzer()
{
	delete m_symTable;
}

bool compilerCore::synAnalyzer::checkSyntax()
{
	synState_Program* p = new synState_Program(m_lexAnalyzer, m_errorModule, m_symTable);
	return p->checkSyntax();
}

void compilerCore::synAnalyzer::getSymbols(map<string, compilerCore::globalNode>* symbols)
{
	m_symTable->getSymbols(symbols);
}