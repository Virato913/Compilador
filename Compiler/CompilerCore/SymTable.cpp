#include "stdafx.h"
#include "SymTable.h"


compilerCore::symTable::symTable()
{

}

compilerCore::symTable::~symTable()
{
	reset();
}

bool compilerCore::symTable::addSymbol(string name, compilerCore::nodeData symbol) 
{
	map<string, globalNode>::iterator* it = new map<string, globalNode>::iterator();
	if (!symbolExists(name, it))
	{
		globalNode newSymbol(name, symbol);
		m_symbols.insert(std::make_pair(name, newSymbol));
	}
	else
	{
		localNode* node = new localNode(symbol);
		(*it)->second.addLocalNode(node);
	}
	return true;
}

bool compilerCore::symTable::symbolExists(string name, map<string, compilerCore::globalNode>::iterator* it)
{
	*it = m_symbols.find(name);
	return (*it != m_symbols.end());
}

string compilerCore::symTable::getSymbolName() 
{
	return 0;
}

string compilerCore::symTable::getSymbolScope(string name)
{
	return 0;
}

bool compilerCore::symTable::updateSymbolType() 
{
	return 0;
}

int	compilerCore::symTable::getSymbolDimension(string name, SCOPE scope, string funcName)
{
	return 0;
}

void compilerCore::symTable::reset()
{
	m_symbols.clear();
}

void compilerCore::symTable::getSymbols(map<string, globalNode>* symbols)
{
	*symbols = m_symbols;
}