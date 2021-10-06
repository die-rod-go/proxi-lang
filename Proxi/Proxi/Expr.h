#include "Token.h"

template <typename R>
class Visitor {
		virtual R visitBinaryExpr(Binary expr);
		virtual R visitGroupingExpr(Grouping expr);
		virtual R visitLiteralExpressionExpr(LiteralExpression expr);
		virtual R visitUnaryExpr(Unary expr);
};

class Expr {
template<typename R>
	R accept(R visitor);
};

class Binary : public Expr {
	Binary(Expr left, Token oper, Expr right) : left(left), oper(oper), right(right)	{
	}

	template<typename R>
	R accept(R visitor) {
		return visitor.visitBinaryExpr(this);
	}

	const Expr left;
	const Token oper;
	const Expr right;
};

class Grouping : public Expr {
	Grouping(Expr expression) : expression(expression)	{
	}

	template<typename R>
	R accept(R visitor) {
		return visitor.visitGroupingExpr(this);
	}

	const Expr expression;
};

class LiteralExpression : public Expr {
	LiteralExpression(Literal lit, TokenType type) : lit(lit), type(type)	{
	}

	template<typename R>
	R accept(R visitor) {
		return visitor.visitLiteralExpressionExpr(this);
	}

	const Literal lit;
	const TokenType type;
};

class Unary : public Expr {
	Unary(Token oper, Expr right) : oper(oper), right(right)	{
	}

	template<typename R>
	R accept(R visitor) {
		return visitor.visitUnaryExpr(this);
	}

	const Token oper;
	const Expr right;
};

