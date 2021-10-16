#include "AstPrinter.h"

void AstPrinter::test()
{
    
    Binary<std::string> binary(
        Unary<std::string>(Token(MINUS, "-", Literal(true), 1), LiteralExpression<std::string>(Literal(123), INTEGER)),
        Token(STAR, "*", Literal(true), 1),
        Grouping<std::string>(LiteralExpression<std::string>(Literal(45.67f), FLOATING_POINT))
        );
    
    Expr<std::string> *expression = &binary; 
    std::cout << print(expression) << std::endl;
}

std::string AstPrinter::print(Expr<std::string>* expr)
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

std::string AstPrinter::visitLiteralExpressionExpr(LiteralExpression<std::string> expr)
{
    if (expr.lit.isNull)
        return "NOV";
    
    if (expr.type == INTEGER)
        return std::to_string(expr.lit.intLit);
    else if (expr.type == FLOATING_POINT)
        return std::to_string(expr.lit.floatLit);
    else if (expr.type == STRING_LIT)
        return expr.lit.stringLit;
}

std::string AstPrinter::visitUnaryExpr(Unary<std::string> expr)
{
    return parenthesize(expr.oper.lexeme, { expr.right });
}

std::string AstPrinter::parenthesize(std::string name, std::vector<Expr<std::string>*> exprs)
{
    name = "(" + name;
    for (Expr<std::string>* expr : exprs)
    {
        name += " ";
        name += expr->accept(this);
    }

    name += ")";
    return name;    
}
