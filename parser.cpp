/*
	# Lexical and Syntax Analyzer for Wika Programming Language

	Language: C++

	To compile, type in Powershell:
	```
		g++ parse.c
		./a.exe
	```
Group 4
Members:
	Agulto, Marilyn
	Besana, Juan Marco E.
	Enriquez, Kyle Sebastien
	Prado, Clarence
	Saya-ang, Kenth G.

*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

string fileName = "clarence.wika";
string outputFileName = "output_symbol_table.wika";

/*============================= LEXER ========================================================================*/

enum TokenType
{
	DATA_TYPE,
	KEYWORD,
	RESERVED_WORD,
	IDENTIFIER,
	CONSTANT,
	ASSIGN_OP,
	ARITH_OP,
	REL_OP,
	LOG_OP,
	COMMENT,
	DELIMITER,
	SEMICOLON,
	NEWLINE
};

string stringify(TokenType token)
{
	switch (token)
	{
	case DATA_TYPE:
		return "data type";
	case KEYWORD:
		return "keyword";
	case IDENTIFIER:
		return "identifier";
	case CONSTANT:
		return "constant";
	case SEMICOLON:
		return "";
	case ASSIGN_OP:
		return "";
	case ARITH_OP:
		return "";
	case REL_OP:
		return "";
	case LOG_OP:
		return "";
	case DELIMITER:
		return "";
	case NEWLINE:
		return "";
	default:
		return "Identifier";
	}
}

struct Token
{
	TokenType type;
	string value;
	string description;
	int line;
};

unordered_map<string, Token> tokenTypeMap = {
	// Data Type
	{"karakter", {DATA_TYPE, "karakter", "Character Data Type", 0}},
	{"buumbilang", {DATA_TYPE, "buumbilang", "Integer Data Type", 0}},
	{"bahagimbilang", {DATA_TYPE, "bahagimbilang", "Floating Point Data Type", 0}},
	{"bool", {DATA_TYPE, "bool", "Character Data Type", 0}},
	{"string", {DATA_TYPE, "string", "String Data Type", 0}},

	// Keyword
	{"kunin", {KEYWORD, "kunin", "Input Statement", 0}},
	{"tignan", {KEYWORD, "tignan", "Output Statement", 0}},

	// Reserved Word
	{"kung", {RESERVED_WORD, "kung", "Conditional Statement", 0}},
	{"kundi_kung", {RESERVED_WORD, "kundi_kung", "Conditional Statement", 0}},
	{"kundi", {RESERVED_WORD, "kundi", "Conditional Statement", 0}},
	{"hanggang", {KEYWORD, "hanggang", "Repetition Statement", 0}},
	{"habang", {KEYWORD, "habang", "Repetition Statement", 0}},

	// Logical Operator
	{"hindi", {LOG_OP, "hindi", "Logical Operator", 0}},
	{"at", {LOG_OP, "at", "Logical Operator", 0}},
	{"o_kaya", {LOG_OP, "o_kaya", "Logical Operator", 0}},

	// Constant

	{"tama", {CONSTANT, "tama", "Boolean Constant Value", 0}},
	{"mali", {CONSTANT, "mali", "Boolean Constant Value", 0}},
	{"true", {CONSTANT, "true", "Boolean Constant Value", 0}},
	{"false", {CONSTANT, "false", "Boolean Constant Value", 0}},

};

vector<string> errors;

void unrecognizedToken(string token, int index)
{
	cout << "unrecognized token " << token << " on input string index " << index << endl;
}

