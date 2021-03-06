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
	const token* t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare("("))
	{
		//Error - Expected (
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_PAREN))
			return false;
	}
	//Check logical expression
	synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
	if (!e->checkSyntax())
		return false;
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare(")"))
	{
		//Error - Expected ")"
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CPAREN))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare("{"))
	{
		//Error - Expected {
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_BRACKET))
			return false;
	}
	else
	{
		synState_StatementBlock* sb = new synState_StatementBlock(m_lexAnalyzer, m_errorModule, m_symTable);
		if (!sb->checkSyntax())
			return false;
	}
	if (!m_lexAnalyzer->peekToken()->getLex().compare("else"))
	{
		t = m_lexAnalyzer->getNextToken();
		t = m_lexAnalyzer->getNextToken();
		if (t->getLex().compare("{"))
		{
			//Error - Expected {
			if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_BRACKET))
				return false;
		}
		synState_StatementBlock* sb = new synState_StatementBlock(m_lexAnalyzer, m_errorModule, m_symTable);
		if (!sb->checkSyntax())
			return false;
	}
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
	const token* t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare("("))
	{
		//Error - Expected (
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_PAREN))
			return false;
	}
	//Check logical expression
	synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
	if (!e->checkSyntax())
		return false;
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare(")"))
	{
		//Error - Expected ")"
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CPAREN))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare("{"))
	{
		//Error - Expected {
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_BRACKET))
			return false;
	}
	else
	{
		synState_StatementBlock* sb = new synState_StatementBlock(m_lexAnalyzer, m_errorModule, m_symTable);
		if (!sb->checkSyntax())
			return false;
	}
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
	const token* t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare("("))
	{
		//Error - Expected (
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_PAREN))
			return false;
	}
	else
	{
		synState_Assign* a = new synState_Assign(m_lexAnalyzer, m_errorModule, m_symTable);
		if (!a->checkSyntax())
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare(";"))
	{
		//Error - Expected ;
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_SEMICOLON))
			return false;
	}
	//Check logical expression
	synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
	if (!e->checkSyntax())
		return false;
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare(";"))
	{
		//Error - Expected ;
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_SEMICOLON))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare("inc") && t->getLex().compare("dec"))
	{
		//Error - Increment or decrement expected
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_INC_DEC))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getType() != TOKEN_TYPE::INT)
	{
		//Error - Invalid number
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_INT))
			return false;
	}
	else
	{
		if (atoi(t->getLex().c_str()) < 0)
		{
			//Error - Positive integer expected
			if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_POS_INT))
				return false;
		}
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare(")"))
	{
		//Error - Expected )
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CPAREN))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare("{"))
	{
		//Error - Expected {
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_PAREN))
			return false;
	}
	else
	{
		synState_StatementBlock* sb = new synState_StatementBlock(m_lexAnalyzer, m_errorModule, m_symTable);
		if (!sb->checkSyntax())
			return false;
	}
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
	const token* t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare("("))
	{
		//Error - Expected (
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_PAREN))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getType() != TOKEN_TYPE::ID)
	{
		//Error - Expected ID
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_ID))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (!t->getLex().compare("["))
	{
		//Check logical expression
		synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
		if (!e->checkSyntax())
			return false;
		t = m_lexAnalyzer->getNextToken();
		if (t->getLex().compare("]"))
		{
			//Error - Expected "]"
			if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CBRACKET))
				return false;
		}
		t = m_lexAnalyzer->getNextToken();
	}
	if (t->getLex().compare(")"))
	{
		//Error - Expected )
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CPAREN))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	//Evaluate switch block
	if (t->getLex().compare("{"))
	{
		//Error - Expected {
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_BRACKET))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	while (t->getLex().compare("}"))
	{
		//Evaluate each case block
		while (!t->getLex().compare("case"))
		{
			t = m_lexAnalyzer->getNextToken();
			if (t->getLex().compare(":"))
			{
				//Error - Expected :
				if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_SEPARATOR))
					return false;
			}
			else
			{
				t = m_lexAnalyzer->getNextToken();
				if (t->getType() != TOKEN_TYPE::INT || t->getType() != TOKEN_TYPE::FLOAT || t->getType() != TOKEN_TYPE::STRING || t->getLex().compare("true") || t->getLex().compare("false"))
				{
					//Error - Expected constant
					if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CONSTANT))
						return false;
				}
				else
				{
					//Statement block
					while (t->getLex().compare("case"))
					{
						t = m_lexAnalyzer->getNextToken();
						if (!t->getLex().compare("if"))
						{
							synState_If* s = new synState_If(m_lexAnalyzer, m_errorModule, m_symTable);
							if (!s->checkSyntax())
								return false;
						}
						if (!t->getLex().compare("while"))
						{
							synState_While* s = new synState_While(m_lexAnalyzer, m_errorModule, m_symTable);
							if (!s->checkSyntax())
								return false;
						}
						if (!t->getLex().compare("for"))
						{
							synState_For* s = new synState_For(m_lexAnalyzer, m_errorModule, m_symTable);
							if (!s->checkSyntax())
								return false;
						}
						if (!t->getLex().compare("switch"))
						{
							synState_Switch* s = new synState_Switch(m_lexAnalyzer, m_errorModule, m_symTable);
							if (!s->checkSyntax())
								return false;
						}
						if (t->getType() == TOKEN_TYPE::ID)
						{
							t = m_lexAnalyzer->getNextToken();
							if (!t->getLex().compare("("))
							{
								synState_FuncCall* s = new synState_FuncCall(m_lexAnalyzer, m_errorModule, m_symTable);
								if (!s->checkSyntax())
									return false;
							}
							else
							{
								if (!t->getLex().compare("["))
								{
									//Evaluate logical expression for the dimension
									while (t->getLex().compare("]"))
									{
										t = m_lexAnalyzer->getNextToken();
									}
									t = m_lexAnalyzer->getNextToken();
									if (!t->getLex().compare("="))
									{
										//Evaluate logical expresion for assignment
										while (t->getLex().compare(";"))
										{
											t = m_lexAnalyzer->getNextToken();
										}
									}
									else
									{
										//Assignment error
										if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_ASSIGN))
											return false;
									}
								}
								else if (!t->getLex().compare("="))
								{
									//Evaluate logical expresion for assignment
									while (t->getLex().compare(";"))
									{
										t = m_lexAnalyzer->getNextToken();
									}
								}
								else
								{
									//Assignment error
									if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_ASSIGN))
										return false;
								}
							}
						}
						if (!t->getLex().compare("read"))
						{
							synState_Read* s = new synState_Read(m_lexAnalyzer, m_errorModule, m_symTable);
							if (!s->checkSyntax())
								return false;
						}
						if (!t->getLex().compare("print"))
						{
							synState_Print* s = new synState_Print(m_lexAnalyzer, m_errorModule, m_symTable);
							if (!s->checkSyntax())
								return false;
						}
						if (!t->getLex().compare("return"))
						{

							synState_Return* s = new synState_Return(m_lexAnalyzer, m_errorModule, m_symTable);
							if (!s->checkSyntax())
								return false;
							break;
						}
					}
				}
			}
		}
		if (!t->getLex().compare("default"))
		{
			t = m_lexAnalyzer->getNextToken();
			if (t->getLex().compare(":"))
			{
				//Error - Expected :
				if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_SEPARATOR))
					return false;
			}
			else
			{
				//Statement block
				while (t->getLex().compare("}"))
				{
					t = m_lexAnalyzer->getNextToken();
					if (!t->getLex().compare("if"))
					{
						synState_If* s = new synState_If(m_lexAnalyzer, m_errorModule, m_symTable);
						if (!s->checkSyntax())
							return false;
					}
					if (!t->getLex().compare("while"))
					{
						synState_While* s = new synState_While(m_lexAnalyzer, m_errorModule, m_symTable);
						if (!s->checkSyntax())
							return false;
					}
					if (!t->getLex().compare("for"))
					{
						synState_For* s = new synState_For(m_lexAnalyzer, m_errorModule, m_symTable);
						if (!s->checkSyntax())
							return false;
					}
					if (!t->getLex().compare("switch"))
					{
						synState_Switch* s = new synState_Switch(m_lexAnalyzer, m_errorModule, m_symTable);
						if (!s->checkSyntax())
							return false;
					}
					if (t->getType() == TOKEN_TYPE::ID)
					{
						t = m_lexAnalyzer->getNextToken();
						if (!t->getLex().compare("("))
						{
							synState_FuncCall* s = new synState_FuncCall(m_lexAnalyzer, m_errorModule, m_symTable);
							if (!s->checkSyntax())
								return false;
						}
						else
						{
							if (!t->getLex().compare("["))
							{
								//Evaluate logical expression for the dimension
								while (t->getLex().compare("]"))
								{
									t = m_lexAnalyzer->getNextToken();
								}
								t = m_lexAnalyzer->getNextToken();
								if (!t->getLex().compare("="))
								{
									//Evaluate logical expresion for assignment
									while (t->getLex().compare(";"))
									{
										t = m_lexAnalyzer->getNextToken();
									}
								}
								else
								{
									//Assignment error
									if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_ASSIGN))
										return false;
								}
							}
							else if (!t->getLex().compare("="))
							{
								//Evaluate logical expresion for assignment
								while (t->getLex().compare(";"))
								{
									t = m_lexAnalyzer->getNextToken();
								}
							}
							else
							{
								//Assignment error
								if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_ASSIGN))
									return false;
							}
						}
					}
					if (!t->getLex().compare("read"))
					{
						synState_Read* s = new synState_Read(m_lexAnalyzer, m_errorModule, m_symTable);
						if (!s->checkSyntax())
							return false;
					}
					if (!t->getLex().compare("print"))
					{
						synState_Print* s = new synState_Print(m_lexAnalyzer, m_errorModule, m_symTable);
						if (!s->checkSyntax())
							return false;
					}
					if (!t->getLex().compare("return"))
					{

						synState_Return* s = new synState_Return(m_lexAnalyzer, m_errorModule, m_symTable);
						if (!s->checkSyntax())
							return false;
						break;
					}
				}
			}
		}
	}
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
	const token* t = m_lexAnalyzer->getNextToken();
	if (t->getType() != TOKEN_TYPE::ID)
	{
		//Error - Expected ID
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_ID))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (!t->getLex().compare("["))
	{
		//Check logical expression
		synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
		if (!e->checkSyntax())
			return false;
		t = m_lexAnalyzer->getNextToken();
		if (t->getLex().compare("]"))
		{
			//Error - Expected "]"
			if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CBRACKET))
				return false;
		}
		t = m_lexAnalyzer->getNextToken();
	}
	if (t->getLex().compare("="))
	{
		//Error - Expected assign token
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_ASSIGN))
			return false;
	}
	//Evaluate logical expression for assignment
	synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
	if (!e->checkSyntax())
		return false;
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare(";"))
	{
		//Error - Expected ";"
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_SEMICOLON))
			return false;
	}
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
	const token* t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare("("))
	{
		//Error - Expected (
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_PAREN))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getType() != TOKEN_TYPE::ID)
	{
		//Error - Expected ID
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_ID))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (!t->getLex().compare("["))
	{
		//Check logical expression
		synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
		if (!e->checkSyntax())
			return false;
		t = m_lexAnalyzer->getNextToken();
		if (t->getLex().compare("]"))
		{
			//Error - Expected "]"
			if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CBRACKET))
				return false;
		}
		t = m_lexAnalyzer->getNextToken();
	}
	if (t->getLex().compare(")"))
	{
		//Error - Expected )
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CPAREN))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare(";"))
	{
		//Error - Expected ;
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_SEMICOLON))
			return false;
	}
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
	const token* t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare("("))
	{
		//Error - Expected (
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_PAREN))
			return false;
	}
	//Check logical expression
	synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
	if (!e->checkSyntax())
		return false;
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare(")"))
	{
		//Error - Expected ")"
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CPAREN))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare(";"))
	{
		//Error - Expected ;
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_SEMICOLON))
			return false;
	}
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
	synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
	if (!e->checkSyntax())
		return false;
	const token* t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare(")"))
	{
		//Error - Expected ")"
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CPAREN))
			return false;
	}
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
	//Check logical expression
	synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
	if (!e->checkSyntax())
		return false;
	const token* t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare(")"))
	{
		//Error - Expected ")"
		if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CPAREN))
			return false;
	}
	t = m_lexAnalyzer->getNextToken();
	if (t->getLex().compare(";"))
	{
		//Error - Expected ";"
	}
	return true;
}

