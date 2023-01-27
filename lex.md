# Lexical Analyzer


1. Press the links below and download the files
2. Open the files in Notepad or VSC 

	    				
	Input : [program source code](https://drive.google.com/file/d/1ES7oFvLA2uSb91zWPLaDPO4KUjbpo2cm/view)  ===> Output:   [output symbol table](https://drive.google.com/file/d/1SDI_dCKG0TRyaVEPeDchNJ58pNFgQr72/view)

>A <span style="color: #34DFA8"><b>Lexeme</b></span> is a string of characters that is a lowest-level syntatic unit in the programming language. The <span style="color: #34DFA8"><b>Lexer</b></span> is a program that takes a string of characters as input and divides it into smaller units called <span style="color: #34DFA8"><b>Tokens</b></span>. These tokens can be words, numbers, or special characters that have a specific meaning in a programming language. 

For example, consider: 

```c

int x = a + 2; float y = b / 4; bool z = c < d;

```
Lexemes: 
- int
- x
- = 
- \+ 
- a
...etc

Tokens: 
- int (KEYWORD)
- x (IDENTIFIER)
- = (ASSIGN)
-  \+ (ARITH_OP)
- \> (REL_OP)

...etc



## Task to distribute

1. Symbol table
2. FSM/Transition Table
3. Code