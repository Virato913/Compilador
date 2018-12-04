#include "stdafx.h"
#include "ExpLogTreeNode.h"


compilerCore::expLogTreeNode::expLogTreeNode()
{
	m_left = nullptr;
	m_right = nullptr;
}

compilerCore::expLogTreeNode::expLogTreeNode(const token* value)
{
	m_left = nullptr;
	m_right = nullptr;
	m_value = value;
	switch (m_value->getType())
	{
	case TOKEN_TYPE::ARIT_OP:
		m_nodeType = NODE_RESULT::E_ARIT;
		m_expectedResultLeft = NODE_RESULT::E_ARIT;
		m_expectedResultRight = NODE_RESULT::E_ARIT;
		break;
	case TOKEN_TYPE::LOGICAL_OP:
		m_nodeType = NODE_RESULT::E_LOG;
		m_expectedResultLeft = NODE_RESULT::E_LOG;
		m_expectedResultRight = NODE_RESULT::E_LOG;
		break;
	case TOKEN_TYPE::REL_OP:
		m_nodeType = NODE_RESULT::E_LOG;
		m_expectedResultLeft = NODE_RESULT::E_LOG;
		m_expectedResultRight = NODE_RESULT::E_LOG;
		break;
	case TOKEN_TYPE::UNARY_LOGICAL_OP:
		m_nodeType = NODE_RESULT::E_LOG;
		m_expectedResultLeft = NODE_RESULT::E_LOG;
		m_expectedResultRight = NODE_RESULT::E_LOG;
		break;
	default:
		break;
	}
}

compilerCore::expLogTreeNode::~expLogTreeNode()
{
	if (m_left)
	{
		delete m_left;
		m_left = nullptr;
	}
	if (m_right)
	{
		delete m_right;
		m_right = nullptr;
	}
}

compilerCore::expLogTreeNode* compilerCore::expLogTreeNode::constructTree(std::vector<const token*> postfixExp)
{
	std::stack<expLogTreeNode*> stackTree;
	expLogTreeNode* root;
	expLogTreeNode* left;
	expLogTreeNode* right;
	for (int i = 0; i < postfixExp.size(); i++)
	{
		root = new expLogTreeNode(postfixExp[i]);
		if (postfixExp[i]->getType() == TOKEN_TYPE::ARIT_OP ||
			postfixExp[i]->getType() == TOKEN_TYPE::LOGICAL_OP ||
			postfixExp[i]->getType() == TOKEN_TYPE::REL_OP ||
			postfixExp[i]->getType() == TOKEN_TYPE::UNARY_LOGICAL_OP)
		{
			right = stackTree.top();
			stackTree.pop();
			left = stackTree.top();
			stackTree.pop();
			root->setRight(right);
			root->setLeft(left);
		}
		stackTree.push(root);
	}
	root = stackTree.top();
	stackTree.pop();
	return root;
}

void compilerCore::expLogTreeNode::setRight(expLogTreeNode* node)
{
	m_right = node;
}

void compilerCore::expLogTreeNode::setLeft(expLogTreeNode* node)
{
	m_left = node;
}
