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

	if (argc == 1)
		std::cout << "Usage: cproxi [script]" << std::endl;
	else if (argc == 2)
		proxi.runFile(argv[1]);
	else
		proxi.runPrompt();

	return EXIT_SUCCESS;
}