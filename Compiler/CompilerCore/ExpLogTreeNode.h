#pragma once

#include "Token.h"

#include <stack>
#include <vector>

namespace compilerCore
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

		const token* m_value;

		void setRight(expLogTreeNode* node);
		void setLeft(expLogTreeNode* node);

	public:
		expLogTreeNode();
		expLogTreeNode(const token* value);
		~expLogTreeNode();
		expLogTreeNode* constructTree(std::vector<const token*> postfixExp);
	};
}
