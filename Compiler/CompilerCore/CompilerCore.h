// CompilerCore.h

#pragma once

using namespace System;

namespace compilerCore {

	public ref class Manager
	{
		// TODO: Add your methods for this class here.
	public:
		Manager();
		~Manager();
		cli::array<String^>^ compileProgram(String^ sourceCode);
	};
}
