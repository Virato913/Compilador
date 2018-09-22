#pragma once

#include <string>

using std::string;

namespace compilerCore
{
	enum class TOKEN_TYPE
	{
		UNDEFINED = 0,
		ID,
		INT,
		FLOAT,
		STRING,
		KEYWORD,
		LOGICAL_OP,
		UNARY_LOGICAL_OP,
		ARIT_OP,
		REL_OP,
		ASSIGN,
		DEL,
		AGROUP_OP,
		DIMEN_OP
	};

	class token
	{
	private:
		string m_Lex;
		TOKEN_TYPE m_Type;
		int m_LineNumber;

	public:
		token(string, TOKEN_TYPE, int);
		~token();

		string getLex() const { return m_Lex; }
		string getTypeStr();
		TOKEN_TYPE getType() const { return m_Type; }
		int getLineNumber() const { return m_LineNumber; }
	};
}