vector<Token> tokenize(string input)
{
	vector<Token> tokens;
	string tokenValue;
	string tokenDescription;
	int tokenLine;

	int line = 1;
	int col = 1;
	int lineStart;

	for (int i = 0; i < input.size(); i++)
	{
		char c = input[i];

		if (c == '\n')
		{
			tokens.push_back({NEWLINE, "\n", "New Line Character", line});
			line++;
			col = 1;
		}
		else
		{
			col++;
		}
		if (isspace(c))
			continue;
		switch (c)
		{
		case '+':
			tokens.push_back({ARITH_OP, string(1, c), "Addition Symbol", line});
			break;
		case '-':
			tokens.push_back({ARITH_OP, string(1, c), "Subraction Symbol, line", line});
			break;
		case '*':
			tokens.push_back({ARITH_OP, string(1, c), "Multiplication Symbol, line", line});
			break;
		case '%':
			tokens.push_back({ARITH_OP, string(1, c), "Modulus Symbol, line", line});
			break;
		case '/':
			if (input[i + 1] == '/')
			{
				// single line comment
				i += 2;
				tokenValue = "";
				while (input[i] != '\n' && input[i] != EOF)
				{
					tokenValue += input[i];
					i++;
				}
				tokens.push_back({COMMENT, "//", "Single Line Comment start", line});
				tokens.push_back({COMMENT, tokenValue, "Single line comment", line});
			}
			else if (input[i + 1] == '*')
			{
				// single line comment
				i += 2;
				tokenValue = "";
				while (input[i] != '*' && input[i] != '/' && input[i] != EOF)
				{
					tokenValue += input[i];
					i++;
				}
				if (input[i] != '*' && input[i] + 1 != '/')
				{
					// print the error message
					errors.push_back("\u001b[38;5;208m" + fileName + ": error: missing terminating */" + " on line " + to_string(line) + " column " + to_string(col) + "\033[0m\n\t");

					// return the tokens
					return tokens;
				}
				tokens.push_back({COMMENT, "/*", "Multi Line Comment Start", line});
				tokens.push_back({COMMENT, tokenValue, "Multi line comment", line});
				tokens.push_back({COMMENT, "*/", "Multi Line Comment End", line});
			}
			else
			{
				// not a comment, treat as an operator
				tokenValue = input[i];
				tokens.push_back({ARITH_OP, tokenValue, "Division Symbol", line});
			}
			break;
		case '=':
			if (input[i + 1] == '=')
			{
				tokens.push_back({REL_OP, "==", "Relational Operator", line});
				i++;
			}
			else
			{
				tokens.push_back({ASSIGN_OP, string(1, c), "Assignment Operator", line});
			}
			break;
		case '>':
			if (input[i + 1] == '=')
			{
				tokens.push_back({REL_OP, ">=", "Relational Operator", line});
				i++;
			}
			else
			{
				tokens.push_back({REL_OP, string(1, c), "Relational Operator", line});
			}
			break;
		case '<':
			if (input[i + 1] == '=')
			{
				tokens.push_back({REL_OP, "<=", "Relational Operator", line});
				i++;
			}
			else
			{
				tokens.push_back({REL_OP, string(1, c), "Relational Operator", line});
			}
			break;
		case '!':
			if (input[i + 1] == '=')
			{
				tokens.push_back({REL_OP, "!=", "Relational Operator", line});
				i++;
			}
			else
			{
				tokens.push_back({LOG_OP, string(1, c), "Logical Operator", line});
			}
			break;
		case ';':
			tokens.push_back({SEMICOLON, string(1, c), "Semicolon", line});
			break;
		case '\\':
			tokens.push_back({DELIMITER, string(1, c), "Backslash", line});
			break;
		case '(':
			tokens.push_back({DELIMITER, string(1, c), "Left Parenthesis", line});
			break;
		case ')':
			tokens.push_back({DELIMITER, string(1, c), "Right Parenthesis", line});
			break;
		case '[':
			tokens.push_back({DELIMITER, string(1, c), "Left Bracket", line});
			break;
		case ']':
			tokens.push_back({DELIMITER, string(1, c), "Right Bracket", line});
			break;
		case '{':
			tokens.push_back({DELIMITER, string(1, c), "Left Braces", line});
			break;
		case '}':
			tokens.push_back({DELIMITER, string(1, c), "Right Braces", line});
			break;
		case ',':
			tokens.push_back({DELIMITER, string(1, c), "Comma", line});
			break;
		case '.':
			// Check if the character before the '.' is a digit
			if (isdigit(input[i - 1]))
			{
				// If the character before the '.' is a digit, we have a float constant
				// Concatenate the integer and float parts together into a single token value
				tokenValue += input[i];
				// Consume the remaining float digits
				while (isdigit(input[i + 1]))
				{
					tokenValue += input[i + 1];
					i++;
				}
				// Add the float constant token to the list of tokens
				tokens.pop_back();
				tokens.push_back({CONSTANT, tokenValue, "Float Constant Value", line});
				break;
			}
			else
			{
				// If the character before the '.' is not a digit, we have a single '.' token
				// Add the '.' token to the list of tokens

				tokens.push_back({DELIMITER, ".", "Period", line});
				break;
			}
			break;
		case '"':
			tokenValue = "";
			i++;
			while (input[i] != '"' && input[i] != EOF)
			{
				tokenValue += input[i];
				i++;
			}
			if (input[i] != '"')
			{
				// print the error message
				errors.push_back("\u001b[38;5;208m" + fileName + ": error: missing terminating \" character" + " on line " + to_string(line) + " column " + to_string(col) + "\033[0m\n\t");

				// return the tokens
				return tokens;
			}
			tokens.push_back({DELIMITER, "\"", "Delimiter Double Quotation", line});
			tokens.push_back({CONSTANT, tokenValue, "String Constant Value", line});
			tokens.push_back({DELIMITER, "\"", "Delimiter Double Quotation", line});
			break;
		default:
			if (isalpha(c) || c == '_')
			{
				tokenValue = "";
				while (isalpha(input[i]) || (input[i]) == '_' || isdigit(input[i]))
				{
					tokenValue += input[i];
					i++;
				}
				i--;
				TokenType tokenType = IDENTIFIER;

				if (tokenTypeMap.count(tokenValue) > 0)
				{
					tokenType = tokenTypeMap[tokenValue].type;
					tokenDescription = tokenTypeMap[tokenValue].description;
					tokenLine = line;
				}
				else
				{
					tokenDescription = "Identifier " + tokenValue;
				}
				tokens.push_back({tokenType, tokenValue, tokenDescription, line});
			}
			else if (isdigit(c))
			{
				tokenValue = "";
				while (isdigit(input[i]))
				{
					tokenValue += input[i];
					i++;
				}
				i--;
				tokens.push_back({CONSTANT, tokenValue, "Integer Constant Value", line});
			}
			else
			{
				cout << "unrecognized token '" << string(1, c) << "' on line " << line << " column " << col - 1 << endl;
			}
			break;
		}
	}
	return tokens;
}

