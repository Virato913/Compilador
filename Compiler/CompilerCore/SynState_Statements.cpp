#include "stdafx.h"
#include "SynState_Statements.h"


compilerCore::synState_Statements::synState_Statements(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_Statements::~synState_Statements()
{

}
