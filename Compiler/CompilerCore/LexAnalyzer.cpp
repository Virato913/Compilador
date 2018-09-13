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

}

void compilerCore::lexAnalyzer::getTokens(vector<token*>* tokensVec) const
{

}