#include "Token.h"
#include <iostream>

template<typename T>
class Binary;

template<typename T>
class Grouping;

template<typename T>
class LiteralExpression;

template<typename T>
class Unary;

template <typename T>
class Visitor {
public:
	virtual T visitBinaryExpr(Binary<T> expr) { T temp;  return temp; };
	virtual T visitGroupingExpr(Grouping<T> expr) { T temp;  return temp; };
	virtual T visitLiteralExpressionExpr(LiteralExpression<T> expr) { T temp;  return temp; };
	virtual T visitUnaryExpr(Unary<T> expr) { T temp;  return temp; };
};


template <typename T>
class Expr { // visitable
public:
	virtual T accept(Visitor<T> visitor) { std::cout << "please" << std::endl; T temp; return temp; };
};

template<typename T>
class Binary : public Expr<T> {
public:
	Binary(Expr<T> left, Token oper, Expr<T> right) : left(left), oper(oper), right(right)	{
	}

	T accept(Visitor<T> visitor) {
		return visitor.visitBinaryExpr(*this);
	}

	const Expr<T> left;
	const Token oper;
	const Expr<T> right;
};

template<typename T>
class Grouping : public Expr<T> {
public:
	Grouping(Expr<T> expression) : expression(expression)	{
	}

	template<typename T>
	T accept(Visitor<T> visitor) {
		return visitor.visitGroupingExpr(*this);
	}

	const Expr<T> expression;
};

template<typename T>
class LiteralExpression : public Expr<T> {
public:
	LiteralExpression(Literal lit, TokenType type) : lit(lit), type(type)	{
	}

	template<typename T>
	T accept(Visitor<T> visitor) {
		std::cout << "visited" << std::endl;	//	this is for debugging to see if it called the right accept
		return visitor.visitLiteralExpressionExpr(*this);
	}

	const Literal lit;
	const TokenType type;
};

template<typename T>
class Unary : public Expr<T> {
public:
	Unary(Token oper, Expr<T> right) : oper(oper), right(right)	{
	}

	template<typename T>
	T accept(Visitor<T> visitor) {
		return visitor.visitUnaryExpr(*this);
	}

	const Token oper;
	const Expr<T> right;
};

