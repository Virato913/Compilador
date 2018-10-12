// This is the main DLL file.

#include "stdafx.h"

#include "CompilerCore.h"

compilerCore::Manager::Manager()
{
	m_errorModule = gcnew errorModule();
	m_lexAnalyzer = new lexAnalyzer(m_errorModule);
	m_synAnalyzer = new synAnalyzer(m_lexAnalyzer, m_errorModule);
}

compilerCore::Manager::~Manager()
{
	// Free memory of LEX analyzer
	if (m_lexAnalyzer != nullptr)
	{
		delete m_lexAnalyzer;
		m_lexAnalyzer = nullptr;
	}

	// Free memory of SYN analyzer
	if (m_synAnalyzer != nullptr)
	{
		delete m_synAnalyzer;
		m_synAnalyzer = nullptr;
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

	synAnalysis();

	compilationDetails = getCompilationDetails();

	return compilationDetails;
}

void compilerCore::Manager::lexAnalysis(String^ sourceCode)
{
	if (m_lexAnalyzer != nullptr)
	{
		if (!m_lexAnalyzer->parseSourceCode((const char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sourceCode).ToPointer()))
		{
			m_errorModule->reset();
			m_lexAnalyzer->reset();
			m_errorModule->addErrorLex(0, "Max errors reached", "");
		}
	}
}

void compilerCore::Manager::synAnalysis()
{
	if (m_synAnalyzer != nullptr)
	{
		m_synAnalyzer->checkSyntax();
	}
}

cli::array<String^>^ compilerCore::Manager::getCompilationDetails()
{
	vector<token*>* tokens = new vector<token*>();
	m_lexAnalyzer->getTokens(tokens);
	cli::array<String^>^ tokenArray = gcnew cli::array<String^>(tokens->size());
	int i = 0;
	for (vector<token*>::iterator it = tokens->begin(); it != tokens->end(); ++it)
	{
		String^ lex = gcnew String((*it)->getLex().c_str());
		String^ type = gcnew String((*it)->getTypeStr().c_str());
		tokenArray->SetValue(String::Format("{0} {1} {2}", lex, type, (*it)->getLineNumber()), i);
		i++;
	}
	int k = 0;
	for (int i = 0; i < m_errorModule->Errors->Length; i++)
	{
		if (m_errorModule->Errors[i] != "")
		{
			k++;
		}
	}
	cli::array<String^>^ compDetails = gcnew cli::array<String^>(k + tokens->size());
	for (i = 0; i < m_errorModule->Errors->Length; i++)
	{
		if (m_errorModule->Errors[i] != "")
		{
			compDetails[i] = m_errorModule->Errors[i];
		}
	}
	for (int j = 0; j < tokens->size(); j++)
	{
		compDetails[j + k] = tokenArray[j];
	}
	return compDetails;
}

cli::array<cli::array<String^>^, 2>^ compilerCore::Manager::compile(String^ sourceCode)
{
	//cli::array<String^>^ compilationDetails = gcnew cli::array<String^>(1);
	//compilationDetails[0] = gcnew String("Hola mundo.");
	//return compilationDetails;
	cli::array<cli::array<String^>^, 2>^ compilationDetails;

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

	compilationDetails = getCompDetails();

	return compilationDetails;
}

cli::array<cli::array<String^>^, 2>^ compilerCore::Manager::getCompDetails()
{
	cli::array<cli::array<String^>^, 2>^ compDetails = gcnew cli::array<cli::array<String^>^, 2>(1, 1);
	return compDetails;
}