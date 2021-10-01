#include "Scanner.h"

Scanner::Scanner(std::string source) : source(source), nullLiteral(false, -1, -1, "null")
{
	this->start = 0;
	this->current = 0;
	this->line = 1;

	keywords.emplace("and",		AND);
	keywords.emplace("class",	CLASS);
	keywords.emplace("else",	ELSE);
	keywords.emplace("false",	FALSE);
	keywords.emplace("for",		FOR);
	keywords.emplace("fun",		FUN);
	keywords.emplace("if",		IF);
	keywords.emplace("NOV",		NOV);
	keywords.emplace("or",		OR);
	keywords.emplace("print",	PRINT);
	keywords.emplace("return",	RETURN);
	keywords.emplace("super",	SUPER);
	keywords.emplace("this",	THIS);
	keywords.emplace("self",	SELF);
	keywords.emplace("true",	TRUE);
	keywords.emplace("bool",	BOOL);
	keywords.emplace("int",		INT);
	keywords.emplace("float",	FLOAT);
	keywords.emplace("string",	STRING);
	keywords.emplace("while",	WHILE);

}
/*AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NOV, OR,
	PRINT, RETURN, SUPER, SELF, THIS, TRUE,
	INT, FLOAT, BOOL, STRING, WHILE,*/

std::vector<Token> Scanner::scanTokens()
{
	while (!isAtEnd())
	{
		//	at the beginning of the next leceme
		start = current;
		scanToken();
	}

	tokens.push_back(Token(END_OF_FILE, "", nullLiteral, line));
	return tokens;
}


bool Scanner::isAtEnd()
{
	return current >= source.length();
}

void Scanner::scanToken()
{
	char c = advance();
	switch (c) {
		case '(': addToken(LEFT_PAREN); break;
		case ')': addToken(RIGHT_PAREN); break;
		case '{': addToken(LEFT_BRACE); break;
		case '}': addToken(RIGHT_BRACE); break;
		case ',': addToken(COMMA); break;
		case '.': addToken(DOT); break;
		case '-': addToken(MINUS); break;
		case '+': addToken(PLUS); break;
		case ';': addToken(SEMICOLON); break;
		case '*': addToken(STAR); break;

		case '!': // checks for tokens that could be single or part of double character lexems ex: ! vs != and > and >=
			addToken(match('=') ? BANG_EQUAL : BANG);
			break;
		case '=':
			addToken(match('=') ? EQUAL_EQUAL : EQUAL);
			break;
		case '<':
			addToken(match('=') ? LESS_EQUAL : LESS);
			break;
		case '>':
			addToken(match('=') ? GREATER_EQUAL : GREATER);
			break;

		case '/': // checks for comments "//" and consumes the whole line
			if (match('/')) {
				// A comment goes until the end of the line.
				while (peek() != '\n' && !isAtEnd()) 
					advance();
			}
			else {
				addToken(SLASH);
			}
			break;

		case ' ':
		case '\r':
		case '\t':
		//	ignore whitespace/meaningless characters
			break;

		case '\n':
			line++;
			break;

		case '"': string(); break;

		default:
			if (isdigit(c))
				number();
			else if (isalpha(c))
				identifier();
			else
				Proxi::error(line, "Unexpected Character.");
	}
}

char Scanner::advance()
{
	return source[current++];
}

void Scanner::addToken(TokenType type)
{
	addToken(type, nullLiteral);
}

void Scanner::addToken(TokenType type, Literal lit)
{
	std::string text = source.substr(start, current);
	tokens.push_back(Token(type, text, lit, line));
}

bool Scanner::match(char expected)	//	checks if two characters are equal
{
	if (isAtEnd()) 
		return false;
	if (source[current] != expected)
		return false;

	current++;
	return true;
}

char Scanner::peek()
{
	if (isAtEnd())
		return '\0';
	return source[current];
}

char Scanner::peekNext()
{
	if (current + 1 >= source.length())
		return '\0';
	return source[current + 1];
}

void Scanner::string()
{
	while (peek() != '"' && !isAtEnd())
	{
		if (peek() == '\n')
			line++;
		advance();
	}

	if (isAtEnd())
	{
		Proxi::error(line, "Unterminated string");
		return;
	}

	//	The closing "
	advance();

	//	Trim the surrounding quotes
	std::string value = source.substr(start + 1, current - 1);
	addToken(STRING, Literal(false, -1, -1, value));
}

void Scanner::number()
{
	bool isFloat = false;

	while (isdigit(peek()))
		advance();

	if (peek() == '.' && isdigit(peekNext()))
	{
		isFloat = true;
		advance();
		while (isdigit(peek()))
			advance();
	}

	if (isFloat)
	{
		float value = std::stof(source.substr(start, current));
		addToken(FLOAT, Literal(false, -1, value, "null"));			
	}
	else
	{
		int value = std::stoi(source.substr(start, current));
		addToken(FLOAT, Literal(false, value, -1, "null"));
	}
}

void Scanner::identifier()
{
	while (isalnum(peek()))
		advance();

	TokenType type;
	std::string text = source.substr(start, current);

	if (keywords.find(text) != keywords.end()) //	if keyword is in map/exists in the language
		type = keywords.at(text);
	else
		type = IDENTIFIER;

	addToken(type);
}
