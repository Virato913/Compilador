#include "stdafx.h"
#include "GlobalNode.h"


compilerCore::globalNode::globalNode()
{
	m_value = nullptr;
	m_localNode = nullptr;
}

compilerCore::globalNode::globalNode(string name, compilerCore::nodeData data)
{
	m_name = name;
	m_type = data.type;
	m_scope = data.scope;
	m_dimen = data.dimen;
	m_value = data.value;
	m_localNode = data.localNode;
}

compilerCore::globalNode::~globalNode()
{
	if (m_localNode)
		delete m_localNode;
}

void compilerCore::globalNode::addLocalNode(compilerCore::localNode* node)
{
	if (m_localNode)
	{
		m_localNode->addNode(node);
	}
	else
	{
		m_localNode = node;
	}
}