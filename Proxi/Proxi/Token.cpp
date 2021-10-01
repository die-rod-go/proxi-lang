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
	IDENTIFIER, INTEGER, FLOATING_POINT, BOOLEAN, STRING_LIT,

	// Keywords.
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NOV, OR,
	PRINT, RETURN, SUPER, SELF, THIS, TRUE,
	INT, FLOAT, BOOL, STRING, WHILE,

	END_OF_FILE
*/
Token::Token(TokenType type, std::string lexeme, Literal lit, int line):
	type(type), lexeme(lexeme), lit(lit), line(line)
{
	enumStrings.emplace(LEFT_PAREN,		"LEFT_PAREN");
	enumStrings.emplace(RIGHT_PAREN,	"RIGHT_PAREN");
	enumStrings.emplace(LEFT_BRACE,		"LEFT_BRACE");
	enumStrings.emplace(RIGHT_BRACE,	"RIGHT_BRACE");
	enumStrings.emplace(COMMA,			"COMMA");
	enumStrings.emplace(DOT,			"DOT");
	enumStrings.emplace(MINUS,			"MINUS");
	enumStrings.emplace(PLUS,			"PLUS");
	enumStrings.emplace(SEMICOLON,		"SEMICOLON");
	enumStrings.emplace(SLASH,			"SLASH");
	enumStrings.emplace(STAR,			"STAR");

	enumStrings.emplace(BANG,			"BANG");
	enumStrings.emplace(BANG_EQUAL,		"BANG_EQUAL");
	enumStrings.emplace(EQUAL,			"EQUAL");
	enumStrings.emplace(EQUAL_EQUAL,	"EQUAL_EQUAL");
	enumStrings.emplace(GREATER,		"GREATER");
	enumStrings.emplace(GREATER_EQUAL,	"GREATER_EQUAL");
	enumStrings.emplace(LESS,			"LESS");
	enumStrings.emplace(LESS_EQUAL,		"LESS_EQUAL");

	enumStrings.emplace(IDENTIFIER,		"IDENTIFIER");
	enumStrings.emplace(INTEGER,		"INTEGER");
	enumStrings.emplace(FLOATING_POINT,	"FLOATING_POINT");
	enumStrings.emplace(BOOLEAN,		"BOOLEAN");
	enumStrings.emplace(STRING_LIT,		"STRING_LIT");

	enumStrings.emplace(AND,			"AND");
	enumStrings.emplace(CLASS,			"CLASS");
	enumStrings.emplace(ELSE,			"ELSE");
	enumStrings.emplace(FALSE,			"FALSE");
	enumStrings.emplace(FUN,			"FUN");
	enumStrings.emplace(FOR,			"FOR");
	enumStrings.emplace(IF,				"IF");
	enumStrings.emplace(NOV,			"NOV");
	enumStrings.emplace(OR,				"OR");
	enumStrings.emplace(PRINT,			"PRINT");
	enumStrings.emplace(RETURN,			"RETURN");
	enumStrings.emplace(SUPER,			"SUPER");
	enumStrings.emplace(SELF,			"SELF");
	enumStrings.emplace(THIS,			"THIS");
	enumStrings.emplace(TRUE,			"TRUE");
	enumStrings.emplace(INT,			"INT");
	enumStrings.emplace(FLOAT,			"FLOAT");
	enumStrings.emplace(BOOL,			"BOOL");
	enumStrings.emplace(STRING,			"STRING");
	enumStrings.emplace(WHILE,			"WHILE");

	enumStrings.emplace(END_OF_FILE,	"END_OF_FILE");
	
}

std::string Token::toString()
{
	//return lexeme;
	return "type: " + enumStrings.at(type) + (std::string)"\nlexeme: " + lexeme + (std::string)"\nline: " + std::to_string(line);
	//return (std::string)"\nlexeme: " + lexeme + (std::string)"\nline: " + std::to_string(line);
}
