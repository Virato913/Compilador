#include "stdafx.h"
#include "LexAnalyzer.h"

compilerCore::lexAnalyzer::lexAnalyzer(errorModule^ errorsModule)
{
	m_errorModule = errorsModule;
	m_Keywords.insert(std::make_pair("var", ""));
	m_Keywords.insert(std::make_pair("int", ""));
	m_Keywords.insert(std::make_pair("float", ""));
	m_Keywords.insert(std::make_pair("string", ""));
	m_Keywords.insert(std::make_pair("bool", ""));
	m_Keywords.insert(std::make_pair("void", ""));
	m_Keywords.insert(std::make_pair("function", ""));
	m_Keywords.insert(std::make_pair("main", ""));
	m_Keywords.insert(std::make_pair("if", ""));
	m_Keywords.insert(std::make_pair("else", ""));
	m_Keywords.insert(std::make_pair("while", ""));
	m_Keywords.insert(std::make_pair("for", ""));
	m_Keywords.insert(std::make_pair("inc", ""));
	m_Keywords.insert(std::make_pair("dec", ""));
	m_Keywords.insert(std::make_pair("switch", ""));
	m_Keywords.insert(std::make_pair("case", ""));
	m_Keywords.insert(std::make_pair("default", ""));
	m_Keywords.insert(std::make_pair("print", ""));
	m_Keywords.insert(std::make_pair("read", ""));
	m_Keywords.insert(std::make_pair("return", ""));
	m_Keywords.insert(std::make_pair("true", ""));
	m_Keywords.insert(std::make_pair("false", ""));
}

compilerCore::lexAnalyzer::~lexAnalyzer()
{
	m_Keywords.clear();
	m_Tokens.clear();
}

bool compilerCore::lexAnalyzer::parseSourceCode(const char* sourceCode)
{
	return 0;
}

void compilerCore::lexAnalyzer::reset()
{
	m_errorModule->reset();
	m_Tokens.clear();
	//m_Tokens.resize(0);
}

void compilerCore::lexAnalyzer::getTokens(vector<token*>* tokensVec) const
{
	tokensVec[0] = m_Tokens;
}