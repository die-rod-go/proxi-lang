#include "AstPrinter.h"

void AstPrinter::test()
{
    LiteralExpression lit(Literal(13), INTEGER);
    Expr *expression = &lit; 
    AstPrinter printer;
    printer.print(*expression);

}

std::string AstPrinter::print(Expr expr)
{
    return expr.accept(*this);
}

std::string AstPrinter::visitBinaryExpr(Binary expr)
{
    std::vector<Expr> exprList;
    exprList.push_back(expr.left);
    exprList.push_back(expr.right);

    return parenthesize(expr.oper.lexeme, exprList);
}

std::string AstPrinter::visitGroupingExpr(Grouping expr)
{
    std::vector<Expr> exprList;
    exprList.push_back(expr.expression);
    return parenthesize("group", exprList);
}

std::string AstPrinter::visitLiteralExpr(Literal expr)
{
    if (expr.isNull)
        return "NOV";
    
    if (expr.type == INTEGER)
        return std::to_string(expr.intLit);
    else if (expr.type == FLOATING_POINT)
        return std::to_string(expr.floatLit);
    else if (expr.type == STRING_LIT)
        return expr.stringLit;
}

std::string AstPrinter::visitUnaryExpr(Unary expr)
{
    std::vector<Expr> exprList;
    exprList.push_back(expr.right);
    return parenthesize(expr.oper.lexeme, exprList);
}

std::string AstPrinter::parenthesize(std::string name, std::vector<Expr> exprVector)
{
    name = "(" + name;
    for (Expr expr : exprVector)
    {
        name += " ";
        name += expr.accept(*this);
    }

    name += ")";
    return name;
}
