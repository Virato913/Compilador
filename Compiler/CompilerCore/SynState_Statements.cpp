#include "stdafx.h"
#include "SynState_Statements.h"

compilerCore::synState_If::synState_If(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_If::~synState_If()
{

}

bool compilerCore::synState_If::checkSyntax()
{
	return true;
}

compilerCore::synState_While::synState_While(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_While::~synState_While()
{

}

bool compilerCore::synState_While::checkSyntax()
{
	return true;
}

compilerCore::synState_For::synState_For(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_For::~synState_For()
{

}

bool compilerCore::synState_For::checkSyntax()
{
	return true;
}

compilerCore::synState_Switch::synState_Switch(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_Switch::~synState_Switch()
{

}

bool compilerCore::synState_Switch::checkSyntax()
{
	return true;
}

compilerCore::synState_Assign::synState_Assign(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_Assign::~synState_Assign()
{

}

bool compilerCore::synState_Assign::checkSyntax()
{
	return true;
}

compilerCore::synState_Read::synState_Read(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_Read::~synState_Read()
{

}

bool compilerCore::synState_Read::checkSyntax()
{
	return true;
}

compilerCore::synState_Print::synState_Print(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_Print::~synState_Print()
{

}

bool compilerCore::synState_Print::checkSyntax()
{
	return true;
}

compilerCore::synState_Return::synState_Return(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_Return::~synState_Return()
{

}

bool compilerCore::synState_Return::checkSyntax()
{
	return true;
}

compilerCore::synState_FuncCall::synState_FuncCall(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_FuncCall::~synState_FuncCall()
{

}

bool compilerCore::synState_FuncCall::checkSyntax()
{
	return true;
}
