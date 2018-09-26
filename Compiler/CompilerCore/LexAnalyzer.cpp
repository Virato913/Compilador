#include "stdafx.h"
#include "LexAnalyzer.h"

bool isLogical(const char currChar);
bool isArithmetic(const char currChar);
bool isRelational(const char currChar);
bool isDelimiter(const char currChar);
bool isGrouping(const char currChar);
bool isDimensional(const char currChar);
bool isBlank(const char currChar);
bool isValidChar(const char currChar);

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
	int commentLine;
	const char* currChar = sourceCode;
	const char* currLine = sourceCode;
	string buffer;
	string lineBuffer;
	string commentBuffer;
	string line = sourceCode;
	size_t errorPos = line.find('\n');
	string errorLine = line.substr(0, errorPos - 1);
	token* newToken;
	LEX_STATE state = LEX_STATE::START;
	while (*currChar != '\0' || buffer.size() > 0)
	{
		switch (state)
		{
		case compilerCore::LEX_STATE::START:
			if (isValidChar(*currChar))
			{
				if (isalpha(static_cast<unsigned char>(*currChar)) || *currChar == '_')
				{
					buffer.clear();
					buffer.append(currChar, 1);
					currChar++;
					state = LEX_STATE::ID;
				}
				else if (isdigit(static_cast<unsigned char>(*currChar)))
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
				else if (isLogical(*currChar))
				{
					buffer.clear();
					buffer.append(currChar, 1);
					currChar++;
					state = LEX_STATE::LOGICAL_OP;
				}
				else if (isArithmetic(*currChar))
				{
					buffer.clear();
					buffer.append(currChar, 1);
					currChar++;
					state = LEX_STATE::ARIT_OP;
				}
				else if (isRelational(*currChar))
				{
					buffer.clear();
					buffer.append(currChar, 1);
					currChar++;
					state = LEX_STATE::REL_OP;
				}
				else if (isDelimiter(*currChar))
				{
					buffer.clear();
					buffer.append(currChar, 1);
					currChar++;
					state = LEX_STATE::DEL;
				}
				else if (isGrouping(*currChar))
				{
					buffer.clear();
					buffer.append(currChar, 1);
					currChar++;
					state = LEX_STATE::AGROUP_OP;
				}
				else if (isDimensional(*currChar))
				{
					buffer.clear();
					buffer.append(currChar, 1);
					currChar++;
					state = LEX_STATE::DIMEN_OP;
				}
				else if (isBlank(*currChar))
				{
					if (*currChar == '\n')
					{
						line = line.substr(errorPos + 1);
						errorPos = line.find('\n');
						errorLine = line.substr(0, errorPos - 1);
						lineNum++;
					}
					currChar++;
				}
			}
			else
			{
				//errorPos = line.find('\n');
				//lineBuffer = line.substr(0, errorPos - 2);
				//line = line.substr(errorPos + 1);
				//errorPos = currChar - currLine;
				//lineBuffer.clear();
				//lineBuffer.append(currLine, errorPos);
				if (!m_errorModule->addErrorLex(lineNum, LEX_ERROR_INVALID_CHARACTER, errorLine.c_str()))
				{
					return false;
				}
				currChar++;
			}
			break;
		case compilerCore::LEX_STATE::ID:
			if (isalnum(static_cast<unsigned char>(*currChar)) || *currChar == '_')
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
					buffer.clear();
				}
				else
				{
					newToken = new token(buffer, compilerCore::TOKEN_TYPE::ID, lineNum);
					m_Tokens.push_back(newToken);
					buffer.clear();
				}
				state = LEX_STATE::START;
			}
			break;
		case compilerCore::LEX_STATE::INT:
			if (isdigit(static_cast<unsigned char>(*currChar)))
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
				if (isalpha(static_cast<unsigned char>(*currChar)))
				{
					//errorPos = line.find('\n');
					//lineBuffer = line.substr(0, errorPos - 2);
					//line = line.substr(errorPos + 1);
					//errorPos = currChar - currLine;
					//lineBuffer.clear();
					//lineBuffer.append(currLine, errorPos);
					if (!m_errorModule->addErrorLex(lineNum, "Invalid number", errorLine.c_str()))
					{
						return false;
					}
					currChar++;
				}
				else
				{
					newToken = new token(buffer, compilerCore::TOKEN_TYPE::INT, lineNum);
					m_Tokens.push_back(newToken);
					buffer.clear();
				}
				state = LEX_STATE::START;
			}
			break;
		case compilerCore::LEX_STATE::FLOAT:
			if (isdigit(static_cast<unsigned char>(*currChar)))
			{
				buffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				if (isalpha(static_cast<unsigned char>(*currChar))/* || *currChar == '.'*/ || buffer.back() == '.')
				{
					//errorPos = line.find('\n');
					//lineBuffer = line.substr(0, errorPos - 2);
					//line = line.substr(errorPos + 1);
					//errorPos = currChar - currLine;
					//lineBuffer.clear();
					//lineBuffer.append(currLine, errorPos);
					if (!m_errorModule->addErrorLex(lineNum, LEX_ERROR_INVALID_FLOAT, errorLine.c_str()))
					{
						return false;
					}
					currChar++;
				}
				else
				{
					newToken = new token(buffer, compilerCore::TOKEN_TYPE::FLOAT, lineNum);
					m_Tokens.push_back(newToken);
					buffer.clear();
				}
				state = LEX_STATE::START;
			}
			break;
		case compilerCore::LEX_STATE::STRING:
			if (*currChar != '"')
			{
				if (*currChar != '\r')
				{
					buffer.append(currChar, 1);
					currChar++;
				}
				else
				{
					buffer.append(currChar, 1);
					currChar++;
					//if (*currChar != '\n')
					//{
						//errorPos = line.find('\n');
						//lineBuffer = line.substr(0, errorPos - 2);
						//line = line.substr(errorPos + 1);
						//errorPos = currChar - currLine;
						//lineBuffer.clear();
						//lineBuffer.append(currLine, errorPos);
						if (!m_errorModule->addErrorLex(lineNum, LEX_ERROR_STRING_NOT_CLOSED, errorLine.c_str()))
						{
							return false;
						}
						//currChar++;
						state = LEX_STATE::START;
					//}
				}
			}
			else
			{
				buffer.append(currChar, 1);
				currChar++;
				newToken = new token(buffer, compilerCore::TOKEN_TYPE::STRING, lineNum);
				m_Tokens.push_back(newToken);
				buffer.clear();
				state = LEX_STATE::START;
			}
			break;
		case compilerCore::LEX_STATE::LOGICAL_OP:
			if (*currChar != buffer.back())
			{
				//errorPos = line.find('\n');
				//lineBuffer = line.substr(0, errorPos - 2);
				//line = line.substr(errorPos + 1);
				//errorPos = currChar - currLine;
				//lineBuffer.clear();
				//lineBuffer.append(currLine, errorPos);
				if (buffer.back() == '&')
				{
					if (!m_errorModule->addErrorLex(lineNum, LEX_ERROR_INVALID_LOGICAL_OP_AND, errorLine.c_str()))
					{
						return false;
					}
				}
				else
				{
					if (!m_errorModule->addErrorLex(lineNum, LEX_ERROR_INVALID_LOGICAL_OP_OR, errorLine.c_str()))
					{
						return false;
					}
				}
				currChar++;
				state = LEX_STATE::START;
			}
			else
			{
				buffer.append(currChar, 1);
				currChar++;
				newToken = new token(buffer, compilerCore::TOKEN_TYPE::LOGICAL_OP, lineNum);
				m_Tokens.push_back(newToken);
				buffer.clear();
				state = LEX_STATE::START;
			}
			break;
		case compilerCore::LEX_STATE::ARIT_OP:
			if (isdigit(static_cast<unsigned char>(*currChar)) && buffer.back() == '-')
			{
				buffer.append(currChar, 1);
				currChar++;
				state = LEX_STATE::INT;
			}
			else if (*currChar == '.' && buffer.back() == '-')
			{
				buffer.append(currChar, 1);
				currChar++;
				state = LEX_STATE::FLOAT;
			}
			else if ((*currChar == '+' || *currChar == '-') && *currChar == buffer.back())
			{
				buffer.append(currChar, 1);
				currChar++;
				newToken = new token(buffer, compilerCore::TOKEN_TYPE::ARIT_OP, lineNum);
				m_Tokens.push_back(newToken);
				buffer.clear();
				state = LEX_STATE::START;
			}
			else if (*currChar == '*' && buffer.back() == '/')
			{
				//buffer.append(currChar, 1);
				//buffer.clear();
				commentBuffer.clear();
				currChar++;
				commentLine = lineNum;
				lineBuffer = errorLine;
				state = LEX_STATE::COMMENT;
			}
			else
			{
				newToken = new token(buffer, compilerCore::TOKEN_TYPE::ARIT_OP, lineNum);
				m_Tokens.push_back(newToken);
				buffer.clear();
				state = LEX_STATE::START;
			}
			break;
		case compilerCore::LEX_STATE::REL_OP:
			if (*currChar != '=')
			{
				if (isRelational(*currChar))
				{
					//errorPos = line.find('\n');
					//lineBuffer = line.substr(0, errorPos - 2);
					//line = line.substr(errorPos + 1);
					//errorPos = currChar - currLine;
					//lineBuffer.clear();
					//lineBuffer.append(currLine, errorPos);
					if (!m_errorModule->addErrorLex(lineNum, "Invalid relational operator", errorLine.c_str()))
					{
						return false;
					}
					currChar++;
					state = LEX_STATE::START;
				}
				else if (buffer.back() == '=')
				{
					newToken = new token(buffer, compilerCore::TOKEN_TYPE::ASSIGN, lineNum);
					m_Tokens.push_back(newToken);
					buffer.clear();
				}
				else if (buffer.back() == '!')
				{
					newToken = new token(buffer, compilerCore::TOKEN_TYPE::UNARY_LOGICAL_OP, lineNum);
					m_Tokens.push_back(newToken);
					buffer.clear();
				}
				else
				{
					newToken = new token(buffer, compilerCore::TOKEN_TYPE::REL_OP, lineNum);
					m_Tokens.push_back(newToken);
					buffer.clear();
				}
				state = LEX_STATE::START;
			}
			else
			{
				buffer.append(currChar, 1);
				currChar++;
				newToken = new token(buffer, compilerCore::TOKEN_TYPE::REL_OP, lineNum);
				m_Tokens.push_back(newToken);
				buffer.clear();
				state = LEX_STATE::START;
			}
			break;
		case compilerCore::LEX_STATE::DEL:
			if (isdigit(static_cast<unsigned char>(*currChar)) && buffer.back() == '.')
			{
				buffer.append(currChar, 1);
				currChar++;
				state = LEX_STATE::FLOAT;
			}
			else
			{
				newToken = new token(buffer, compilerCore::TOKEN_TYPE::DEL, lineNum);
				m_Tokens.push_back(newToken);
				buffer.clear();
				state = LEX_STATE::START;
			}
			break;
		case compilerCore::LEX_STATE::AGROUP_OP:
			newToken = new token(buffer, compilerCore::TOKEN_TYPE::AGROUP_OP, lineNum);
			m_Tokens.push_back(newToken);
			buffer.clear();
			state = LEX_STATE::START;
			break;
		case compilerCore::LEX_STATE::DIMEN_OP:
			newToken = new token(buffer, compilerCore::TOKEN_TYPE::DIMEN_OP, lineNum);
			m_Tokens.push_back(newToken);
			buffer.clear();
			state = LEX_STATE::START;
			break;
		case compilerCore::LEX_STATE::COMMENT:
			if (*currChar == '\n' || *currChar == '\0')
			{
				if (*currChar == '\n')
				{
					line = line.substr(errorPos + 1);
					errorPos = line.find('\n');
					errorLine = line.substr(0, errorPos - 1);
					lineNum++;
					commentBuffer.append(currChar, 1);
					currChar++;
				}
				else
				{
					//errorPos = line.find('\n');
					//lineBuffer = line.substr(0, errorPos - 2);
					//line = line.substr(errorPos + 1);
					//errorPos = currChar - currLine;
					//lineBuffer.clear();
					//lineBuffer.append(currLine, errorPos);
					if (!m_errorModule->addErrorLex(commentLine, LEX_ERROR_COMMENT_NOT_CLOSED, lineBuffer.c_str()))
					{
						return false;
					}
					currChar++;
					buffer.clear();
				}
			}
			else
			{
				if (commentBuffer.size() > 0)
				{
					if (*currChar == '/' && commentBuffer.back() == '*')
					{
						currChar++;
						state = LEX_STATE::START;
					}
					else
					{
						commentBuffer.append(currChar, 1);
						currChar++;
					}
				}
				else
				{
					commentBuffer.append(currChar, 1);
					currChar++;
				}
			}
			break;
		default:
			break;
		}
	}
	return true;
}

