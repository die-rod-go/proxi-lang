#pragma once
#include <string>

enum TokenType {	//	put the enum info FIRST because not doing so causes a weird dependency issue
	// Single-character tokens.
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// One or two character tokens.
	BANG, BANG_EQUAL,		// ! !=
	EQUAL, EQUAL_EQUAL,		// = == 
	GREATER, GREATER_EQUAL,	// > >=
	LESS, LESS_EQUAL,		// < <=

	// Literals.
	IDENTIFIER, INTEGER, FLOATING_POINT, BOOLEAN, STRING_LIT, 

	// Keywords.
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NOV, OR,
	PRINT, RETURN, SUPER, SELF, THIS, TRUE,
	INT, FLOAT, BOOL, STRING, WHILE,

	END_OF_FILE
};

class Literal
{
public:
	bool boolLit;
	int intLit;
	float floatLit;
	std::string stringLit;

	Literal(bool boolLit, int intLit, float floatLit, std::string stringLit)
	{
		this->boolLit = boolLit;
		this->intLit = intLit;
		this->floatLit = floatLit;
		this->stringLit = stringLit;
	}
};

class Token
{
public:
	const TokenType type;
	const std::string lexeme;
	const Literal lit;
	const int line;
	Token(TokenType type, std::string lexeme, Literal lit, int line);
	std::string toString();

};



