/*
	# Lexical Analyzer for Wika Programming Language

	Language: C++

	To compile, type in Powershell:
	```
		g++ lex-copy.c
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

string fileName = "marco.wika";
string outputFileName = "output_symbol_table.wika";

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
	SEMICOLON
};

struct Token
{
	TokenType type;
	string value;
	string description;
};

unordered_map<string, Token> tokenTypeMap = {
	// Data Type
	{"karakter", {DATA_TYPE, "karakter", "Character Data Type"}},
	{"buumbilang", {DATA_TYPE, "buumbilang", "Integer Data Type"}},
	{"bahagimbilang", {DATA_TYPE, "bahagimbilang", "Floating Point Data Type"}},
	{"bool", {DATA_TYPE, "bool", "Character Data Type"}},
	{"string", {DATA_TYPE, "string", "String Data Type"}},

	// Keyword
	{"kunin", {KEYWORD, "kunin", "Input Statement"}},
	{"tignan", {KEYWORD, "tignan", "Output Statement"}},

	// Reserved Word
	{"kung", {RESERVED_WORD, "kung", "Conditional Statement"}},
	{"kundi_kung", {RESERVED_WORD, "kundi_kung", "Conditional Statement"}},
	{"kundi", {RESERVED_WORD, "kundi", "Conditional Statement"}},
	{"hanggang", {KEYWORD, "hanggang", "Repetition Statement"}},
	{"habang", {KEYWORD, "habang", "Repetition Statement"}},

	// Logical Operator
	{"hindi", {LOG_OP, "hindi", "Logical Operator"}},
	{"at", {LOG_OP, "at", "Logical Operator"}},
	{"o_kaya", {LOG_OP, "o_kaya", "Logical Operator"}},

	// Constant

	{"tama", {CONSTANT, "tama", "Boolean Constant Value"}},
	{"mali", {CONSTANT, "mali", "Boolean Constant Value"}},

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

	int line = 1;
	int col = 1;
	int lineStart;

	for (int i = 0; i < input.size(); i++)
	{
		char c = input[i];

		if (c == '\n')
		{
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
			tokens.push_back({ARITH_OP, string(1, c), "Addition Symbol"});
			break;
		case '-':
			tokens.push_back({ARITH_OP, string(1, c), "Subraction Symbol"});
			break;
		case '*':
			tokens.push_back({ARITH_OP, string(1, c), "Multiplication Symbol"});
			break;
		case '%':
			tokens.push_back({ARITH_OP, string(1, c), "Modulus Symbol"});
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
				tokens.push_back({COMMENT, "//", "Single Line Comment start"});
				tokens.push_back({COMMENT, tokenValue, "Single line comment"});
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
				tokens.push_back({COMMENT, "/*", "Multi Line Comment Start"});
				tokens.push_back({COMMENT, tokenValue, "Multi line comment"});
				tokens.push_back({COMMENT, "*/", "Multi Line Comment End"});
			}
			else
			{
				// not a comment, treat as an operator
				tokenValue = input[i];
				tokens.push_back({ARITH_OP, tokenValue, "Division Symbol"});
			}
			break;
		case '=':
			if (input[i + 1] == '=')
			{
				tokens.push_back({REL_OP, "==", "Relational Operator"});
				i++;
			}
			else
			{
				tokens.push_back({ASSIGN_OP, string(1, c), "Assignment Operator"});
			}
			break;
		case '>':
			if (input[i + 1] == '=')
			{
				tokens.push_back({REL_OP, ">=", "Relational Operator"});
				i++;
			}
			else
			{
				tokens.push_back({REL_OP, string(1, c), "Relational Operator"});
			}
			break;
		case '<':
			if (input[i + 1] == '=')
			{
				tokens.push_back({REL_OP, "<=", "Relational Operator"});
				i++;
			}
			else
			{
				tokens.push_back({REL_OP, string(1, c), "Relational Operator"});
			}
			break;
		case '!':
			if (input[i + 1] == '=')
			{
				tokens.push_back({REL_OP, "!=", "Relational Operator"});
				i++;
			}
			else
			{
				tokens.push_back({LOG_OP, string(1, c), "Logical Operator"});
			}
			break;
		case ';':
			tokens.push_back({SEMICOLON, string(1, c), "Semicolon"});
			break;
		case '\\':
			tokens.push_back({DELIMITER, string(1, c), "Backslash"});
			break;
		case '(':
			tokens.push_back({DELIMITER, string(1, c), "Left Parenthesis"});
			break;
		case ')':
			tokens.push_back({DELIMITER, string(1, c), "Right Parenthesis"});
			break;
		case '[':
			tokens.push_back({DELIMITER, string(1, c), "Left Bracket"});
			break;
		case ']':
			tokens.push_back({DELIMITER, string(1, c), "Right Bracket"});
			break;
		case '{':
			tokens.push_back({DELIMITER, string(1, c), "Left Braces"});
			break;
		case '}':
			tokens.push_back({DELIMITER, string(1, c), "Right Braces"});
			break;
		case ',':
			tokens.push_back({DELIMITER, string(1, c), "Comma"});
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
				tokens.push_back({CONSTANT, tokenValue, "Float Constant Value"});
				break;
			}
			else
			{
				// If the character before the '.' is not a digit, we have a single '.' token
				// Add the '.' token to the list of tokens

				tokens.push_back({DELIMITER, ".", "Period"});
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
			tokens.push_back({DELIMITER, "\"", "Delimiter Double Quotation"});
			tokens.push_back({CONSTANT, tokenValue, "String Constant Value"});
			tokens.push_back({DELIMITER, "\"", "Delimiter Double Quotation"});
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
				TokenType type = IDENTIFIER;

				if (tokenTypeMap.count(tokenValue) > 0)
				{
					type = tokenTypeMap[tokenValue].type;
					tokenDescription = tokenTypeMap[tokenValue].description;
				}
				else
				{
					tokenDescription = "Identifier " + tokenValue;
				}
				tokens.push_back({type, tokenValue, tokenDescription});
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
				tokens.push_back({CONSTANT, tokenValue, "Integer Constant Value"});
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
			 << "INDEX\t\t\t"
			 << "TOKEN\t\t\t\t"
			 << "TYPE\t\t\t"
			 << "DESCRIPTION\t\t"
			 << endl;
		for (int i = 0; i < tokens.size(); i++)
		{
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
	cout << ">> Generating output symbol table..." << endl << endl;
	cout << ">> Output file generated: " << outputFileName << endl << endl;
	file.close();
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
		}
		else
		{
			cout << "Error: file " << fileName << " not found." << endl;
		}
	}

	//   string input = "!!== string xyz_123 = abc + 2-;/% \n if for while - <= == >=  float{}[]nope)(";
	//   cout << endl << "Input string: " << endl << input << endl << endl;

	return 0;
}
