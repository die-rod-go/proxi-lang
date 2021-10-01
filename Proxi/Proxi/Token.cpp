#include "Token.h"

Token::Token(TokenType type, std::string lexeme, Literal lit, int line):
	type(type), lexeme(lexeme), lit(lit), line(line)
{
}

std::string Token::toString()
{
	return "type: " + (int)type + (std::string)"lexeme: " + lexeme + (std::string)"line: " + std::to_string(line);
}
