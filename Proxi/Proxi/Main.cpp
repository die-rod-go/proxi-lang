#include <iostream>
#include "Proxi.h"

int main(int argc, char* argv[])
{
	Proxi proxi = Proxi();
	std::cout << argc << std::endl;

	if (argc == 1)
		std::cout << "Usage: cproxi [script]" << std::endl;
	else if (argc == 2)
		proxi.runFile(argv[1]);
	else
		proxi.runPrompt();

	return EXIT_SUCCESS;
}