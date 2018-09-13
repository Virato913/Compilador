#include "Stdafx.h"
#include "ErrorModule.h"

using namespace System;

compilerCore::errorModule::errorModule()
{
	m_numErrors = 0;
	m_errorsArray = gcnew cli::array<String^>(MAX_ERRORS);

	for (int i = 0; i < MAX_ERRORS; ++i)
	{
		m_errorsArray[i] = gcnew String("");
	}
}

compilerCore::errorModule::~errorModule()
{

}

void compilerCore::errorModule::reset()
{
	m_numErrors = 0;
}

bool compilerCore::errorModule::addErrorLex(int lineNum, const char* desc, const char* line)
{
	String^ strDesc = gcnew String(desc);
	String^ strLine = gcnew String(line);
	return addError(compilerCore::ERROR_PHASE::LEXIC_ANALYZER, lineNum, strDesc, strLine);
}

bool compilerCore::errorModule::addError(ERROR_PHASE errorPhase, int lineNumber, String^ errorDesc, String^ errorLine)
{
	if (m_numErrors < MAX_ERRORS)
	{
		String^ errLine = gcnew String("");
		if (errorLine->Length > 20)
		{
			errLine = errorLine->Substring(0, 20);
		}
		else
		{
			errLine = errorLine;
		}

		m_errorsArray->SetValue(String::Format("<{0}>: \t{1} \t\t{2} \t\t{3}", errorPhase.ToString(), lineNumber, errorDesc, errLine), m_numErrors);
		++m_numErrors;

		return true;
	}

	return false;
}
