#include "Token.h"
#include <iostream>

class Binary;
class Grouping;
class LiteralExpression;
class Unary;

template <typename R>
class Visitor {
	virtual R visitBinaryExpr(Binary expr) { R temp; return temp; };
	virtual R visitGroupingExpr(Grouping expr) { R temp; return temp; };
	virtual R visitLiteralExpressionExpr(LiteralExpression expr) { R temp; return temp; };
	virtual R visitUnaryExpr(Unary expr) { R temp; return temp; };
};

class Expr {
public:
	template <typename R>
	R accept(Visitor<R> visitor) { R temp; return temp; };
};

class Binary : public Expr {
public:
	Binary(Expr left, Token oper, Expr right) : left(left), oper(oper), right(right)	{
	}

	template<typename T>
	T accept(T visitor) {
		return visitor.visitBinaryExpr(this);
	}

	const Expr left;
	const Token oper;
	const Expr right;
};

class Grouping : public Expr {
public:
	Grouping(Expr expression) : expression(expression)	{
	}

	template<typename T>
	T accept(T visitor) {
		return visitor.visitGroupingExpr(this);
	}

	const Expr expression;
};

class LiteralExpression : public Expr {
public:
	LiteralExpression(Literal lit, TokenType type) : lit(lit), type(type)	{
	}

	template<typename T>
	T accept(T visitor) {
		return visitor.visitLiteralExpressionExpr(this);
	}

	const Literal lit;
	const TokenType type;
};

class Unary : public Expr {
public:
	Unary(Token oper, Expr right) : oper(oper), right(right)	{
	}

	template<typename T>
	T accept(T visitor) {
		return visitor.visitUnaryExpr(this);
	}

	const Token oper;
	const Expr right;
};