compilerCore::synState_StatementBlock::synState_StatementBlock(compilerCore::lexAnalyzer* lexAnalyzer, compilerCore::errorModule^ errorModule, compilerCore::symTable* symTable)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
}

compilerCore::synState_StatementBlock::~synState_StatementBlock()
{

}

bool compilerCore::synState_StatementBlock::checkSyntax()
{
	const token* t = m_lexAnalyzer->getNextToken();
	while (t->getLex().compare("}"))
	{
		t = m_lexAnalyzer->getNextToken();
		if (!t->getLex().compare("if"))
		{
			synState_If* s = new synState_If(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!s->checkSyntax())
				return false;
		}
		if (!t->getLex().compare("while"))
		{
			synState_While* s = new synState_While(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!s->checkSyntax())
				return false;
		}
		if (!t->getLex().compare("for"))
		{
			synState_For* s = new synState_For(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!s->checkSyntax())
				return false;
		}
		if (!t->getLex().compare("switch"))
		{
			synState_Switch* s = new synState_Switch(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!s->checkSyntax())
				return false;
		}
		if (t->getType() == TOKEN_TYPE::ID)
		{
			t = m_lexAnalyzer->getNextToken();
			if (!t->getLex().compare("("))
			{
				synState_FuncCall* s = new synState_FuncCall(m_lexAnalyzer, m_errorModule, m_symTable);
				if (!s->checkSyntax())
					return false;
			}
			else
			{
				if (!t->getLex().compare("["))
				{
					//Check logical expression
					synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
					if (!e->checkSyntax())
						return false;
					t = m_lexAnalyzer->getNextToken();
					if (t->getLex().compare("]"))
					{
						//Error - Expected "]"
						if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CBRACKET))
							return false;
					}
					t = m_lexAnalyzer->getNextToken();
					if (!t->getLex().compare("="))
					{
						//Check logical expression
						synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
						if (!e->checkSyntax())
							return false;
						t = m_lexAnalyzer->getNextToken();
						if (t->getLex().compare(";"))
						{
							//Error - Expected ";"
							if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_SEMICOLON))
								return false;
						}
						t = m_lexAnalyzer->getNextToken();
					}
					else
					{
						//Assignment error
						if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_ASSIGN))
							return false;
					}
				}
				else if (!t->getLex().compare("="))
				{
					//Check logical expression
					synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable);
					if (!e->checkSyntax())
						return false;
					t = m_lexAnalyzer->getNextToken();
					if (t->getLex().compare(";"))
					{
						//Error - Expected ";"
						if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_SEMICOLON))
							return false;
					}
					t = m_lexAnalyzer->getNextToken();
				}
				else
				{
					//Assignment error
					if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_ASSIGN))
						return false;
				}
			}
		}
		if (!t->getLex().compare("read"))
		{
			synState_Read* s = new synState_Read(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!s->checkSyntax())
				return false;
		}
		if (!t->getLex().compare("print"))
		{
			synState_Print* s = new synState_Print(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!s->checkSyntax())
				return false;
		}
		if (!t->getLex().compare("return"))
		{

			synState_Return* s = new synState_Return(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!s->checkSyntax())
				return false;
			break;
		}
	}
	return true;
}

