#include "stdafx.h"
#include "LexAnalyzer.h"

compilerCore::lexAnalyzer::lexAnalyzer(errorModule^ errorsModule)
{
	m_errorModule = errorsModule;
	m_Keywords.insert(std::make_pair("var", ""));
	m_Keywords.insert(std::make_pair("int", ""));
	m_Keywords.insert(std::make_pair("float", ""));
	m_Keywords.insert(std::make_pair("string", ""));
	m_Keywords.insert(std::make_pair("bool", ""));
	m_Keywords.insert(std::make_pair("void", ""));
	m_Keywords.insert(std::make_pair("function", ""));
	m_Keywords.insert(std::make_pair("main", ""));
	m_Keywords.insert(std::make_pair("if", ""));
	m_Keywords.insert(std::make_pair("else", ""));
	m_Keywords.insert(std::make_pair("while", ""));
	m_Keywords.insert(std::make_pair("for", ""));
	m_Keywords.insert(std::make_pair("inc", ""));
	m_Keywords.insert(std::make_pair("dec", ""));
	m_Keywords.insert(std::make_pair("switch", ""));
	m_Keywords.insert(std::make_pair("case", ""));
	m_Keywords.insert(std::make_pair("default", ""));
	m_Keywords.insert(std::make_pair("print", ""));
	m_Keywords.insert(std::make_pair("read", ""));
	m_Keywords.insert(std::make_pair("return", ""));
	m_Keywords.insert(std::make_pair("true", ""));
	m_Keywords.insert(std::make_pair("false", ""));
}

compilerCore::lexAnalyzer::~lexAnalyzer()
{
	m_Keywords.clear();
	m_Tokens.clear();
}

bool compilerCore::lexAnalyzer::parseSourceCode(const char* sourceCode)
{
	int lineNum = 1;
	const char* currChar = sourceCode;
	string buffer;
	string lineBuffer;
	token* newToken;
	LEX_STATE state = LEX_STATE::START;
	while (*currChar != '\0')
	{
		switch (state)
		{
		case compilerCore::LEX_STATE::START:
			if (isalpha(*currChar) || *currChar == '_')
			{
				buffer.clear();
				buffer.append(currChar, 1);
				currChar++;
				state = LEX_STATE::ID;
			}
			else if (isdigit(*currChar))
			{
				buffer.clear();
				buffer.append(currChar, 1);
				currChar++;
				state = LEX_STATE::INT;
			}
			else if (*currChar == '"')
			{
				buffer.clear();
				buffer.append(currChar, 1);
				currChar++;
				state = LEX_STATE::STRING;
			}
			else if (*currChar == '&' || *currChar == '|')
			{
				buffer.clear();
				buffer.append(currChar, 1);
				currChar++;
				state = LEX_STATE::LOGICAL_OP;
			}
			else if (*currChar == '+' || *currChar == '-' || *currChar == '/' || *currChar == '*' || *currChar == '%' || *currChar == '^')
			{
				buffer.clear();
				buffer.append(currChar, 1);
				currChar++;
				state = LEX_STATE::ARIT_OP;
			}
			else if (*currChar == '<' || *currChar == '>' || *currChar == '!' || *currChar == '=')
			{
				buffer.clear();
				buffer.append(currChar, 1);
				currChar++;
				state = LEX_STATE::REL_OP;
			}
			else if (*currChar == '.' || *currChar == ',' || *currChar == ':' || *currChar == ';')
			{
				buffer.clear();
				buffer.append(currChar, 1);
				currChar++;
				state = LEX_STATE::DEL;
			}
			else if (*currChar == '{' || *currChar == '}' || *currChar == '(' || *currChar == ')')
			{
				buffer.clear();
				buffer.append(currChar, 1);
				currChar++;
				state = LEX_STATE::AGROUP_OP;
			}
			else if (*currChar == '[' || *currChar == ']')
			{
				buffer.clear();
				buffer.append(currChar, 1);
				currChar++;
				state = LEX_STATE::DIMEN_OP;
			}
			else if (*currChar == ' ' || *currChar == '\t' || *currChar == '\n')
			{
				if (*currChar == '\n')
					lineNum++;
				currChar++;
			}
			else
			{
				//m_errorModule->addErrorLex(lineNum, LEX_ERROR_INVALID_CHARACTER, );
				currChar++;
			}
			break;
		case compilerCore::LEX_STATE::ID:
			if (isalnum(*currChar) || *currChar == '_')
			{
				buffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				if (m_Keywords.find(buffer) != m_Keywords.end())
				{
					newToken = new token(buffer, compilerCore::TOKEN_TYPE::KEYWORD, lineNum);
					m_Tokens.push_back(newToken);
				}
				else
				{
					newToken = new token(buffer, compilerCore::TOKEN_TYPE::ID, lineNum);
					m_Tokens.push_back(newToken);
				}
				state = LEX_STATE::START;
			}
			break;
		case compilerCore::LEX_STATE::INT:
			if (isdigit(*currChar))
			{
				buffer.append(currChar, 1);
				currChar++;
			}
			else if (*currChar == '.')
			{
				buffer.append(currChar, 1);
				currChar++;
				state = LEX_STATE::FLOAT;
			}
			else
			{
				newToken = new token(buffer, compilerCore::TOKEN_TYPE::INT, lineNum);
				m_Tokens.push_back(newToken);
			}
			break;
		case compilerCore::LEX_STATE::FLOAT:
			if (isdigit(*currChar))
			{
				buffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				newToken = new token(buffer, compilerCore::TOKEN_TYPE::FLOAT, lineNum);
				m_Tokens.push_back(newToken);
			}
			break;
		case compilerCore::LEX_STATE::STRING:
			break;
		case compilerCore::LEX_STATE::LOGICAL_OP:
			break;
		case compilerCore::LEX_STATE::ARIT_OP:
			break;
		case compilerCore::LEX_STATE::REL_OP:
			break;
		case compilerCore::LEX_STATE::DEL:
			break;
		case compilerCore::LEX_STATE::AGROUP_OP:
			break;
		case compilerCore::LEX_STATE::DIMEN_OP:
			break;
		default:
			break;
		}
	}
	return 0;
}

void compilerCore::lexAnalyzer::reset()
{
	m_errorModule->reset();
	m_Tokens.clear();
	//m_Tokens.resize(0);
}

void compilerCore::lexAnalyzer::getTokens(vector<token*>* tokensVec) const
{
	tokensVec[0] = m_Tokens;
}