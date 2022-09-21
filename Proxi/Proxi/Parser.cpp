#include "Parser.h"

template<typename T>
Parser<T>::Parser(std::vector<Token> tokens) : tokens(tokens)
{
}

template<typename T>
Expr<T> Parser<T>::parse()
{
	try
	{
		return expression();
	}
	catch (ParseError error)
	{
		return NULL;
	}
}

template<typename T>
Expr<T> Parser<T>::expression()
{
	return equality();
}

template<typename T>
Expr<T> Parser<T>::equality()
{
	Expr<T> expr = comparison();

	while (match({ BANG_EQUAL, EQUAL_EQUAL }))
	{
		Token oper = previous();
		Expr<T> right = comparison();
		expr = Binary<T>(expr, oper, right);
	}

	return expr;
}

template<typename T>
Expr<T> Parser<T>::comparison()
{
	Expr<T> expr = term();

	while (match({ GREATER, GREATER_EQUAL, LESS, LESS_EQUAL }))
	{
		Token oper = previous();
		Expr<T> right = term();
		expr = Binary<T>(expr, oper, right);
	}

	return expr;
}

template<typename T>
Expr<T> Parser<T>::term()
{
	Expr<T> expr = factor();

	while (match({ MINUS, PLUS }))
	{
		Token oper = previous();
		Expr<T> right = factor();
		expr = Binary<T>(expr, oper, right);
	}

	return expr;
}

template<typename T>
Expr<T> Parser<T>::factor()
{
	Expr<T> expr = unary();

	while (match({ SLASH, STAR }))
	{
		Token oper = previous();
		Expr<T> right = unary();
		expr = Binary<T>(expr, oper, right);
	}

	return expr;
}

template<typename T>
Expr<T> Parser<T>::unary()
{
	if (match({ BANG, MINUS }))
	{
		Token oper = previous();
		Expr<T> right = unary();
		return Unary<T>(oper, right);
	}

	return primary();
}

template<typename T>
Expr<T> Parser<T>::primary()
{
	if (match(FALSE))
		return LiteralExpression<T>(Literal(false));
	if (match(TRUE))
		return LiteralExpression<T>(Literal(true));
	if (match(NOV))
		return LiteralExpression<T>(Literal(NOV));

	if (match(INTEGER, FLOATING_POINT, STRING))
		return LiteralExpression<T>(previous().lit);

	if (match(LEFT_PAREN))
	{
		Expr expr = expression();
		consume(RIGHT_PAREN, "Expect ')' after expression.");
		return Grouping<T>(expr);
	}

	throw error(peek(), "Expect expression");
}

template<typename T>
bool Parser<T>::match(std::vector<TokenType> types)
{
	for (TokenType type : types)
	{
		if (check(type))
		{
			advance();
			return true;
		}
	}

	return false;
}

template<typename T>
bool Parser<T>::check(TokenType type)
{
	if (isAtEnd())
		return false;
	return peek().type == type;
}

template<typename T>
Token Parser<T>::advance()
{
	if (!isAtEnd())
		current++;
	return previous();
}

template<typename T>
bool Parser<T>::isAtEnd()
{
	return peek().type == END_OF_FILE;
}

template<typename T>
Token Parser<T>::peek()
{
	return tokens[current];
}

template<typename T>
Token Parser<T>::previous()
{
	return tokens[current - 1];
}

template<typename T>
ParseError Parser<T>::error(Token token, std::string message)
{
	//Proxi.error(token, message);
	ParseError error;
	return error;
}

template<typename T>
void Parser<T>::synchronize()
{
	advance();

	while (!isAtEnd())
	{
		if (previous().type == SEMICOLON)
			return;

		switch (peek().type)
		{
		case CLASS:
		case FUN:
		case INT:
		case FLOAT:
		case STRING:
		case FOR:
		case IF:
		case WHILE:
		case PRINT:
		case RETURN:
			return;
		}
	}
}

template<typename T>
Token Parser<T>::consume(TokenType type, std::string message)
{
	if (check(type))
		return advance();
	throw error(peek(), message);
}
