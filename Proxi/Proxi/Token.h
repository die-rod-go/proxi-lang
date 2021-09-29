#pragma once
class Token
{
	const TokenType type;

};

enum TokenType {
	// Single-character tokens.
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// One or two character tokens.
	BANG, BANG_EQUAL,		// ! !=
	EQUAL, EQUAL_EQUAL,		// = == 
	GREATER, GREATER_EQUAL,	// > >=
	LESS, LESS_EQUAL,		// < <=

	// Literals.
	IDENTIFIER, INTEGER, FLOAT, BOOLEAN, STRING,

	// Keywords.
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NOV, OR,
	PRINT, RETURN, SUPER, SELF, THIS, TRUE,
	INT, FLOAT, BOOLEAN, STRING, WHILE,

	EOF
};

