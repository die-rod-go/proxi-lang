#include "AstPrinter.h"
#include <iostream>

void AstPrinter::test()
{
    
    LiteralExpression<std::string> lit(Literal(123));    
    Unary<std::string> unary(Token(MINUS, "-", Literal(true), 1), lit); 
    Grouping<std::string> grouping(lit); 

    Binary<std::string> binary(
        unary,
        Token(STAR, "*", Literal(true), 1),
        grouping
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
    if (expr.lit.type == NOV)
        return "NOV";
    
    if (expr.lit.type == INTEGER)
        return std::to_string(expr.lit.intLit);
    else if (expr.lit.type == FLOATING_POINT)
        return std::to_string(expr.lit.floatLit);
    else if (expr.lit.type == STRING_LIT)
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
