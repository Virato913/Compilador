#pragma once

#include <string>

using std::string;

namespace compilerCore
{
	enum class SCOPE
	{
		UNDEFINED,
		FUNC,
		GLOBAL_VAR,
		LOCAL_VAR,
		PARAM
	};

	struct nodeData;

	class localNode
	{
	private:
		string m_type;
		SCOPE m_scope;
		int m_dimen;
		void* m_value;
		localNode* m_localNode;
		string m_funcName;

	public:
		localNode();
		localNode(nodeData data);
		~localNode();
	};

	struct nodeData
	{
		string type;
		SCOPE scope;
		int dimen;
		void* value;
		localNode* localNode;
		string funcName;
	};
}