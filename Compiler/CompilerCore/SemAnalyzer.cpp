#include "stdafx.h"
#include "SemAnalyzer.h"


compilerCore::semAnalyzer::semAnalyzer(compilerCore::errorModule^ errorModule)
{
	m_errorModule = errorModule;
}

compilerCore::semAnalyzer::~semAnalyzer()
{

}

void compilerCore::semAnalyzer::addExpLog(int lineNum, string funcName, std::vector<const token*> expLogVec, string symbolToUpdate)
{
	expLog* newExpLog = new expLog(lineNum, funcName, expLogVec, symbolToUpdate);
	newExpLog->buildTree();
	m_expLogVec.push_back(newExpLog);
}

void compilerCore::semAnalyzer::checkExpressions()
{
	for (int i = 0; i < m_expLogVec.size(); i++)
	{
		if (!m_expLogVec[i]->validateTree())
			if (!m_errorModule->addErrorSem(m_expLogVec[i]->getLineNum(), "Invalid expression"))
				break;
	}
}