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
	bool boolLit;
	bool isNull = true;
	int intLit;
	float floatLit;
	std::string stringLit;
	TokenType type;

	Literal(bool boolLit, int intLit, float floatLit, std::string stringLit, bool isNull, TokenType type)
	{
		this->boolLit = boolLit;
		this->intLit = intLit;
		this->floatLit = floatLit;
		this->stringLit = stringLit;
		this->isNull = isNull;
		this->type = type;
	}

	Literal(int intLit)
	{
		this->floatLit = -1;
		this->stringLit = "NULL";

		this->intLit = intLit;
		this->isNull = false;
		this->type = INTEGER;
	}

	Literal(float floatLit)
	{
		this->intLit = -1;
		this->stringLit = "NULL";

		this->floatLit = floatLit;
		this->isNull = false;
		this->type = FLOATING_POINT;
	}

	Literal(std::string stringLit)
	{
		this->intLit = -1;
		this->floatLit = -1;

		this->stringLit = stringLit;
		this->isNull = false;
		this->type = STRING_LIT;
	}

	Literal(bool boolLit)
	{
		this->boolLit;
		this->intLit = -1;
		this->floatLit = -1;
		this->stringLit = "NULL";
		this->isNull = true;
		if (boolLit)
			this->type = TRUE;
		else
			this->type = FALSE;
	}

	Literal(TokenType type)
	{
		this->boolLit = false;
		this->intLit = -1;
		this->floatLit = -1;
		this->stringLit = "NULL";
		this->isNull = true;
		this->type = NOV;
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
	void emplaceMap();

};



