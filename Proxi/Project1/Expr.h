#pragma once
#include "Token.h"
#include <iostream>

template <typename T>
class Binary;
template <typename T>
class Grouping;
template <typename T>
class Literal;
template <typename T>
class Unary;
template <typename T>
class Visitor;

template <typename T>
class Expr {
public:
	virtual T accept(Visitor<T> *visitor) { std::cout << "Called default accept" << std::endl; T temp; return temp; };
	virtual std::string toString() const { std::string temp; return temp; };
};

template <typename T>
class Visitor {
public:
	virtual T visitBinaryExpr(Binary<T> expr) { T temp; return temp; };
	virtual T visitGroupingExpr(Grouping<T> expr) { T temp; return temp; };
	virtual T visitLiteralExpr(Literal<T> expr) { std::cout << "Called default visit" << std::endl; T temp; return temp; };
	virtual T visitUnaryExpr(Unary<T> expr) { T temp; return temp; };
};

template <typename T>
class Binary : public Expr<T> {
public:
	Binary(Expr<T> &left, Token oper, Expr<T> &right) : left(&left), oper(oper), right(&right) { }
	T accept(Visitor<T> *visitor) {
		return visitor->visitBinaryExpr(*this);
	}

	const Expr<T> *left;
	const Token oper;
	const Expr<T> *right;
};

template <typename T>
class Grouping : public Expr<T> {
public:
	Grouping(Expr<T> &expression) : expression(&expression) { }
	T accept(Visitor<T> *visitor) {
		return visitor->visitGroupingExpr(*this);
	}

	const Expr<T> *expression;
};

template <typename T>
class Literal : public Expr<T> {
public:
	Literal(Literal_Token lit) : lit(lit) { };
	T accept(Visitor<T> *visitor) {
		return visitor->visitLiteralExpr(*this);
	}

	const Literal_Token lit;
};

template <typename T>
class Unary : public Expr<T> {
public:
	Unary(Token oper, Expr<T> &right) : oper(oper), right(&right) { }
	T accept(Visitor<T> *visitor) {
		return visitor->visitUnaryExpr(*this);
	}

	const Token oper;
	const Expr<T> *right;
};