void printTokens(vector<Token> tokens)
{
	ofstream file(outputFileName);
	if (file.is_open())
	{

		file << endl
			 << "LINE\t\t\t"
			 << "INDEX\t\t\t"
			 << "TOKEN\t\t\t\t"
			 << "TYPE\t\t\t"
			 << "DESCRIPTION\t\t"
			 << endl;
		for (int i = 0; i < tokens.size(); i++)
		{
			file << tokens[i].line
				 << "\t\t\t"; // INDEXF
			file << i
				 << "\t\t\t"; // INDEXF
			file
				<< tokens[i].value
				<< "\t\t\t\t"; // TOKEN
			switch (tokens[i].type)
			{ // TOKEN TYPE
			case DATA_TYPE:
				file << "DATA_TYPE"
					 << "\t\t\t";
				break;
			case KEYWORD:
				file << "KEYWORD"
					 << "\t\t\t";
				break;
			case RESERVED_WORD:
				file << "RESERVED_WORD"
					 << "\t\t";
				break;
			case IDENTIFIER:
				file << "IDENTIFIER"
					 << "\t\t";
				break;
			case CONSTANT:
				file << "CONSTANT"
					 << "\t\t";
				break;
			case ASSIGN_OP:
				file << "ASSIGN_OP"
					 << "\t\t\t";
				break;
			case ARITH_OP:
				file << "ARITH_OP"
					 << "\t\t\t\t";
				break;
			case REL_OP:
				file << "REL_OP"
					 << "\t\t\t";
				break;
			case LOG_OP:
				file << "LOG_OP"
					 << "\t\t\t";
				break;
			case SEMICOLON:
				file << "SEMICOLON"
					 << "\t\t\t\t";
				break;
			case COMMENT:
				file << "COMMENT"
					 << "\t\t\t\t";
				break;
			case DELIMITER:
				file << "DELIMITER"
					 << "\t\t\t\t";
				break;
			}
			file << "" << tokens[i].description << endl; // TOKEN DESCRIPTION
		}
	}
	cout << ">> Generating output symbol table..." << endl
		 << endl;
	cout << ">> Output file generated: " << outputFileName << endl
		 << endl;
	file.close();
}

/*============================ PARSER =======================================================================*/

struct Statement
{
	int line;
	string syntax;
	bool validity;
	string message;
};

