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

bool compilerCore::synState_FunctionBlock::checkSyntax()
{
	return true;
}