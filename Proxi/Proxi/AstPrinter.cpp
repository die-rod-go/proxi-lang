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
    std::cout << "binary" << std::endl;
    std::vector<Expr<std::string>*> exprList;
    exprList.push_back(&expr.left);
    exprList.push_back(&expr.right);

    return parenthesize(expr.oper.lexeme, exprList);
}

std::string AstPrinter::visitGroupingExpr(Grouping<std::string> expr)
{
    std::cout << "grouping" << std::endl;
    std::vector<Expr<std::string>*> exprList;
    exprList.push_back(&expr.expression);
    return parenthesize("group", exprList);
}

std::string AstPrinter::visitLiteralExpressionExpr(LiteralExpression<std::string> expr)
{
    std::cout << "literal" << std::endl;
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
    std::cout << "unary" << std::endl;
    std::vector<Expr<std::string>*> exprList;
    exprList.push_back(&expr.right);
    return parenthesize(expr.oper.lexeme, exprList);
}

std::string AstPrinter::parenthesize(std::string name, std::vector<Expr<std::string>*> exprVector)
{
    std::cout << "parenthesize" << std::endl;
    name = "(" + name;
    for (Expr<std::string> *expr : exprVector)
    {
        name += " ";
        name += expr->accept(this);
    }

    name += ")";
    return name;
}
