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
	Literal_Token nullLiteral;

	int start;
	int current;
	int line;

	int currentOnLine; //	where on the current line it is (for debugging purposes)

	const std::string source;
	std::vector<Token> tokens;

	bool isAtEnd();
	void scanToken();
	char advance();
	void addToken(TokenType type);
	void addToken(TokenType type, Literal_Token lit);
	bool match(char expected);	//	checks if two characters are equal, advances if tey are
	char peek();
	char peekNext();

	void string();
	void number();
	void identifier();

	int getLength(int start, int current);

	std::unordered_map<std::string, TokenType> keywords;

	// debug
	void printCurrent();

};

