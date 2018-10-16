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
		bool symbolExists(string name, map<string, globalNode>::iterator* it);
		string getSymbolName();
		string getSymbolScope();
		bool updateSymbolType();
		int getSymbolDimension();
		void reset();
	};
}