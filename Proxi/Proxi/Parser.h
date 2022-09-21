#pragma once
#include "Proxi.h"
#include "Token.h"
#include <vector>
#include "Expr.h"
#include <string>

class ParseError : std::runtime_error {};

template<typename T>
class Parser
{
public:
	Parser(std::vector<Token> tokens);
	Expr<T> parse();
private:
	const std::vector<Token> tokens;
	int current = 0;

	Expr<T> expression();
	Expr<T> equality();
	Expr<T> comparison();
	Expr<T> term();
	Expr<T> factor();

	Expr<T> unary();
	Expr<T> primary();

	bool match(std::vector<TokenType> types);
	bool check(TokenType type);
	Token advance();
	bool isAtEnd();
	Token peek();
	Token previous();
	ParseError error(Token token, std::string message);
	void synchronize();
	Token consume(TokenType type, std::string message);
};

