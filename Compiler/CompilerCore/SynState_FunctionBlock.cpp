#include "stdafx.h"
#include "SynState_FunctionBlock.h"


compilerCore::synState_FunctionBlock::synState_FunctionBlock(lexAnalyzer* lexAnalizer, errorModule^ errorModule)
{
	m_lexAnalizer = lexAnalizer;
	m_errorModule = errorModule;
}


compilerCore::synState_FunctionBlock::~synState_FunctionBlock()
{

}

bool compilerCore::synState_FunctionBlock::checkSyntax()
{
	return true;
}