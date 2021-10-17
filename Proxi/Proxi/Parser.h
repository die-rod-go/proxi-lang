#pragma once
#include "Token.h"
#include <vector>
#include "Expr.h"
#include <string>

template<typename T>
class Parser
{
public:
	Parser(std::vector<Token> tokens);
private:
	const std::vector<Token> tokens;
	int current;

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
	Token consume(TokenType type, std::string message);
};

