#include "stdafx.h"
#include "Token.h"

compilerCore::token::token(string lex, TOKEN_TYPE type, int lineNum)
{
	m_Lex = lex;
	m_Type = type;
	m_LineNumber = lineNum;
}

compilerCore::token::~token()
{
	
}

string compilerCore::token::getTypeStr()
{
	switch (m_Type)
	{
	case compilerCore::TOKEN_TYPE::UNDEFINED:
		return string("Sin definir");
		break;
	case compilerCore::TOKEN_TYPE::ID:
		return string("ID");
		break;
	case compilerCore::TOKEN_TYPE::INT:
		return string("ID");
		break;
	case compilerCore::TOKEN_TYPE::FLOAT:
		return string("ID");
		break;
	case compilerCore::TOKEN_TYPE::STRING:
		return string("ID");
		break;
	case compilerCore::TOKEN_TYPE::KEYWORD:
		return string("Keyword");
		break;
	case compilerCore::TOKEN_TYPE::LOGICAL_OP:
		return string("Operador logico");
		break;
	case compilerCore::TOKEN_TYPE::UNARY_LOGICAL_OP:
		return string("Operador logico unario");
		break;
	case compilerCore::TOKEN_TYPE::ARIT_OP:
		return string("Operador aritmetico");
		break;
	case compilerCore::TOKEN_TYPE::REL_OP:
		return string("Operador relacional");
		break;
	case compilerCore::TOKEN_TYPE::ASSIGN:
		return string("Operador de asignacion");
		break;
	case compilerCore::TOKEN_TYPE::DEL:
		return string("Delimitador");
		break;
	case compilerCore::TOKEN_TYPE::AGROUP_OP:
		return string("Agrupacion");
		break;
	case compilerCore::TOKEN_TYPE::DIMEN_OP:
		return string("Operador de dimension");
		break;
	default:
		return string("Desconocido");
		break;
	}
}