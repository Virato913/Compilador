#include "stdafx.h"
#include "ExpLog.h"

compilerCore::expLog::expLog(int lineNum, string funcName, vector<const token*> expVec, string symbolToUpdate)
{
	m_lineNum = lineNum;
	m_funcName = funcName;
	m_symbolToUpdate = symbolToUpdate;
	m_exp = expVec;
}

compilerCore::expLog::~expLog()
{
	if (m_tree)
		delete m_tree;
}

void compilerCore::expLog::buildTree()
{

}

bool compilerCore::expLog::validateTree()
{

}