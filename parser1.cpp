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
#include <unordered_set>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

string fileName = "clarence.wika";
string outputFileLexer = "output_Lexer.wika";
string outputFileParser = "output_Parser.wika";

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
	{"bool", {DATA_TYPE, "bool", "Boolean Data Type", 0}},
	{"string", {DATA_TYPE, "string", "String Data Type", 0}},
	{"char", {DATA_TYPE, "char", "Character Data Type", 0}},
	{"int", {DATA_TYPE, "int", "Integer Data Type", 0}},
	{"float", {DATA_TYPE, "float", "Floating Point Data Type", 0}},
	{"bool", {DATA_TYPE, "bool", "Boolean Data Type", 0}},
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
					cout << "tokenvalue: " << tokenValue << endl;
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
				i++;
				break;
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
	ofstream file(outputFileLexer);
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
				file << "dataType"
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
	cout << ">> Output file generated: " << outputFileLexer << endl
		 << endl;
	file.close();
}

/*============================ PARSER =======================================================================*/

struct Statement
{
	int line;
	string syntax;
	vector<Token> tokens;
	bool validity;
	string message;
	string type;
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

Statement parseFactor(vector<Token> *tokens, int *i)
{
	int j = *i;

	Token currentToken = (*tokens)[j];

	Statement factor;
	factor.line = currentToken.line;
	factor.syntax = "";
	factor.validity = true;
	factor.message = "";
	factor.tokens;

	if (currentToken.type == CONSTANT || currentToken.type == IDENTIFIER)
	{
		factor.syntax += " " + currentToken.value;
		factor.tokens.push_back(currentToken);
		j++;
		currentToken = (*tokens)[j];
	}
	else if (currentToken.value == "\"") // a string
	{
		factor.syntax += " " + currentToken.value;
		factor.tokens.push_back(currentToken);
		j++;
		currentToken = (*tokens)[j];
		if (currentToken.type == CONSTANT)
		{
			factor.syntax += " " + currentToken.value;
			factor.tokens.push_back(currentToken);
			j++;
			currentToken = (*tokens)[j];

			if (currentToken.value == "\"")
			{
				factor.syntax += " " + currentToken.value;
				factor.tokens.push_back(currentToken);
			}
			else
			{
				factor.validity = false;
				factor.message = "Expected \"";
			}
		}
		else
		{
			factor.validity = false;
			factor.message = "Expected a string";
		}
	}
	else
	{
		factor.validity = false;
		factor.message = "Expected a factor";
	}

	parse_rest(tokens, &factor, &j);
	*i = j;
	return factor;
}

Statement parseTerm(vector<Token> *tokens, int *i)
{
	int j = *i;

	Token currentToken = (*tokens)[j];

	Statement term;
	term.line = currentToken.line;
	term.syntax = "";
	term.validity = true;
	term.message = "";
	term.tokens;

	if (currentToken.type == CONSTANT || currentToken.type == IDENTIFIER || currentToken.value == "\"")
	{

		Statement factor = parseFactor(tokens, &j);

		if (factor.validity)
		{
			term.syntax += " " + factor.syntax;
			term.tokens.insert(term.tokens.end(), factor.tokens.begin(), factor.tokens.end());
			if (currentToken.value == "\"")
			{
				j++;
				currentToken = (*tokens)[j];
			}
			currentToken = (*tokens)[j];

			if (currentToken.value == "*" || currentToken.value == "/")
			{
				term.syntax += " " + currentToken.value;
				term.tokens.push_back(currentToken);
				j++;
				currentToken = (*tokens)[j];

				Statement term2 = parseTerm(tokens, &j);

				if (term2.validity)
				{
					term.syntax += term2.syntax;
					term.tokens.insert(term.tokens.end(), term2.tokens.begin(), term2.tokens.end());
				}
				else
				{
					term.validity = false;
					term.message = "Expected a term";
				}
			}
			else if (currentToken.value == ";" || currentToken.value == ",")
			{
			}
			else
			{
				*i = j;
				return term;
			}
		}
		else
		{
			term.validity = false;
			term.message = "Expected a term";
		}
	}
	else
	{
		term.validity = false;
		term.message = "Expected a term";
	}

	parse_rest(tokens, &term, &j);
	*i = j;
	return term;
}

Statement parseExpression(vector<Token> *tokens, int *i)
{

	int j = *i;

	Token currentToken = (*tokens)[j];

	Statement expression;
	expression.line = currentToken.line;
	expression.syntax = "";
	expression.validity = true;
	expression.message = "";
	expression.tokens;

	if ((currentToken.type == CONSTANT || currentToken.type == IDENTIFIER || currentToken.value == "\""))
	{

		Statement term = parseTerm(tokens, &j);

		if (term.validity)
		{
			expression.syntax += " " + term.syntax;
			expression.tokens.insert(expression.tokens.end(), term.tokens.begin(), term.tokens.end());

			currentToken = (*tokens)[j];

			if (currentToken.value == "+" || currentToken.value == "-")
			{
				expression.syntax += " " + currentToken.value;
				expression.tokens.push_back(currentToken);
				j++;
				currentToken = (*tokens)[j];
				Statement expression2 = parseExpression(tokens, &j);
				if (expression.validity)
				{
					expression.syntax += expression2.syntax;
					expression.tokens.insert(expression.tokens.end(), expression2.tokens.begin(), expression2.tokens.end());
				}
				else
				{
					*i = j;
					return expression;
				}
			}
			else if (currentToken.value == ";" || currentToken.value == ",")
			{
			}
			else
			{
				expression.validity = false;
				expression.message = "Expected operator or ;";
			}
		}
		else if (currentToken.value == ";" || currentToken.value == ",")
		{
		}
		else
		{
			expression.validity = false;
			expression.message = "Expected expression " + but_got(currentToken);
		}
	}
	else if (currentToken.value == ";")
	{
	}
	else if ((currentToken.type == CONSTANT || currentToken.type == IDENTIFIER) && (*tokens)[j + 1].value != ";")
	{
		expression.syntax += " " + currentToken.value;
		expression.tokens.push_back(currentToken);
		j++;
		currentToken = (*tokens)[j];
		Statement term = parseTerm(tokens, &j);
		if (term.validity)
		{
			expression.syntax += term.syntax;
			expression.tokens.insert(expression.tokens.end(), term.tokens.begin(), term.tokens.end());
		}
		else
		{
			expression.validity = false;
			expression.message = "Expected constant or variable" + but_got(currentToken);
		}
	}
	else
	{
		expression.validity = false;
		expression.message = "Expected expression" + but_got(currentToken);
	}

	parse_rest(tokens, &expression, &j);
	*i = j;
	return expression;
}

Statement parseOutput(vector<Token> *tokens, int *i)
{
	int j = *i;

	Token currentToken = (*tokens)[j];

	Statement output;
	output.line = currentToken.line;
	output.syntax = "";
	output.tokens;
	output.validity = true;
	output.message = "";

	if (currentToken.type == KEYWORD && currentToken.value == "tignan")
	{
		output.syntax += " " + currentToken.value;
		output.tokens.push_back(currentToken);
		j++;
		currentToken = (*tokens)[j];

		if (currentToken.value == "(")
		{
			output.syntax += " " + currentToken.value;
			output.tokens.push_back(currentToken);
			j++;
			currentToken = (*tokens)[j];

			if (currentToken.type == IDENTIFIER) // check if variable
			{
				output.syntax += " " + currentToken.value;
				output.tokens.push_back(currentToken);
				j++;
				currentToken = (*tokens)[j];

				if (currentToken.value == ")")
				{
					output.syntax += " " + currentToken.value;
					output.tokens.push_back(currentToken);
					j++;
					currentToken = (*tokens)[j];

					if (currentToken.value == ";")
					{
						output.syntax += " " + currentToken.value;
						output.tokens.push_back(currentToken);
					}
					else
					{
						output.validity = false;
						output.message = "Expected ; ";
					}
				}
			}
			else if (currentToken.value == "\"") // check if string data type
			{
				output.syntax += "" + currentToken.value;
				output.tokens.push_back(currentToken);
				j++;
				currentToken = (*tokens)[j];

				if (currentToken.type == CONSTANT)
				{
					output.syntax += "" + currentToken.value;
					output.tokens.push_back(currentToken);
					j++;
					currentToken = (*tokens)[j];

					if (currentToken.value == "\"")
					{
						output.syntax += "" + currentToken.value;
						output.tokens.push_back(currentToken);
						j++;
						currentToken = (*tokens)[j];
						if (currentToken.value == ")")
						{
							output.syntax += "" + currentToken.value;
							output.tokens.push_back(currentToken);
							j++;
							currentToken = (*tokens)[j];

							if (currentToken.value == ";")
							{
								output.syntax += " " + currentToken.value;
								output.tokens.push_back(currentToken);
							}
							else
							{
								output.validity = false;
								output.message = "Expected ; ";
							}
						}
					}
				}
			}
			else
			{
				output.validity = false;
				output.message = "Expected string ";
			}
		}
		else
		{
			output.validity = false;
			output.message = "Expected '(' ";
		}
	}
	else
	{
		output.validity = false;
		output.message = "Expected keyword 'tignan' ";
	}

	*i = j;
	return output;
}

Statement parseVariables(vector<Token> *tokens, int *i)
{
	int j = *i;

	Token currentToken = (*tokens)[j];

	Statement variables;
	variables.line = currentToken.line;
	variables.syntax = "";
	variables.validity = true;
	variables.message = "";
	variables.tokens;

	if (currentToken.type == IDENTIFIER)
	{
		variables.syntax += " " + currentToken.value;
		variables.tokens.push_back(currentToken);
		j++;
		currentToken = (*tokens)[j];

		if (currentToken.value == "=")
		{
			variables.syntax += " " + currentToken.value;
			variables.tokens.push_back(currentToken);
			j++;
			currentToken = (*tokens)[j];

			Statement expression = parseExpression(tokens, &j);
			if (expression.validity)
			{
				variables.syntax += expression.syntax;
				variables.tokens.insert(variables.tokens.end(), expression.tokens.begin(), expression.tokens.end());
				currentToken = (*tokens)[j];

				if (currentToken.value == ",")
				{
					variables.syntax += "" + currentToken.value;
					j++;
					Statement variables2 = parseVariables(tokens, &j);

					if (variables2.validity)
					{
						variables.syntax += variables2.syntax;
						variables.tokens.push_back(currentToken);
						variables.tokens.insert(variables.tokens.end(), variables2.tokens.begin(), variables2.tokens.end());
					}
					else
					{
						variables.validity = false;
						variables.message = variables.message;
					}
				}
			}
			else
			{
				variables.validity = false;
				variables.message = expression.message;
			}
		}
		else if (currentToken.value == ",")
		{

			variables.syntax += currentToken.value;
			variables.tokens.push_back(currentToken);
			j++;

			Statement variables2 = parseVariables(tokens, &j);
			if (variables.validity)
			{
				variables.syntax += variables2.syntax;
				variables.tokens.insert(variables.tokens.end(), variables2.tokens.begin(), variables2.tokens.end());
			}
			else
			{
				variables.validity = false;
				variables.message = variables.message;
			}
		}
		else
		{
			*i = j;
			return variables;
		}
	}
	else
	{
		variables.validity = false;
		variables.message = "Expected identifier ";
	}

	*i = j;
	parse_rest(tokens, &variables, &j);
	return variables;
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
	declaration.tokens;

	// Check for the presence of data type
	if (currentToken.type == DATA_TYPE)
	{
		declaration.syntax += currentToken.value;
		declaration.tokens.push_back(currentToken);
		j++;
		currentToken = (*tokens)[j];

		Statement ident_list = parseVariables(tokens, &j);

		// code
		if (ident_list.validity)
		{

			declaration.syntax += ident_list.syntax;
			declaration.tokens.insert(declaration.tokens.end(), ident_list.tokens.begin(), ident_list.tokens.end());
			currentToken = (*tokens)[j];

			// Check for the presence of ;
			if (currentToken.value == ";")
			{
				declaration.syntax += currentToken.value;
				declaration.tokens.push_back(currentToken);
				// End of declaration syntax so no need to increment
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
			declaration.message = ident_list.message;
		}
	}
	else
	{
		declaration.validity = false;
		declaration.message = "Expected data type " + but_got(currentToken);
	}

	parse_rest(tokens, &declaration, &j);
	*i = j;

	declaration.type = "DECLARATION";
	return declaration;
}

Statement parseAssignment(vector<Token> *tokens, int *i)
{

	int j = *i;

	Token currentToken = (*tokens)[j];

	Statement assignment;
	assignment.line = currentToken.line;
	assignment.validity = true;
	assignment.message = "";

	// <assignment> ::= <IDENTIFIER><ASSIGN_OP><EXPRESSION>

	if (currentToken.type == IDENTIFIER)
	{
		assignment.syntax += currentToken.value;
		assignment.tokens.push_back(currentToken);
		j++;
		currentToken = (*tokens)[j];

		if (currentToken.type == ASSIGN_OP)
		{
			assignment.syntax += " " + currentToken.value;
			assignment.tokens.push_back(currentToken);
			j++;
			currentToken = (*tokens)[j];
			Statement expression = parseExpression(tokens, &j);
			if (expression.validity)
			{
				assignment.syntax += " " + expression.syntax;
				assignment.tokens.insert(assignment.tokens.end(), expression.tokens.begin(), expression.tokens.end());
				currentToken = (*tokens)[j];

				if (currentToken.value == ";")
				{
					assignment.syntax += "" + currentToken.value;
					assignment.tokens.push_back(currentToken);
				}
				else
				{
					assignment.validity = false;
					assignment.message = "Expected ;";
				}
			}
			else
			{
				assignment.validity = false;
				assignment.message = "Expected constant/expression";
			}
		}
		else
		{
			assignment.validity = false;
			assignment.message = "Expected assignment operator";
		}
	}
	else
	{
		assignment.validity = false;
		assignment.message = "Expected identifier";
	}

	assignment.type = "ASSIGNMENT";
	*i = j;
	return assignment;
}

Statement parseStatement(vector<Token> *tokens, int *i)
{
	Statement statement;

	// Get the current token
	Token currentToken = (*tokens)[*i];
	Token nextToken = (*tokens)[*i + 1];

	// Choose the appropriate subparser based on first token of the line
	switch (currentToken.type)
	{
	case SEMICOLON:
		statement.line = currentToken.line;
		statement.syntax = currentToken.value;
		statement.validity = true;
		statement.message = "";
		break;
	case DATA_TYPE:
		statement = parseDeclaration(tokens, i);
		break;
	case IDENTIFIER:
		statement = parseAssignment(tokens, i);
		break;
	case CONSTANT:
		statement = parseExpression(tokens, i);
		if (statement.validity)
		{
			currentToken = (*tokens)[*i];

			if (currentToken.type == SEMICOLON)
			{
				statement.syntax += currentToken.value;
			}
			else
			{
				statement.validity = false;
				statement.message = "Expected ; " + but_got(currentToken);
			}
		}
		else
		{
			statement.validity = false;
			statement.message = statement.message;
		}
		break;
	case COMMENT:
		statement.line = currentToken.line;
		statement.syntax = currentToken.value;
		statement.validity = true;
		statement.message = "";
		break;
	// case DELIMITER:
	// 	if (currentToken.value == "{")
	// 	{
	// 		statement = parseCompoundStatement(tokens, i);
	// 	}
	// 	break;
	case KEYWORD:
		if (currentToken.value == "tignan")
		{
			statement = parseOutput(tokens, i);
		}
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
		break;
	default:
		int j = *i;
		Statement invalidStatement;
		while (j < (*tokens).size())
		{
			// read the rest of the line until newline is encountered
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

void testStatementTokens(vector<Statement> statements)
{
	cout << "\n\n\nTEST STATEMENT TOKEN\n\n\n";

	cout << endl
		 << "LINE\t"
		 << "TOKENS\t\t\t\t\t"
		 //   << "VALIDITY\t\t\t"
		 //   << "MESSAGE\t\t"
		 << "TYPE\t\t"
		 << endl;
	for (int i = 0; i < statements.size(); i++)
	{
		Statement statement = statements[i];

		cout << statement.line << "\t";

		for (int i = 0; i < statement.tokens.size(); i++)
		{
			cout << statement.tokens[i].value << " ";
		}
		// if (statement.validity)
		// {
		// 	cout << "Valid";
		// }
		// else
		// {
		// 	cout << "Invalid";
		// }
		// cout << "\t\t\t";
		// cout << statement.message;
		cout << statement.type;
		cout << endl;
	}

	ofstream file(outputFileParser);
	if (file.is_open())
	{

		file << endl
			 << "LINE\t\t\t"
			 << "INDEX\t\t\t"
			 << "TOKENS\t\t\t\t"
			 << "MESSAGE\t\t\t"
			 << endl;
		for (int i = 0; i < statements.size(); i++)
		{
			Statement statement = statements[i];

			file << statement.line << "\t";

			for (int i = 0; i < statement.tokens.size(); i++)
			{
				file << statement.tokens[i].value << " ";
			}

			if (statement.validity)
			{
				file << "Valid";
			}
			else
			{
				file << "Invalid";
			}
			file << "\t\t\t";
			file << statement.message;
			file << endl;
		}
	}
	// cout << ">> Generating syntax tree..." << endl
	// 	 << endl;
	// cout << ">> Output file generated: " << outputFileParser << endl
	// 	 << endl;
	file.close();
}

/*============================================= SEMANTIC ANALYSIS ================================================*/

enum DataType
{
	INT,
	STRING,
	BOOL,
	FLOAT
};

struct Variable
{
	string name;
	DataType type;
	bool initialized = false;
};

unordered_map<string, Variable> symbol_table;

// void analyze(vector<Statement> *statement)
// {
// 	vector<Statement> statements;

// 	// Loop through the whole statement vector
// 	for (int i = 0; i < (*statement).size(); i++)
// 	{
// 		Statement currentStatement = (*statement)[i];

// 		// Semantic checks

// 		if (currentStatement.type == "DECLARATION") {

// 		}

// 	}

// }

void analyze(vector<Statement> *statements)
{
	for (Statement statement : *statements)
	{
		vector<Variable> declaredVariables;

		if (statement.type == "DECLARATION")
		{
			Variable var;
			var.type;
			var.name;
			var.initialized;

			for (int i = 0; i < statement.tokens.size(); i++) // Read each tokens of each statement
			{
				Token currentToken = (statement.tokens)[i];

				if (currentToken.type == DATA_TYPE)
				{
					if (currentToken.value == "int")
					{
						var.type = INT;
					}
					else if (currentToken.value == "string")
					{
						var.type = STRING;
					}
					else if (currentToken.value == "bool")
					{
						var.type = BOOL;
					}
					else if (currentToken.value == "float")
					{
						var.type = FLOAT;
					}
				}
				else if (currentToken.type == IDENTIFIER)
				{
					var.name = currentToken.value;

					if (statement.tokens[i + 1].type == ASSIGN_OP) // between int x ; || ,x, || ,x= || before x = //
					{
						var.initialized = true;
	
					}
					else if ((statement.tokens[i - 1].type == DATA_TYPE && statement.tokens[i + 1].value == ";"))
					{
						var.initialized = false;
					}

					// CHECK WHETHER VARIABLE WAS ALREADY DECLARED
						if (symbol_table.count(var.name) > 0)
						{
							statement.validity = false;
							cout << "Line " << statement.line << " : multiple declarations for identifier/variable '" + var.name + "'" << endl;
							statement.message = " multiple declarations for identifier/variable '" + var.name + "'";
							break;
						}

					symbol_table[var.name] = {var.name, var.type, var.initialized};
					declaredVariables.push_back(var);
				}
			}
		}
		else if (statement.type == "ASSIGNMENT")
		{
			Variable var;
			var.type;
			var.name;
			var.initialized;

			for (int i = 0; i < statement.tokens.size(); i++) // Read each tokens of each statement
			{
				Token currentToken = (statement.tokens)[i];

				if (currentToken.type == IDENTIFIER)
				{
					var.name = currentToken.value;

					if (symbol_table.count(var.name) == 0)
					{
						statement.validity = false;
						cout << "Line " << statement.line << " : identifier/variable '" << var.name << "' in assignment statement not declared" << endl;
						statement.message = "undeclared variable '" + var.name + "'";
						break;
					}
					else if (!symbol_table[var.name].initialized && !(statement.tokens[i+1].type == ASSIGN_OP))
					{
						statement.validity = false;
						cout << "Line " << statement.line << " : identifier/variable '" << var.name << "' in assignment statement not initialized" << endl;
						statement.message = "uninitialized variable '" + currentToken.value + "'";
						break;
					}
				}
				else if (statement.tokens[i+1].type == ASSIGN_OP)
				{
					symbol_table[currentToken.value].initialized = true;
				}
			}
		}
		// else if (statement.type == "ASSIGNMENT")
		// {

		// 	Variable var;
		// 	var.type;
		// 	var.name = statement.tokens[0].value;
		// 	// CHECK IF VARIABLE IS NOT DECLARED
		// 	if (symbol_table.count(var.name) == 0)
		// 	{
		// 		statement.validity = false;
		// 		cout << "identifier/variable '" << var.name << "' not declared" << endl;
		// 		statement.message = "identifier/variable '" + var.name + "' not declared";
		// 		continue;
		// 	}

		// 	if (symbol_table[var.name].initialized == false)
		// 	{
		// 		statement.validity = false;
		// 		cout << "identifier/variable in assignment statement '" << var.name << "' not initialized" << endl;
		// 		statement.message = "variable '" + var.name + "' not initialized";
		// 		continue;
		// 	}

		// 	DataType variable_type = symbol_table[var.name].type;
		// 	Token value_token = statement.tokens[2];
		// 	if (value_token.type == TokenType::IDENTIFIER)
		// 	{
		// 		string value_varName = value_token.value;
		// 		if (symbol_table.count(value_varName) == 0)
		// 		{
		// 			statement.validity = false;
		// 			statement.message = "identifier/variable valvar'" + value_varName + "' not declared";
		// 			continue;
		// 		}
		// 		DataType value_variable_type = symbol_table[value_varName].type;
		// 		if (value_variable_type != variable_type)
		// 		{
		// 			statement.validity = false;
		// 			statement.message = "variable initialization type mismatched";
		// 			continue;
		// 		}
		// 	}
		// 	// Handle other cases for checking type mismatch
		// 	symbol_table[var.name].initialized = true;

		// 	for (const auto &entry : symbol_table)
		// 	{
		// 		const string &varName = entry.first;
		// 		const Variable &variable = entry.second;

		// 		cout << "Variable name: " << varName << ", type: " << (int)variable.type << ", initialized: " << variable.initialized << endl;
		// 	}
		// }
		// Check for uninitialized variables
		for (Variable var : declaredVariables)
		{

			// if (!symbol_table[var].initialized)
			// {
			// 	statement.validity = false;
			// 	cout << "uninitialized variable '" << var << "'" << endl;
			// 	statement.message = "uninitialized variable '" + var + "'";
			// 	break;
			// }
		}
	}
	cout << "VARIABLE SYMBOL TABLE CONTENTS: " << endl;
	for (auto &pair : symbol_table)
	{
		std::cout << pair.first << ", data type id: " << pair.second.type << " (initialized: " << pair.second.initialized << ")" << std::endl;
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
			testStatementTokens(statements);
			// printSyntax(statements);
			analyze(&statements);
		}
		else
		{
			cout << "Error: file " << fileName << " not found." << endl;
		}
	}

	return 0;
}