void compilerCore::lexAnalyzer::reset()
{
	//m_errorModule->reset();
	m_Tokens.clear();
	//m_Tokens.resize(0);
}

void compilerCore::lexAnalyzer::getTokens(vector<token*>* tokensVec) const
{
	*tokensVec = m_Tokens;
}

bool isLogical(const char currChar)
{
	return (currChar == '&' || currChar == '|');
}

bool isArithmetic(const char currChar)
{
	return (currChar == '+' || currChar == '-' || currChar == '/' || currChar == '*' || currChar == '%' || currChar == '^');
}

bool isRelational(const char currChar)
{
	return (currChar == '<' || currChar == '>' || currChar == '!' || currChar == '=');
}

bool isDelimiter(const char currChar)
{
	return (currChar == '.' || currChar == ',' || currChar == ':' || currChar == ';');
}

bool isGrouping(const char currChar)
{
	return (currChar == '{' || currChar == '}' || currChar == '(' || currChar == ')');
}

bool isDimensional(const char currChar)
{
	return (currChar == '[' || currChar == ']');
}

bool isBlank(const char currChar)
{
	return (currChar == ' ' || currChar == '\t' || currChar == '\n' || currChar == '\r');
}

bool isValidChar(const char currChar)
{
	return (isalnum(static_cast<unsigned char>(currChar)) || isLogical(currChar) || isArithmetic(currChar) || isRelational(currChar) || isDelimiter(currChar) || isGrouping(currChar) || isDimensional(currChar) || isBlank(currChar) || currChar == '_' || currChar == '"');
}