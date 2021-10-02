#pragma once
#include <string>
#include <unordered_map>

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
	IDENTIFIER, INTEGER, FLOATING_POINT, STRING_LIT, 

	// Keywords.
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NOV, OR,
	PRINT, RETURN, SUPER, SELF, THIS, TRUE,
	INT, FLOAT, BOOL, STRING, WHILE,

	END_OF_FILE
};

class Literal
{
public:
	bool isNull = true;
	int intLit;
	float floatLit;
	std::string stringLit;

	Literal(int intLit, float floatLit, std::string stringLit, bool isNull)
	{
		this->intLit = intLit;
		this->floatLit = floatLit;
		this->stringLit = stringLit;
		this->isNull = isNull;
	}

	Literal(int intLit, bool isNull)
	{
		this->intLit = intLit;
		this->isNull = isNull;
	}

	Literal(float floatLit, bool isNull)
	{
		this->floatLit = floatLit;
		this->isNull = isNull;
	}

	Literal(std::string stringLit, bool isNull)
	{
		this->stringLit = stringLit;
		this->isNull = isNull;
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


private:
	std::unordered_map<TokenType, std::string> enumStrings;	//	for outputting enums - mostly for debugging

};



