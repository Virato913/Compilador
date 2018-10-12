#include "stdafx.h"
#include "LocalNode.h"


compilerCore::localNode::localNode()
{
	m_value = nullptr;
	m_localNode = nullptr;
}

compilerCore::localNode::localNode(compilerCore::nodeData data)
{
	m_type = data.type;
	m_scope = data.scope;
	m_dimen = data.dimen;
	m_value = data.value;
	m_localNode = data.localNode;
	m_funcName = data.funcName;
}

compilerCore::localNode::~localNode()
{
	if (m_localNode)
		delete m_localNode;
}