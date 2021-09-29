#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class Proxi
{
public:
	Proxi();
	static bool hadError;
	static void error(int line, std::string message);
	void runFile(std::string path);
	void runPrompt();

private:

	void run(std::string file);
	static void report(int line, std::string location, std::string message);
	

};

