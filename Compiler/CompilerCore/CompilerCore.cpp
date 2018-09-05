// This is the main DLL file.

#include "stdafx.h"

#include "CompilerCore.h"

compilerCore::Manager::Manager()
{

}

compilerCore::Manager::~Manager()
{

}

cli::array<String^>^ compilerCore::Manager::compileProgram(String^ sourceCode)
{
	cli::array<String^>^ compilationDetails = gcnew cli::array<String^>(1);
	compilationDetails[0] = gcnew String("Hola mundo.");
	return compilationDetails;
}