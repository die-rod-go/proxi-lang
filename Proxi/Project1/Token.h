#pragma once
#include <string>
#include <unordered_map>

enum class TokenType {	//	put the enum info FIRST because not doing so causes a weird dependency issue
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
	std::string stringLit;
	TokenType type;
	
	int iValue;
	float fValue;
	std::string sValue;
	bool bValue;

	Literal(int intLit)
	{
		this->iValue = intLit;
		this->isNull = false;
		this->type = TokenType::INTEGER;
	}

	Literal(float floatLit)
	{
		this->fValue = floatLit;
		this->isNull = false;
		this->type = TokenType::FLOATING_POINT;
	}

	Literal(std::string stringLit)
	{
		this->stringLit = stringLit;
		this->isNull = false;
		this->type = TokenType::STRING_LIT;
	}

	Literal(bool boolLit)
	{
		this->bValue = boolLit;
		this->isNull = false;
		if (boolLit)
			this->type = TokenType::TRUE;
		else
			this->type = TokenType::FALSE;
	}

	Literal(TokenType type)
	{
		this->isNull = true;
		this->type = TokenType::NOV;
	}

	~Literal()
	{

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



