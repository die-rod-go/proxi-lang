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
	return parenthesize("group", { expr.expression });
}

std::string AstPrinter::visitLiteralExpr(Literal<std::string> expr)
{
	return expr.lit.toString();
}

std::string AstPrinter::visitUnaryExpr(Unary<std::string> expr)
{
	return parenthesize(expr.oper.lexeme, { expr.right });
}

std::string AstPrinter::parenthesize(std::string name, std::vector<Expr<std::string> const*> exprs)
{
	std::string output = "(" + name;
	for (Expr<std::string> const *expr : exprs)
	{
		output += " ";
		output += expr->accept(this);
	}

	output += ")";
	return output;
}