compilerCore::synState_ExpLog::synState_ExpLog(lexAnalyzer* lexAnalyzer, errorModule^ errorModule, symTable* symTable, vector<const token*>* expVec)
{
	m_lexAnalyzer = lexAnalyzer;
	m_errorModule = errorModule;
	m_symTable = symTable;
	m_expVec = expVec;
}

compilerCore::synState_ExpLog::~synState_ExpLog()
{

}

bool compilerCore::synState_ExpLog::checkSyntax(string funcName, string symbolToUpdate)
{
	int errorCount = m_errorModule->Errors->Length;
	const token* t = m_lexAnalyzer->getNextToken();
	if (!m_expVec)
		m_expVec = new vector<const token*>();
	if (t->getType() == TOKEN_TYPE::UNARY_LOGICAL_OP)
	{
		m_expVec->push_back(t);
		t = m_lexAnalyzer->getNextToken();
	}
	if (!t->getLex().compare("("))
	{
		m_expVec->push_back(t);
		synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable, m_expVec);
		if (!e->checkSyntax(funcName, symbolToUpdate))
			return false;
		t = m_lexAnalyzer->getNextToken();
		if (t->getLex().compare(")"))
		{
			//Error - Expected ")"
			if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CPAREN))
				return false;
		}
		m_expVec->push_back(t);
	}
	else if (t->getType() == TOKEN_TYPE::INT || t->getType() == TOKEN_TYPE::FLOAT || t->getType() == TOKEN_TYPE::STRING || !t->getLex().compare("false") || !t->getLex().compare("true"))
	{
		m_expVec->push_back(t);
	}
	else if (t->getType() == TOKEN_TYPE::ID)
	{
		if (!m_lexAnalyzer->peekToken()->getLex().compare("["))
		{
			m_expVec->push_back(t);
			t = m_lexAnalyzer->getNextToken();
			synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable, m_expVec);
			if (!e->checkSyntax(funcName, symbolToUpdate))
				return false;
			m_expVec->push_back(t);
			t = m_lexAnalyzer->getNextToken();
			if (t->getLex().compare("]"))
			{
				//Error - Expected "]"
				if (!m_errorModule->addErrorSyn(t->getLineNumber(), SYNTAX_ERROR_CBRACKET))
					return false;
			}
		}
		else if (!m_lexAnalyzer->peekToken()->getLex().compare("("))
		{
			m_expVec->push_back(t);
			t = m_lexAnalyzer->getNextToken();
			synState_FuncCall* f = new synState_FuncCall(m_lexAnalyzer, m_errorModule, m_symTable);
			if (!f->checkSyntax())
				return false;
		}
		else
		{
			m_expVec->push_back(t);
		}
	}
	if (m_lexAnalyzer->peekToken()->getType() == TOKEN_TYPE::ARIT_OP || m_lexAnalyzer->peekToken()->getType() == TOKEN_TYPE::LOGICAL_OP || m_lexAnalyzer->peekToken()->getType() == TOKEN_TYPE::REL_OP)
	{
		t = m_lexAnalyzer->getNextToken();
		m_expVec->push_back(t);
		synState_ExpLog* e = new synState_ExpLog(m_lexAnalyzer, m_errorModule, m_symTable, m_expVec);
		if (!e->checkSyntax(funcName, symbolToUpdate))
			return false;
	}
	if (!(m_errorModule->Errors->Length > errorCount))
	{
		expLog* newExp = new expLog(t->getLineNumber(), funcName, *m_expVec, symbolToUpdate);
		newExp->buildTree();
		newExp->getLineNum();
	}
	return true;
}