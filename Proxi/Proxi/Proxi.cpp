#include "Proxi.h"

Proxi::Proxi()
{
	hadError = false;
}

void Proxi::error(int line, std::string message)
{
	report(line, "", message);
}

void Proxi::runFile(std::string path)
{
	std::ifstream myFile(path); //	open file
	if (!myFile.is_open())
		std::cout << "Error opening file" << std::endl;

	std::stringstream buffer;	//	convert to string stream
	buffer << myFile.rdbuf();	//	read string stream into string

	myFile.close();

	run(buffer.str());	//	run the file
}

void Proxi::runPrompt()
{
	std::string line;

	while (true)
	{
		std::cin >> line;	//	get input from user
		if (line == "")	
			break;	//	quit if no input
		run(line);	//	run input
	}
}

void Proxi::run(std::string file)
{
}

void Proxi::report(int line, std::string location, std::string message)
{
	std::cout << "[line " + line + std::string("]Error") + location + ": " + message << std::endl;	//	for some weird fucking reason it thinks "" is char so you have to cast it to a string fucking stupid ass
	hadError = true;
}