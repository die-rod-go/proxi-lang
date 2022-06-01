/*
Author: Diego Rodriguez
Code is Heavily inspired by the work of Robert Nystrom on the lox language
In "Crafting Interpreters"
https://craftinginterpreters.com/
*/

#include <iostream>
#include "Proxi.h"
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

	Literal_Token six(6);
	Literal_Token five(5);
	Literal lit1(six);
	Literal lit2(five);
	Token oper(TokenType::PLUS, "+", Literal_Token(), 1);

	Binary binary(lit1, oper, lit2);
	std::cout << binary.toString() << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}