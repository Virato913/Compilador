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
	{
		delete m_tree;
		m_tree = nullptr;
	}
}

void compilerCore::expLog::buildTree()
{
	//First, m_exp needs to be converted to postfix notation which will be stored in m_postFixExp
	infixToPostfix();
	//After that, the tree is actually built from the postfix expression
}

bool compilerCore::expLog::validateTree()
{
	return true;
}

void compilerCore::expLog::infixToPostfix()
{
	stack<const token*> opStack;
	for (auto it = m_exp.begin(); it != m_exp.end(); it++)
	{
		if ((*it)->getType() != TOKEN_TYPE::ARIT_OP && (*it)->getType() != TOKEN_TYPE::AGROUP_OP && (*it)->getType() != TOKEN_TYPE::REL_OP)
		{
			m_postFixExp.push_back((*it));
		}
		else
		{
			if ((*it)->getType() == TOKEN_TYPE::ARIT_OP)
			{
				if (opStack.empty() || !opStack.top()->getLex().compare("("))
				{
					opStack.push((*it));
				}
				else
				{
					if (!(*it)->getLex().compare("+") || !(*it)->getLex().compare("-"))
					{
						while (!opStack.empty() && (!opStack.top()->getLex().compare("*") || !opStack.top()->getLex().compare("/") || !opStack.top()->getLex().compare("%") || !opStack.top()->getLex().compare("^")))
						{
							m_postFixExp.push_back(opStack.top());
							opStack.pop();
						}
						if (opStack.empty() || !opStack.top()->getLex().compare("("))
							opStack.push((*it));
						else
						{
							if (!opStack.top()->getLex().compare("+") || !opStack.top()->getLex().compare("-"))
							{
								m_postFixExp.push_back(opStack.top());
								opStack.pop();
								opStack.push((*it));
							}
						}
					}
					else if (!(*it)->getLex().compare("*") || !(*it)->getLex().compare("/") || !(*it)->getLex().compare("%"))
					{
						while (!opStack.empty() && !(*it)->getLex().compare("^"))
						{
							m_postFixExp.push_back(opStack.top());
							opStack.pop();
						}
						if (opStack.empty() || !opStack.top()->getLex().compare("("))
							opStack.push((*it));
						else
						{
							if (!opStack.top()->getLex().compare("+") || !opStack.top()->getLex().compare("-"))
							{
								opStack.push((*it));
							}
							else if (!(*it)->getLex().compare("*") || !(*it)->getLex().compare("/") || !(*it)->getLex().compare("%"))
							{
								m_postFixExp.push_back(opStack.top());
								opStack.pop();
								opStack.push((*it));
							}
						}
					}
					else if (!(*it)->getLex().compare("^"))
					{
						if (!opStack.top()->getLex().compare("+") || !opStack.top()->getLex().compare("-"))
						{
							opStack.push((*it));
						}
						else if (!(*it)->getLex().compare("*") || !(*it)->getLex().compare("/") || !(*it)->getLex().compare("%"))
						{
							opStack.push((*it));
						}
						else if (!(*it)->getLex().compare("^"))
						{
							m_postFixExp.push_back(opStack.top());
							opStack.pop();
							opStack.push((*it));
						}
					}
				}
			}
			else if ((*it)->getType() == TOKEN_TYPE::AGROUP_OP)
			{
				if (!(*it)->getLex().compare("("))
				{
					opStack.push((*it));
				}
				if (!(*it)->getLex().compare(")"))
				{
					while (opStack.top()->getLex().compare("("))
					{
						m_postFixExp.push_back(opStack.top());
						opStack.pop();
					}
					opStack.pop();
				}
			}
		}
	}
	while (!opStack.empty())
	{
		m_postFixExp.push_back(opStack.top());
		opStack.pop();
	}
}