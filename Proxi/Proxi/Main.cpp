/*
Author: Diego Rodriguez
Code is Heavily inspired by the work of Robert Nystrom on the lox language
In "Crafting Interpreters"
https://craftinginterpreters.com/
*/

#include <iostream>
#include "Proxi.h"

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

	//std::cout << "quit" << std::endl;

	return EXIT_SUCCESS;
}