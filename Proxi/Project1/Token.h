#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

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

class Literal_Token
{
public:
	bool isNull = true;
	std::string stringLit;
	TokenType type;
	
	int iValue;
	float fValue;
	std::string sValue;
	bool bValue;

	Literal_Token(int intLit)
	{
		this->iValue = intLit;
		this->isNull = false;
		this->type = TokenType::INTEGER;
	}

	Literal_Token(float floatLit)
	{
		this->fValue = floatLit;
		this->isNull = false;
		this->type = TokenType::FLOATING_POINT;
	}

	Literal_Token(std::string stringLit)
	{
		this->stringLit = stringLit;
		this->isNull = false;
		this->type = TokenType::STRING_LIT;
	}

	Literal_Token(bool boolLit)
	{
		this->bValue = boolLit;
		this->isNull = false;
		if (boolLit)
			this->type = TokenType::TRUE;
		else
			this->type = TokenType::FALSE;
	}

	Literal_Token(TokenType type)
	{
		this->isNull = true;
		this->type = TokenType::NOV;
	}

	std::string toString()
	{
		if (type == TokenType::INTEGER)
			return std::to_string(iValue);
		else if (type == TokenType::FLOAT)
			return std::to_string(fValue);
		else if (type == TokenType::STRING)
			return sValue;
		//else if()
	}

	~Literal_Token()
	{

	}
};

class Token
{
public:
	const TokenType type;
	const std::string lexeme;
	const Literal_Token lit;
	const int line;
	Token(TokenType type, std::string lexeme, Literal_Token lit, int line);
	std::string toString();


private:
	std::unordered_map<TokenType, std::string> enumStrings;	//	for outputting enums - mostly for debugging
	void emplaceMap();

};



