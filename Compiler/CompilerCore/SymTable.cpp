#include "stdafx.h"
#include "SymTable.h"


compilerCore::symTable::symTable()
{

}

compilerCore::symTable::~symTable()
{
	reset();
}

bool	compilerCore::symTable::addSymbol(string name, compilerCore::nodeData symbol) 
{
	globalNode newSymbol(symbol);
	m_symbols.insert(std::make_pair(name, newSymbol));
	return 0;
}

bool	compilerCore::symTable::symbolExists() 
{
	return 0;
}

string	compilerCore::symTable::getSymbolName() 
{
	return 0;
}

string	compilerCore::symTable::getSymbolScope() 
{
	return 0;
}

bool	compilerCore::symTable::updateSymbolType() 
{
	return 0;
}

int		compilerCore::symTable::getSymbolDimension() 
{
	return 0;
}

void compilerCore::symTable::reset()
{
	m_symbols.clear();
}