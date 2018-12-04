#pragma once

#include "Token.h"
#include "ExpLogTreeNode.h"

#include <stack>
#include <string>
#include <vector>

using std::stack;
using std::string;
using std::vector;

namespace compilerCore
{
	class expLog
	{
	private:
		int m_lineNum;
		string m_funcName;
		string m_symbolToUpdate;
		vector<const token*> m_exp;
		vector<const token*> m_postFixExp;
		expLogTreeNode* m_tree;
		NODE_RESULT m_expectedResult;
		void infixToPostfix();
		void postfixToTree();

	public:
		expLog(int lineNum, string funcName, vector<const token*> expVec, string symbolToUpdate = "");
		~expLog();
		void buildTree();
		bool validateTree();
	};
}