string but_got(Token token)
{
	string but_got = "but got " + stringify(token.type) + " '" + token.value + "'"; // + " \e[3m\u001b[31;1m" + token.value + "\e[0m\u001b[0m"
	return but_got;
}

void parse_rest(vector<Token> *tokens, Statement *currentStatement, int *j)
{
	int k = *j;
	Token currentToken = (*tokens)[k];
	while (k < (*tokens).size())
	{
		if (currentToken.value != "\n" && !((*currentStatement).validity))
		{
			// tokens that does not need space
			if (currentToken.type == SEMICOLON ||
				currentToken.type == CONSTANT ||
				currentToken.type == DELIMITER ||
				currentToken.type == ARITH_OP ||
				currentToken.type == REL_OP ||
				currentToken.type == LOG_OP)
			{
				(*currentStatement).syntax += currentToken.value;
			}
			else
			{
				(*currentStatement).syntax += " " + currentToken.value;
			}
			k++;
			currentToken = (*tokens)[k];
		}
		else
		{
			break;
		}
	}
}

Statement parseDeclaration(vector<Token> *tokens, int *i)
{
	int j = *i;
	Token currentToken = (*tokens)[j];

	Statement declaration;
	declaration.line = currentToken.line;
	declaration.syntax = "";
	declaration.validity = true;
	declaration.message = "";

	// Check for the presence of data type
	if (currentToken.type == DATA_TYPE)
	{
		declaration.syntax += currentToken.value;
		j++;
		currentToken = (*tokens)[j];

		// Check for the presence of identifier
		if (currentToken.type == IDENTIFIER)
		{
			declaration.syntax += " " + currentToken.value;
			j++;
			currentToken = (*tokens)[j];
			// Check for the presence of = sign and expression
			if (currentToken.value == "=")
			{
				declaration.syntax += " " + currentToken.value;
				j++;
				currentToken = (*tokens)[j];

				if (currentToken.type == CONSTANT)
				{
					declaration.syntax += " " + currentToken.value;
					j++;
					currentToken = (*tokens)[j];
				}
				else
				{
					declaration.validity = false;
					declaration.message = "Expected constant " + but_got(currentToken);
				}
				// Statement expression = parseExpression(tokens, j);

				// if (!expression.validity)
				// {
				// 	declaration.validity = false;
				// 	declaration.message = "Expected expression";
				// 	return declaration;
				// }
				// else
				// {
				// 	declaration.syntax += " = " + expression.syntax;
				// }
			}

			// Check for the presence of ;
			if (currentToken.value == ";")
			{
				declaration.syntax += currentToken.value;
			}
			else
			{
				declaration.validity = false;
				declaration.message = "Expected ; " + but_got(currentToken);
			}
		}
		else
		{
			declaration.validity = false;
			declaration.message = "Expected identifier " + but_got(currentToken);
		}
	}
	else
	{
		declaration.validity = false;
		declaration.message = "Expected data type " + but_got(currentToken);
	}

	parse_rest(tokens, &declaration, &j);

	*i = j;
	return declaration;
}

// Statement parseExpression(vector<Token> *tokens, int i)
// {
// 	// ...
// }

// Statement parseCompoundStatement(vector<Token> *tokens, int i)
// {
// 	// ...
// }

// Statement parseIf(vector<Token> *tokens, int i)
// {
// 	// ...
// }

// Statement parseFor(vector<Token> *tokens, int i)
// {
// 	// ...
// }

// Statement parseWhile(vector<Token> *tokens, int i)
// {
// 	// ...
// }

// Statement parseDoWhile(vector<Token> *tokens, int i)
// {
// 	// ...
// }

