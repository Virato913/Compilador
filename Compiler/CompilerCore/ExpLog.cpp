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
	postfixToTree();
}

bool compilerCore::expLog::validateTree()
{
	return true;
}

void compilerCore::expLog::infixToPostfix()
{
	stack<const token*> opStack;
	for (int i = 0; i < m_exp.size(); i++)
	{
		if (m_exp[i]->getType() != TOKEN_TYPE::ARIT_OP &&
			m_exp[i]->getType() != TOKEN_TYPE::AGROUP_OP &&
			m_exp[i]->getType() != TOKEN_TYPE::REL_OP &&
			m_exp[i]->getType() != TOKEN_TYPE::LOGICAL_OP &&
			m_exp[i]->getType() != TOKEN_TYPE::UNARY_LOGICAL_OP)
		{
			m_postFixExp.push_back(m_exp[i]);
		}
		else
		{
			if (m_exp[i]->getType() == TOKEN_TYPE::ARIT_OP)
			{
				if (opStack.empty() || !opStack.top()->getLex().compare("("))
				{
					opStack.push(m_exp[i]);
				}
				else
				{
					if (!m_exp[i]->getLex().compare("+") || !m_exp[i]->getLex().compare("-"))
					{
						while (!opStack.empty() &&
							(!opStack.top()->getLex().compare("*") ||
								!opStack.top()->getLex().compare("/") ||
								!opStack.top()->getLex().compare("%") ||
								!opStack.top()->getLex().compare("^")))
						{
							m_postFixExp.push_back(opStack.top());
							opStack.pop();
						}
						if (opStack.empty() || !opStack.top()->getLex().compare("("))
							opStack.push(m_exp[i]);
						else
						{
							if (!opStack.top()->getLex().compare("+") || !opStack.top()->getLex().compare("-"))
							{
								m_postFixExp.push_back(opStack.top());
								opStack.pop();
								opStack.push(m_exp[i]);
							}
						}
					}
					else if (!m_exp[i]->getLex().compare("*") || !m_exp[i]->getLex().compare("/") || !m_exp[i]->getLex().compare("%"))
					{
						while (!opStack.empty() && !opStack.top()->getLex().compare("^"))
						{
							m_postFixExp.push_back(opStack.top());
							opStack.pop();
						}
						if (opStack.empty() || !opStack.top()->getLex().compare("("))
							opStack.push(m_exp[i]);
						else
						{
							if (!opStack.top()->getLex().compare("+") || !opStack.top()->getLex().compare("-"))
							{
								opStack.push(m_exp[i]);
							}
							else if (!m_exp[i]->getLex().compare("*") || !m_exp[i]->getLex().compare("/") || !m_exp[i]->getLex().compare("%"))
							{
								m_postFixExp.push_back(opStack.top());
								opStack.pop();
								opStack.push(m_exp[i]);
							}
						}
					}
					else if (!m_exp[i]->getLex().compare("^"))
					{
						if (opStack.empty() || !opStack.top()->getLex().compare("("))
							opStack.push(m_exp[i]);
						else if (!opStack.top()->getLex().compare("+") ||
							!opStack.top()->getLex().compare("-") ||
							!opStack.top()->getLex().compare("*") ||
							!opStack.top()->getLex().compare("/") ||
							!opStack.top()->getLex().compare("%"))
						{
							opStack.push(m_exp[i]);
						}
						else if (!opStack.top()->getLex().compare("^"))
						{
							m_postFixExp.push_back(opStack.top());
							opStack.pop();
							opStack.push(m_exp[i]);
						}
					}
				}
			}
			else if (m_exp[i]->getType() == TOKEN_TYPE::AGROUP_OP)
			{
				if (!m_exp[i]->getLex().compare("("))
				{
					opStack.push(m_exp[i]);
				}
				if (!m_exp[i]->getLex().compare(")"))
				{
					while (opStack.top()->getLex().compare("("))
					{
						m_postFixExp.push_back(opStack.top());
						opStack.pop();
					}
					opStack.pop();
				}
			}
			else if (m_exp[i]->getType() == TOKEN_TYPE::LOGICAL_OP || m_exp[i]->getType() == TOKEN_TYPE::REL_OP || m_exp[i]->getType() == TOKEN_TYPE::UNARY_LOGICAL_OP)
			{
				m_postFixExp.push_back(opStack.top());
			}
		}
	}
	while (!opStack.empty())
	{
		m_postFixExp.push_back(opStack.top());
		opStack.pop();
	}
}

void compilerCore::expLog::postfixToTree()
{
	expLogTreeNode* tree = new expLogTreeNode();
	m_tree = tree->constructTree(m_postFixExp);
}
