#include "stdafx.h"
#include "LexAnalyzer.h"

compilerCore::lexAnalyzer::lexAnalyzer(errorModule^ errorsModule)
{
	m_errorModule = errorsModule;
}

compilerCore::lexAnalyzer::~lexAnalyzer()
{

}

bool compilerCore::lexAnalyzer::parseSourceCode(const char* sourceCode)
{

}

void compilerCore::lexAnalyzer::reset()
{
	m_errorModule->reset();
	m_Tokens.clear();
	m_Tokens.resize(0);
}

void compilerCore::lexAnalyzer::getTokens(vector<token*>* tokensVec) const
{
	tokensVec[0] = m_Tokens;
}