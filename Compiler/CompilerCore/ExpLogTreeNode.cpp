#include "stdafx.h"
#include "ExpLogTreeNode.h"


compilerCore::expLogTreeNode::expLogTreeNode()
{
	m_left = nullptr;
	m_right = nullptr;
}

compilerCore::expLogTreeNode::expLogTreeNode(const token* value, string type)
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
	case TOKEN_TYPE::INT:
		m_nodeType = NODE_RESULT::E_ARIT;
		m_expectedResultLeft = NODE_RESULT::E_ARIT;
		m_expectedResultRight = NODE_RESULT::E_ARIT;
		break;
	case TOKEN_TYPE::FLOAT:
		m_nodeType = NODE_RESULT::E_ARIT;
		m_expectedResultLeft = NODE_RESULT::E_ARIT;
		m_expectedResultRight = NODE_RESULT::E_ARIT;
		break;
	case TOKEN_TYPE::STRING:
		m_nodeType = NODE_RESULT::E_LOG;
		m_expectedResultLeft = NODE_RESULT::E_LOG;
		m_expectedResultRight = NODE_RESULT::E_LOG;
		break;
	case TOKEN_TYPE::ID:
		if (!type.compare("int"))
		{
			m_nodeType = NODE_RESULT::E_ARIT;
			m_expectedResultLeft = NODE_RESULT::E_ARIT;
			m_expectedResultRight = NODE_RESULT::E_ARIT;
		}
		else if (!type.compare("float"))
		{
			m_nodeType = NODE_RESULT::E_ARIT;
			m_expectedResultLeft = NODE_RESULT::E_ARIT;
			m_expectedResultRight = NODE_RESULT::E_ARIT;
		}
		else if (!type.compare("bool"))
		{
			m_nodeType = NODE_RESULT::E_LOG;
			m_expectedResultLeft = NODE_RESULT::E_LOG;
			m_expectedResultRight = NODE_RESULT::E_LOG;
		}
		else if (!type.compare("string"))
		{
			m_nodeType = NODE_RESULT::E_LOG;
			m_expectedResultLeft = NODE_RESULT::E_LOG;
			m_expectedResultRight = NODE_RESULT::E_LOG;
		}
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
			if (postfixExp[i]->getType() == TOKEN_TYPE::UNARY_LOGICAL_OP)
			{
				right = stackTree.top();
				stackTree.pop();
				root->setRight(right);
			}
			else
			{
				right = stackTree.top();
				stackTree.pop();
				left = stackTree.top();
				stackTree.pop();
				root->setRight(right);
				root->setLeft(left);
			}
		}
		stackTree.push(root);
	}
	root = stackTree.top();
	stackTree.pop();
	return root;
}

void* compilerCore::expLogTreeNode::evaluateNode()
{
	if (!m_left && !m_right)
	{
		//If it isn't a variable return this node's value
		if (m_value->getType() != TOKEN_TYPE::ID)
		{
			if (m_value->getType() == TOKEN_TYPE::INT)
			{
				return (void*)std::stoi(m_value->getLex());
			}
			if (m_value->getType() == TOKEN_TYPE::FLOAT)
			{
				//Can't convert float to void*
			}
			if (m_value->getType() == TOKEN_TYPE::STRING)
			{
				return (void*)m_value->getLex().c_str();
			}
			if (m_value->getType() == TOKEN_TYPE::KEYWORD)
			{
				if (!m_value->getLex().compare("true"))
					return (void*)true;
				if (!m_value->getLex().compare("false"))
					return (void*)false;
			}
		}
	}
	void* l_val = nullptr;
	void* r_val = nullptr;
	if (m_left)
		l_val = m_left->evaluateNode();
	if (m_right)
		r_val = m_right->evaluateNode();
	if (m_value->getType() == TOKEN_TYPE::ARIT_OP)
	{
		if (!m_value->getLex().compare("+"))
			return (void*)(*(int*)l_val + *(int*)r_val);
		if (!m_value->getLex().compare("-"))
			return (void*)(*(int*)l_val - *(int*)r_val);
		if (!m_value->getLex().compare("*"))
			return (void*)(*(int*)l_val * *(int*)r_val);
		if (!m_value->getLex().compare("/"))
			return (void*)(*(int*)l_val / *(int*)r_val);
		if (!m_value->getLex().compare("%"))
			return (void*)(*(int*)l_val % *(int*)r_val);
		if (!m_value->getLex().compare("^"))
			return (void*)(*(int*)l_val ^ *(int*)r_val);
	}
	if (m_value->getType() == TOKEN_TYPE::LOGICAL_OP)
	{
		if (!m_value->getLex().compare("&&"))
			return (void*)(*(bool*)l_val && *(bool*)r_val);
		if (!m_value->getLex().compare("||"))
			return (void*)(*(bool*)l_val || *(bool*)r_val);
	}
	if (m_value->getType() == TOKEN_TYPE::REL_OP)
	{
		if (!m_value->getLex().compare("<"))
			return (void*)(*(int*)l_val < *(int*)r_val);
		if (!m_value->getLex().compare(">"))
			return (void*)(*(int*)l_val > *(int*)r_val);
		if (!m_value->getLex().compare("<="))
			return (void*)(*(int*)l_val <= *(int*)r_val);
		if (!m_value->getLex().compare(">="))
			return (void*)(*(int*)l_val >= *(int*)r_val);
		if (!m_value->getLex().compare("!="))
			return (void*)(*(int*)l_val != *(int*)r_val);
		if (!m_value->getLex().compare("=="))
			return (void*)(*(int*)l_val == *(int*)r_val);
	}
	if (m_value->getType() == TOKEN_TYPE::UNARY_LOGICAL_OP)
	{
		return (void*)(!*(bool*)r_val);
	}
}

void compilerCore::expLogTreeNode::setRight(expLogTreeNode* node)
{
	m_right = node;
}

void compilerCore::expLogTreeNode::setLeft(expLogTreeNode* node)
{
	m_left = node;
}
