#include "stdafx.h"
#include "ExpLogTreeNode.h"


compilerCore::expLogTreeNode::expLogTreeNode()
{
	m_left = nullptr;
	m_right = nullptr;
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
