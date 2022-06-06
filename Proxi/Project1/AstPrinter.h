#pragma once
#include "Expr.h"
#include <vector>

class AstPrinter : public Visitor<std::string>
{
public:
	AstPrinter();
	std::string print(Expr<std::string> *expr);
	std::string visitBinaryExpr(Binary <std::string> expr);
	std::string visitGroupingExpr(Grouping<std::string> expr);
	std::string visitLiteralExpr(Literal<std::string> expr);
	std::string visitUnaryExpr(Unary<std::string> expr);

private:
	std::string parenthesize(std::string name, std::vector<Expr<std::string> const*> exprs);

};

