#pragma once
#include "Expr.h"
#include <string>
#include <vector>

class AstPrinter : public Visitor<std::string>
{
public:

	std::string print(Expr expr);

	std::string visitBinaryExpr(Binary expr);
	std::string visitGroupingExpr(Grouping expr);
	std::string visitLiteralExpr(Literal expr);
	std::string visitUnaryExpr(Unary expr);

	std::string parenthesize(std::string name, std::vector<Expr> exprVector);
};

