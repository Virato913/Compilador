#pragma once
#include "SynState.h"

namespace compilerCore
{
#define SYNTAX_ERROR_PAREN "Expected ("
#define SYNTAX_ERROR_BRACKET "Expected {"
#define SYNTAX_ERROR_SEMICOLON "Expected ;"
#define SYNTAX_ERROR_INC_DEC "Expected increment or decrement"
#define SYNTAX_ERROR_INT "Integer expected"
#define SYNTAX_ERROR_POS_INT "Positive integer expected"
#define SYNTAX_ERROR_CPAREN "Expected )"
#define SYNTAX_ERROR_ASSIGN "Expected ="
#define SYNTAX_ERROR_ID "Expected ID"
	///////////////////////////////////
	///           IF                ///
	///////////////////////////////////
	class synState_If : public synState
	{
	public:
		synState_If(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_If();
		bool checkSyntax();
	};
	///////////////////////////////////
	///           WHILE             ///
	///////////////////////////////////
	class synState_While : public synState
	{
	public:
		synState_While(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_While();
		bool checkSyntax();
	};
	///////////////////////////////////
	///           FOR               ///
	///////////////////////////////////
	class synState_For : public synState
	{
	public:
		synState_For(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_For();
		bool checkSyntax();
	};
	///////////////////////////////////
	///           SWITCH            ///
	///////////////////////////////////
	class synState_Switch : public synState
	{
	public:
		synState_Switch(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_Switch();
		bool checkSyntax();
	};
	///////////////////////////////////
	///           ASSIGN            ///
	///////////////////////////////////
	class synState_Assign : public synState
	{
	public:
		synState_Assign(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_Assign();
		bool checkSyntax();
	};
	///////////////////////////////////
	///           READ              ///
	///////////////////////////////////
	class synState_Read : public synState
	{
	public:
		synState_Read(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_Read();
		bool checkSyntax();
	};
	///////////////////////////////////
	///           PRINT             ///
	///////////////////////////////////
	class synState_Print : public synState
	{
	public:
		synState_Print(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_Print();
		bool checkSyntax();
	};
	///////////////////////////////////
	///           RETURN            ///
	///////////////////////////////////
	class synState_Return : public synState
	{
	public:
		synState_Return(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_Return();
		bool checkSyntax();
	};
	///////////////////////////////////
	///           FUNC_CALL         ///
	///////////////////////////////////
	class synState_FuncCall : public synState
	{
	public:
		synState_FuncCall(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_FuncCall();
		bool checkSyntax();
	};
	///////////////////////////////////
	///           BLOCK             ///
	///////////////////////////////////
	class synState_StatementBlock : public synState
	{
	public:
		synState_StatementBlock(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable);
		~synState_StatementBlock();
		bool checkSyntax();
	};
}
