#pragma once
#include "Token.h"

class Binary;
class Grouping;
class Literal;
class Unary;
class Visitor;

class Expr {
public:
	virtual Expr accept(Visitor& visitor) { Expr temp; return temp; };
	virtual std::string toString() const { std::string temp; return temp; };
};

class Visitor {
public:
	virtual Expr visitBinaryExpr(Binary &expr) { Expr temp; return temp; };
	virtual Expr visitGroupingExpr(Grouping &expr) { Expr temp; return temp; };
	virtual Expr visitLiteralExpr(Literal &expr) { Expr temp; return temp; };
	virtual Expr visitUnaryExpr(Unary &expr) { Expr temp; return temp; };
};

class Binary : public Expr {
public:
	Binary(Expr &left, Token oper, Expr &right) : left(&left), oper(oper), right(&right) { }

	Expr accept(Visitor &visitor) {
		return visitor.visitBinaryExpr(*this);
	}

	const Expr *left;
	const Token oper;
	const Expr *right;
};

class Grouping : public Expr {
public:
	Grouping(Expr expression) : expression(&expression) { }
	Expr accept(Visitor &visitor) {
		return visitor.visitGroupingExpr(*this);
	}

	const Expr *expression;
};

class Literal : public Expr {
public:
	Literal(Literal_Token lit) : lit(lit) { };
	Expr accept(Visitor &visitor) {
		return visitor.visitLiteralExpr(*this);
	}

	const Literal_Token lit;
};

class Unary : public Expr {
public:
	Unary(Token oper, Expr& expr) : oper(oper), right(&expr) { }
	Expr accept(Visitor& visitor) {
		return visitor.visitUnaryExpr(*this);
	}

	const Token oper;
	const Expr *right;
};


