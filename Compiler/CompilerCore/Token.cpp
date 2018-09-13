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
	case compilerCore::UNDEFINED:
		return string("Sin definir");
		break;
	case compilerCore::ID:
		return string("ID");
		break;
	case compilerCore::KEYWORD:
		return string("Keyword");
		break;
	case compilerCore::LOGICAL_OP:
		return string("Operador logico");
		break;
	case compilerCore::UNARY_LOGICAL_OP:
		return string("Operador logico unario");
		break;
	case compilerCore::ARIT_OP:
		return string("Operador aritmetico");
		break;
	case compilerCore::REL_OP:
		return string("Operador relacional");
		break;
	case compilerCore::ASSIGN:
		return string("Operador de asignacion");
		break;
	case compilerCore::DEL:
		return string("Delimitador");
		break;
	case compilerCore::AGROUP_OP:
		return string("Agrupacion");
		break;
	case compilerCore::DIMEN_OP:
		return string("Operador de dimension");
		break;
	default:
		return string("Desconocido");
		break;
	}
}