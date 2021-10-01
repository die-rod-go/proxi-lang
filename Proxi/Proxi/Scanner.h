#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Token.h"
#include "Proxi.h"


class Scanner
{
public:
	Scanner(std::string source);
	std::vector<Token> scanTokens();
	
private:
	Literal nullLiteral;

	int start;
	int current;
	int line;
	const std::string source;
	std::vector<Token> tokens;

	bool isAtEnd();
	void scanToken();
	char advance();
	void addToken(TokenType type);
	void addToken(TokenType type, Literal lit);
	bool match(char expected);	//	checks if two characters are equal
	char peek();
	char peekNext();

	void string();
	void number();
	void identifier();

	std::unordered_map<std::string, TokenType> keywords;

};

