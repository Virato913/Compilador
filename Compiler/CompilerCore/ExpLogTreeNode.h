#pragma once

namespace
{
	enum class NODE_RESULT
	{
		E_ARIT,
		E_LOG,
		E_REL
	};

	class expLogTreeNode
	{
	private:
		NODE_RESULT m_nodeType;
		NODE_RESULT m_result;
		expLogTreeNode* m_left;
		expLogTreeNode* m_right;
		NODE_RESULT m_expectedResultLeft;
		NODE_RESULT m_expectedResultRight;

	public:
		expLogTreeNode();
		~expLogTreeNode();

	};
}