Statement parseStatement(vector<Token> *tokens, int *i)
{
	Statement statement;

	// Get the current token
	Token currentToken = (*tokens)[*i];

	switch (currentToken.type)
	{
	case DATA_TYPE:
		statement = parseDeclaration(tokens, i);
		break;
	// case IDENTIFIER:
	// 	statement = parseExpression(tokens, i);
	// 	break;
	// case DELIMITER:
	// 	if (currentToken.value == "{")
	// 	{
	// 		statement = parseCompoundStatement(tokens, i);
	// 	}
	// 	break;
	// case KEYWORD:
	// 	if (currentToken.value == "if")
	// 	{
	// 		statement = parseIf(tokens, i);
	// 	}
	// 	else if (currentToken.value == "for")
	// 	{
	// 		statement = parseFor(tokens, i);
	// 	}
	// 	else if (currentToken.value == "while")
	// 	{
	// 		statement = parseWhile(tokens, i);
	// 	}
	// 	else if (currentToken.value == "do")
	// 	{
	// 		statement = parseDoWhile(tokens, i);
	// 	}
	// 	break;
	default:
		int j = *i;
		Statement invalidStatement;
		while (j < (*tokens).size())
		{
			if (currentToken.value != "\n")
			{
				if (currentToken.type == SEMICOLON ||
					currentToken.type == CONSTANT ||
					currentToken.type == DELIMITER ||
					currentToken.type == ARITH_OP ||
					currentToken.type == REL_OP ||
					currentToken.type == LOG_OP)
				{
					invalidStatement.syntax += currentToken.value;
				}
				else
				{
					invalidStatement.syntax += currentToken.value + " ";
				}
				j++;
				currentToken = (*tokens)[j];
			}
			else
			{
				statement.line = currentToken.line;
				statement.syntax = invalidStatement.syntax;
				statement.validity = false;
				statement.message = "Unexpected token";
				*i = j;
				break;
			}
		}
		break;
	}

	return statement;
}

vector<Statement> parse(vector<Token> *tokens)
{
	vector<Statement> statements;

	// Loop through the whole token vector
	for (int i = 0; i < (*tokens).size(); i++)
	{
		Token currentToken = (*tokens)[i];

		if (currentToken.value == "\n")
		{
			continue;
		}
		Statement statement = parseStatement(tokens, &i);
		statements.push_back(statement);
	}

	return statements;
}

void printSyntax(vector<Statement> statements)
{
	cout << endl
		 << "LINE\t"
		 << "SYNTAX\t\t\t\t\t"
		 << "VALIDITY\t\t\t"
		 << "MESSAGE\t\t"
		 << endl;
	for (int i = 0; i < statements.size(); i++)
	{
		Statement statement = statements[i];

		cout << statement.line << "\t";
		cout << statement.syntax << "\t\t\t\t\t";
		if (statement.validity)
		{
			cout << "Valid";
		}
		else
		{
			cout << "Invalid";
		}
		cout << "\t\t\t";
		cout << statement.message << endl;
	}
}

int main()
{

	string input = "";
	ifstream file(fileName);

	size_t found = fileName.rfind(".wika");

	cout << endl
		 << endl
		 << ">> Tokenizing "
		 << fileName << "..."
		 << endl
		 << endl;

	if (found == string::npos && found != fileName.size() - 5)
	{
		cout << fileName << endl;
		// '.wika' was not found in the file name, so we cannot accept the input
		cout << "Only .wika files are accepted" << endl;
	}
	else
	{
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				input += line + '\n';
			}
			file.close();
			vector<Token> tokens = tokenize(input);
			printTokens(tokens);
			vector<Statement> statements = parse(&tokens);
			printSyntax(statements);
		}
		else
		{
			cout << "Error: file " << fileName << " not found." << endl;
		}
	}

	return 0;
}

void func()
{
// 	if (statement.type == "ASSIGNMENT")
// 	{
// 		Variable var;
// 		var.type;
// 		var.name;
// 		var.initialized;

// 		for (int i = 0; i < statement.tokens.size(); i++) // Read each tokens of each statement
// 		{
// 			Token currentToken = (statement.tokens)[i];

// 			if (currentToken.type == IDENTIFIER)
// 			{
// 				var.name = currentToken.value;

// 				if (symbol_table.count(var.name) == 0)
// 				{
// 					statement.validity = false;
// 					cout << "Line " << statement.line << " : identifier/variable '" << var.name << "' not declared" << endl;
// 					statement.message = "undeclared variable '" + var.name + "'";
// 					break;
// 				}
// 				else if (symbol_table.count(currentToken.value) > 0)
// 				{
// 					Variable variable = symbol_table[currentToken.value];
// 					if (!variable.initialized)
// 					{
// 						cout << "Line " << statement.line << " : variable '" << currentToken.value << "' not initialized" << endl;
// 						statement.message = "uninitialized variable '" + currentToken.value + "'";
// 					}
// 				}
// 			}
// 		}
// 	}
}