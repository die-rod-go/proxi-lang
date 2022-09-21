#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "AstPrinter.h"

class Proxi
{
public:
	Proxi();
	static bool hadError;
	static void error(int line, std::string message);
	static void error(Token token, std::string message);
	void runFile(std::string path);
	void runPrompt();

private:
	void run(std::string source);
	static void report(int line, std::string location, std::string message);
	

};

