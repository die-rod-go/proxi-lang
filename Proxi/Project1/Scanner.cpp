#include "Scanner.h"

Scanner::Scanner(std::string source) : source(source), nullLiteral(TokenType::NOV)
{
	this->start = 0;
	this->current = 0;
	this->line = 1;
	this->currentOnLine = 1;

	keywords.emplace("and",		TokenType::AND);
	keywords.emplace("class",	TokenType::CLASS);
	keywords.emplace("else",	TokenType::ELSE);
	keywords.emplace("false",	TokenType::FALSE);
	keywords.emplace("for",		TokenType::FOR);
	keywords.emplace("fun",		TokenType::FUN);
	keywords.emplace("if",		TokenType::IF);
	keywords.emplace("NOV",		TokenType::NOV);
	keywords.emplace("or",		TokenType::OR);
	keywords.emplace("print",	TokenType::PRINT);
	keywords.emplace("return",	TokenType::RETURN);
	keywords.emplace("super",	TokenType::SUPER);
	keywords.emplace("this",	TokenType::THIS);
	keywords.emplace("self",	TokenType::SELF);
	keywords.emplace("true",	TokenType::TRUE);
	keywords.emplace("bool",	TokenType::BOOL);
	keywords.emplace("int",		TokenType::INT);
	keywords.emplace("float",	TokenType::FLOAT);
	keywords.emplace("string",	TokenType::STRING);
	keywords.emplace("while",	TokenType::WHILE);
}
/*AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NOV, OR,
	PRINT, RETURN, SUPER, SELF, THIS, TRUE,
	INT, FLOAT, BOOL, STRING, WHILE,*/

std::vector<Token> Scanner::scanTokens()
{
	while (!isAtEnd())
	{
		//	at the beginning of the next lexeme
		start = current;
		scanToken();
	}

	tokens.push_back(Token(TokenType::END_OF_FILE, "", nullLiteral, line));
	return tokens;
}


bool Scanner::isAtEnd()
{
	//printCurrent();
	return current >= source.length();
}

void Scanner::scanToken()
{
	char c = advance();
	switch (c) {
		case '(': addToken(TokenType::LEFT_PAREN); break;
		case ')': addToken(TokenType::RIGHT_PAREN); break;
		case '{': addToken(TokenType::LEFT_BRACE); break;
		case '}': addToken(TokenType::RIGHT_BRACE); break;
		case ',': addToken(TokenType::COMMA); break;
		case '.': addToken(TokenType::DOT); break;
		case '-': addToken(TokenType::MINUS); break;
		case '+': addToken(TokenType::PLUS); break;
		case ';': addToken(TokenType::SEMICOLON); break;
		case '*': addToken(TokenType::STAR); break;

		case '!': // checks for tokens that could be single or part of double character lexems ex: ! vs != and > and >=
			addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
			break;
		case '=':
			addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
			break;
		case '<':
			addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
			break;
		case '>':
			addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
			break;

		case '/': // checks for comments "//" and consumes the whole line
			if (match('/')) {
				// A comment goes until the end of the line.
				while (peek() != '\n' && !isAtEnd()) 
					advance();
			}
			else {
				addToken(TokenType::SLASH);
			}
			break;

		case ' ':
		case '\r':
		case '\t':
		//	ignore whitespace/meaningless characters
			break;

		case '\n':
			line++;
			currentOnLine = 1;
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
	currentOnLine++;
	return source[current++];
}

void Scanner::addToken(TokenType type)
{
	addToken(type, nullLiteral);
}

void Scanner::addToken(TokenType type, Literal lit)
{
	int length = getLength(start, current);
	std::string text = source.substr(start, length);
	tokens.push_back(Token(type, text, lit, line));
}

bool Scanner::match(char expected)	//	checks if two characters are equal - conditional advance
{
	if (isAtEnd()) 
		return false;
	if (source[current] != expected)
		return false;

	currentOnLine++;
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
		{
			line++;
			currentOnLine = 1;
		}
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
	int length = getLength(start + 1, current - 1);
	std::string value = source.substr(start + 1, length);
	addToken(TokenType::STRING_LIT, Literal(value));
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

	int length = getLength(start, current);
	if (isFloat)
	{
		float value = std::stof(source.substr(start, length));
		addToken(TokenType::FLOAT, Literal(value));
	}
	else
	{
		int value = std::stoi(source.substr(start, length));
		addToken(TokenType::INTEGER, Literal(value));
	}
}

void Scanner::identifier()
{
	while (isalnum(peek()))
		advance();

	int length = getLength(start, current);
	TokenType type;
	std::string text = source.substr(start, length);

	if (keywords.find(text) != keywords.end()) //	if keyword is in map (exists in the language)
		type = keywords.at(text);
	else
		type = TokenType::IDENTIFIER;

	addToken(type);
}

int Scanner::getLength(int start, int current)
{
	return current - start;
}

void Scanner::printCurrent()
{
	std::cout << "current: " << current << std::endl;
	std::cout << "line: " << line << std::endl;
	std::cout << "currentOnLine: " << currentOnLine << std::endl;
	std::cout << std::endl;
}
