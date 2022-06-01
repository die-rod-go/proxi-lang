#include "Token.h"

template <typename T>
class Binary;

template <typename T>
class Grouping;

template <typename T>
class LiteralExpression;

template <typename T>
class Unary;

template <typename T>
class Visitor {
public:
		virtual T visitBinaryExpr(Binary<T> expr) { T temp;  return temp; };
		virtual T visitGroupingExpr(Grouping<T> expr) { T temp;  return temp; };
		virtual T visitLiteralExpr(LiteralExpression<T> expr) { T temp;  return temp; };
		virtual T visitUnaryExpr(Unary<T> expr) { T temp;  return temp; };
};

template<typename T>
class Expr {
public:
	virtual T accept(Visitor<T>* visitor) { T temp;  return temp; };
};

template<typename T>
class Binary : public Expr<T> {
public:
	Binary(Expr<T>& left, Token oper, Expr<T>& right) : left(&left), oper(oper), right(&right) { }

	T accept(Visitor<T>* visitor) {
		return visitor->visitBinaryExpr(*this);
	}

	Expr<T> *left;
	Token oper;
	Expr<T> *right;
};

template<typename T>
class Grouping : public Expr<T> {
public:
	Grouping(Expr<T>& expression) : expression(&expression) { }

	T accept(Visitor<T>* visitor) {
		return visitor->visitGroupingExpr(*this);
	}

	Expr<T> *expression;
};

template<typename T>
class LiteralExpression : public Expr<T> {
public:
	LiteralExpression(Literal_Token lit) : lit(lit) { }

	T accept(Visitor<T>* visitor) {
		return visitor->visitLiteralExpressionExpr(*this);
	}

	Literal_Token lit;
};

template<typename T>
class Unary : public Expr<T> {
public:
	Unary(Token oper, Expr<T>& right) : oper(oper), right(&right) { }

	T accept(Visitor<T>* visitor) {
		return visitor->visitUnaryExpr(*this);
	}

	Token oper;
	Expr<T> *right;
};

