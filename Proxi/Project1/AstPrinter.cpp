#include "AstPrinter.h"

AstPrinter::AstPrinter()
{
}

std::string AstPrinter::print(Expr<std::string> *expr)
{
	return expr->accept(this);
}

std::string AstPrinter::visitBinaryExpr(Binary<std::string> expr)
{
	return parenthesize(expr.oper.lexeme, { expr.left, expr.right });
}

std::string AstPrinter::visitGroupingExpr(Grouping<std::string> expr)
{
	return parenthesize("group", { expr.expression, expr.expression });
}

std::string AstPrinter::visitLiteralExpr(Literal<std::string> expr)
{
	return expr.lit.toString();
}

std::string AstPrinter::visitUnaryExpr(Unary<std::string> expr)
{
	return parenthesize(expr.oper.lexeme, { expr.right, expr.right });
}

std::string AstPrinter::parenthesize(std::string name, std::vector<Expr<std::string>*> exprs)
{
	std::string output = "(" + name;
	for (Expr<std::string> *expr : exprs)
	{
		output += " ";
		output += expr->accept(this);
	}

	output += ")";
	return output;
}

