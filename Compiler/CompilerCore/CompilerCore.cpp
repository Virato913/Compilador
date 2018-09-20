// This is the main DLL file.

#include "stdafx.h"

#include "CompilerCore.h"

compilerCore::Manager::Manager()
{
	m_errorModule = gcnew errorModule();
	m_lexAnalyzer = new lexAnalyzer(m_errorModule);
}

compilerCore::Manager::~Manager()
{
	// Free memory of LEX analyzer
	if (m_lexAnalyzer != nullptr)
	{
		delete m_lexAnalyzer;
		m_lexAnalyzer = nullptr;
	}

	// Memory of ERRORS MODULE is automatically collected (allocated with gcnew)
}

cli::array<String^>^ compilerCore::Manager::compileProgram(String^ sourceCode)
{
	//cli::array<String^>^ compilationDetails = gcnew cli::array<String^>(1);
	//compilationDetails[0] = gcnew String("Hola mundo.");
	//return compilationDetails;
	cli::array<String ^> ^ compilationDetails;

	// Clear state if all pointers are valid
	if (m_errorModule && m_lexAnalyzer != nullptr)
	{
		m_errorModule->reset();
		m_lexAnalyzer->reset();
	}
	else
	{
		// invalid pointers, return error...
	}

	lexAnalysis(sourceCode);

	compilationDetails = getCompilationDetails();

	return compilationDetails;
}

void compilerCore::Manager::lexAnalysis(String^ sourceCode)
{

}

cli::array<String^>^ compilerCore::Manager::getCompilationDetails()
{
	vector<token*>* tokens = new vector<token*>();
	m_lexAnalyzer->getTokens(tokens);
	return m_errorModule->Errors;
}