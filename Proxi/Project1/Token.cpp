#include "Token.h"

/*
// Single-character tokens.
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// One or two character tokens.
	BANG, BANG_EQUAL,		// ! !=
	EQUAL, EQUAL_EQUAL,		// = ==
	GREATER, GREATER_EQUAL,	// > >=
	LESS, LESS_EQUAL,		// < <=

	// Literals.
	IDENTIFIER, INTEGER, FLOATING_POINT, STRING_LIT,

	// Keywords.
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NOV, OR,
	PRINT, RETURN, SUPER, SELF, THIS, TRUE,
	INT, FLOAT, BOOL, STRING, WHILE,

	END_OF_FILE
*/
Token::Token(TokenType type, std::string lexeme, Literal lit, int line):
	type(type), lexeme(lexeme), lit(&lit), line(line)
{
	emplaceMap();
}

std::string Token::toString()
{
	//return lexeme;
	return "type: " + enumStrings.at(type) + (std::string)"\nlexeme: " + lexeme + (std::string)"\nline: " + std::to_string(line);
}

void Token::emplaceMap()
{
	enumStrings.emplace(TokenType::LEFT_PAREN, "LEFT_PAREN");
	enumStrings.emplace(TokenType::RIGHT_PAREN, "RIGHT_PAREN");
	enumStrings.emplace(TokenType::LEFT_BRACE, "LEFT_BRACE");
	enumStrings.emplace(TokenType::RIGHT_BRACE, "RIGHT_BRACE");
	enumStrings.emplace(TokenType::COMMA, "COMMA");
	enumStrings.emplace(TokenType::DOT, "DOT");
	enumStrings.emplace(TokenType::MINUS, "MINUS");
	enumStrings.emplace(TokenType::PLUS, "PLUS");
	enumStrings.emplace(TokenType::SEMICOLON, "SEMICOLON");
	enumStrings.emplace(TokenType::SLASH, "SLASH");
	enumStrings.emplace(TokenType::STAR, "STAR");

	enumStrings.emplace(TokenType::BANG, "BANG");
	enumStrings.emplace(TokenType::BANG_EQUAL, "BANG_EQUAL"); 
	enumStrings.emplace(TokenType::EQUAL, "EQUAL");
	enumStrings.emplace(TokenType::EQUAL_EQUAL, "EQUAL_EQUAL");
	enumStrings.emplace(TokenType::GREATER, "GREATER");
	enumStrings.emplace(TokenType::GREATER_EQUAL, "GREATER_EQUAL");
	enumStrings.emplace(TokenType::LESS, "LESS");
	enumStrings.emplace(TokenType::LESS_EQUAL, "LESS_EQUAL");

	enumStrings.emplace(TokenType::IDENTIFIER, "IDENTIFIER");
	enumStrings.emplace(TokenType::INTEGER, "INTEGER");
	enumStrings.emplace(TokenType::FLOATING_POINT, "FLOATING_POINT");
	enumStrings.emplace(TokenType::STRING_LIT, "STRING_LIT");

	enumStrings.emplace(TokenType::AND, "AND");
	enumStrings.emplace(TokenType::CLASS, "CLASS");
	enumStrings.emplace(TokenType::ELSE, "ELSE");
	enumStrings.emplace(TokenType::FALSE, "FALSE");
	enumStrings.emplace(TokenType::FUN, "FUN");
	enumStrings.emplace(TokenType::FOR, "FOR");
	enumStrings.emplace(TokenType::IF, "IF");
	enumStrings.emplace(TokenType::NOV, "NOV");
	enumStrings.emplace(TokenType::OR, "OR");
	enumStrings.emplace(TokenType::PRINT, "PRINT");
	enumStrings.emplace(TokenType::RETURN, "RETURN");
	enumStrings.emplace(TokenType::SUPER, "SUPER");
	enumStrings.emplace(TokenType::SELF, "SELF");
	enumStrings.emplace(TokenType::THIS, "THIS");
	enumStrings.emplace(TokenType::TRUE, "TRUE");
	enumStrings.emplace(TokenType::INT, "INT");
	enumStrings.emplace(TokenType::FLOAT, "FLOAT");
	enumStrings.emplace(TokenType::BOOL, "BOOL");
	enumStrings.emplace(TokenType::STRING, "STRING");
	enumStrings.emplace(TokenType::WHILE, "WHILE");

	enumStrings.emplace(TokenType::END_OF_FILE, "END_OF_FILE");
}


