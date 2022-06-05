/*
Author: Diego Rodriguez
Code is Heavily inspired by the work of Robert Nystrom on the lox language
In "Crafting Interpreters"
https://craftinginterpreters.com/
*/

#include <iostream>
#include "Proxi.h"
#include "AstPrinter.h"
#include "Expr.h"
#include <unordered_map>

int main(int argc, char* argv[])
{
	Proxi proxi;
	//std::cout << argc << std::endl;

	if (argc == 1)
		std::cout << "Usage: cproxi [script]" << std::endl;
	else if (argc == 2)
	{
		//std::cout << "runFile" << std::endl;
		proxi.runFile(argv[1]);
	}
	else
	{
		std::cout << "runPrompt";
		proxi.runPrompt();
	}
	Literal_Token null;
	Literal_Token num1(45.5f);
	Literal_Token num2(56);

	Token minus(TokenType::MINUS, "-", null, 1);
	Literal<std::string> lit1(num1);
	Unary<std::string> unary(minus, lit1);

	Token star(TokenType::STAR, "*", null, 1);

	Literal<std::string> lit2(num2);
	Grouping<std::string> group(lit2);

	Binary<std::string> binary(unary, star, group);

	AstPrinter printer;
	Expr<std::string> *expr = &binary;
	std::cout << printer.print(expr) << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}