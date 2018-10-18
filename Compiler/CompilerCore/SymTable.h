#pragma once

#include <string>
#include <map>
#include "GlobalNode.h"

using std::string;
using std::map;

namespace compilerCore
{
	class symTable
	{
	private:
		map<string, globalNode> m_symbols;
	public:
		symTable();
		~symTable();
		bool addSymbol(string name, nodeData symbol);
		bool addSymbol(string name, SCOPE scope, int dimen, string funcName);
		bool symbolExists(string name, map<string, globalNode>::iterator* it);
		bool symbolExists(string name, SCOPE scope, string funcName);
		string getSymbolName();
		string getSymbolScope(string name);
		bool updateSymbolType();
		int getSymbolDimension(string name, SCOPE scope, string funcName);
		void reset();
	};
}