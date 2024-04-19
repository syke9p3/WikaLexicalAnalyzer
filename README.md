
## I. WiKa Programming Langugae  

This programming project was developed as an output for the course ***COSC 30053: Automata and Language Theory***. Moreover,this programming language draws inspiration
from **```Bato```**, a Filipino-based programming language using Ruby syntax.The goal of this project is to learn how to develop a simple lexer based on the **```C```** language.

## II. **How to use the lexer**

To use this program, follow these steps:

1. Save your WiKa code in a file with a `.wika` extension. For example, you can name it `filename.wika`.

2. Compile the C++ program provided using a C++ compiler like `g++`. For example, you can compile it using the following command in your terminal:
   ```
   g++ your_program_name.cpp -o your_output_name
   ```

3. Run the compiled program in your terminal, providing the name of your WiKa file as input. For example:
   ```
   ./your_output_name
   ```
   This will tokenize the code in your WiKa file and generate an output symbol table file named `output_symbol_table.wika`.

4. Open the generated `output_symbol_table.wika` file to view the tokenized symbols along with their types and descriptions.

## III. **Syntactic Elements of the Language**

### 1. **Character Sets**

All ASCII characters are accepted in the language.

### 2. **Identifiers**

**Rules in Naming Identifiers**
1. Maximum of 31 characters are allowed.
2. It must not be a keyword or reserved word.
3. It must be started with a letter or underscore(```_```)
4. _WiKa_ is case sensitive. Uppercase and lowercase consideredas different
	characters.
5. No white space
6. Identifiers can consist of only letters, digits, or underscore.

### 3. **Operation Symbols**

1. **Arithmetic:** +, –, *, /, %
2. **Relational:** >, >=, <, <=, ==, !=
3. **Logical:** hindi, o_kaya, at
4. **Assignment:** =

### 4. **Keywords and Reserved Words**

| Category    | Reserved words / Keywords<br> | Definition                                                                                                                                                                                          |
| ----------- | ------------------------------ | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Input       | ```kunin```                          | Function that takes and reads user’s input from standard input such as keyboards                                                                                                                 |
| Output      | `tignan`                         | Function that displays output to the screen                                                                                                                                                        |
| Data Types  | `karakter`                       | Refers to an ASCII character enclosed in single quotes                                                                                                                                            |
|             | `buumbilang`                     | Refers to all positive and negative whole numbers with no decimal values                                                                                                                          |
|             | `bahagimbilang`                  | Refers to all positive and negative numbers with a decimal point. It can also be represented in exponential                                                                                      |
|             | `bool`                           | Refers to a data type that contains only 2 values: 1 and 0. 1 represents true and 0 represents false                                                                                             |
|             | `string`                         | Refers to the sequence of characters enclosed in a single or double quotation marks                                                                                                              |
| Relational  | `hindi`                          | Either side needs to be true to produce a TRUE result                                                                                                                                              |
|             | `at`                             | Either side needs to be true to produce a TRUE result                                                                                                                                              |
|             | `o_kaya`                         | One or the other needs to be TRUE to produce a TRUE result                                                                                                                                        |
| Conditional | `kung`                           | The condition evaluates to either true or false. True is always a non-zero value, and false is a value that contains zero.                                                                      |
|             | `kundi kung`                     | If the value of test-expression is true, then the true block of statements will be executed. If the value of test-expression if false, then the false block of statements will be executed. |
| Repetition  | `kundi`                          | If previous conditions are not true displays alternate information or performs alternate commands                                                                                               |
|             | `hanggang`                       | Loops through a block of code several times, until the conditions are met                                                                                                                         |
|             | `gawin`                          | Hold a block of code for the loop and goes through it at least once before checking the loop condition                                                                                            |
|             | `habang`                         | Loops through a block of code while a condition is true                                                                                                                                           |
### 5. **Noise Words**

 The WiKa language has no noise word/s to be used.

### 6. **Comments**

| Comments             | Symbol Definition    |
|----------------------|----------------------|
| Single line comment  | `// Single line comment` |
| Multiple lines comment | `/* ... */ Multiple lines comment` |



### 7. Blanks / Spaces

WiKa requires at least one space to separate characters, words, expressions, or statements.

### 8. Delimeters and Brackets

| Symbol | Definition                            |
| ------ | ------------------------------------- |
| `;`      | End of every line / separates every statement |
| `()`     | Enclosing expressions                 |
| `{}`     | Enclosing multiple statements         |
| `' '`    | Enclosing a character literal         |
| `" "`    | Enclosing a string literal            |

### 9. Free-and-fixed Formats

WiKa program source text is free-format, using the semicolon as a statement separator and curly braces for grouping blocks of statements.


### 10. Expressions

| Expression | Definition                                                  |
| ------ | ------------------------------------------------------------ |
| Arithmetic |  |
| `<exp> = <exp> + <exp>` | addition or unary plus |
| `<exp> = <exp> - <exp>` | subtraction or unary minus |
| `<exp> = <exp> * <exp>` | multiplication |
| `<exp> = <exp> / <exp>` | division |
| `<exp> = <exp> % <exp>` | remainder after division (modulo division) |
| Relational |  |
| `<exp> > <exp>` | compares two expressions and returns TRUE if the left expression is greater than the right expression |
| `<exp> >= <exp>` | compares two expressions and returns TRUE if the left expression is greater than or equal to the right expression |
| `<exp> < <exp>` | compares two expressions and returns TRUE if the left expression is less than the right expression |
| `<exp> <= <exp>` | compares two expressions and returns TRUE if the left expression is less than or equal to the right expression |
| `<exp> == <exp>` | compares two expressions and returns TRUE if the left expression is equal to the right expression |
| `<exp> != <exp>` | compares two expressions and returns TRUE if the left expression is not equal to the right expression |
| Logical |  |
| `<exp> at <exp>` | Outputs TRUE if both expressions are TRUE |
| `<exp> o_kay <exp>` | Outputs TRUE if one or more expressions is TRUE |
| `hindi <exp>` | Inverts the result of a logical expression |
| Assignment |  |
| `<var> = <exp>` | Assigns a value to a variable |

This table should provide a clear overview of the expressions and their definitions in WiKa.
### 11. Statements

| Category    | Reserved words / Keywords | Syntax Definition                                        |
| ----------- | -------------------------- | --------------------------------------------------------- |
| Input       | `kunin`                      | `<var> = kunin();` Function that takes and reads user’s input from standard input such as keyboards |
| Output      | `tignan`                     | `tignan(<variable>);` Function that displays output to the screen |
| Data Types  | `karakter`                   | `karakter <ident_list>;` Refers to an ASCII character enclosed in single quotes |
|             | `buumbilang`                 | `buumbilang <ident_list>` Refers to all positive and negative whole numbers with no decimal values |
|             | `bahagimbilang`              | `bahagimbilang <ident_list>` Refers to all positive and negative numbers with a decimal point. It can also be represented in exponential |
|             | `bool`                       | `bool <ident_list>` Refers to a data type that contains only 2 values: 1 and 0. 1 represents true and 0 represents false |
|             | `string`                     | `string <ident_list>` Refers to the sequence of characters enclosed in a single or double quotation marks |
| Relational  | `hindi`                      | `hindi <exp>` Returns TRUE if the expression is FALSE or Returns FALSE if the expression is TRUE |
|             | `at`                         | `at <exp>` Returns TRUE if both Expression is TRUE |
|             | `o_kaya`                     | `o_kaya <exp>` Returns TRUE if one of the expression is TRUE |
| Conditional | `kung`                       | `kung (<exp>) { <statement> }` The condition evaluates to either true or false. True is always a non-zero value, and false is a value that contains zero. |
|             | `kundi kung`                 | `kundi kung(<exp>) { <statement> }` If the value of test-expression is true, then the true block of statements will be executed. If the value of test-expression if false, then the false block of statements will be executed. |
|             | `kundi`                      | `kundi { <statement> }` If previous conditions are not true displays alternate information or performs alternate commands |
| Repetition  | `hanggang`                   | `hanggang (<initialization>; <condition>, <increment>) { <statement> }` Loops through a block of code several times, until the conditions are met |
|             | `gawin`                      | `gawin { <statement> }` Hold a block of code for the loop and goes through it at least once before checking the loop condition |
|             | `habang`                     | `habang (<condition>)` Loops through a block of code while a condition is true |

## IV. Grammar Rules

| Non Terminals             | Terminals and Productions                                         |
|---------------------------|-------------------------------------------------------------------|
| `<statements>`            | `<statement>[<statements>]`                                      |
| `<statement>`             | `<declaration_statement>` \| `<conditional_statement>` \| `<loop_statement>` |
| `<declaration_statement>` | `<data_type>` `<identifier>`                                     |
| `<data_type>`             | karakter \| buumbilang \| bahagimbilang \| bool \| string       |
| `<identifier>`            | `<variable>` `<expression>` \| `<variable>`                      |
| `<variable>`              | `<alpha>` \| `<alphanum>`                                        |
| `<alpha>`                 | _ \| A \| B \| ... \| z                                         |
| `<alphanum>`              | `<alpha>` `<digit>`                                              |
| `<digit>`                 | constant                                                         |
| `<assign_op>`             | =                                                               |
| `constant`                | 0 \| 1 \| … \| 9                                                |
| `<expression>`            | `<assignment>` \| `<arith_exp>` \| `<increment>` \| `<decrement>` \| `<rel_exp>` \| `<log_exp>` \| `<con_exp>` |
| `<assignment>`            | `<variable>` `<assign_op>` `<expression>`                        |
| `<assign_op>`             | = \| += \| -= \| *= \| /= \| %=                                |
| `<arith_exp>`             | `<expression>` `<arith_op>` `<expression>` \| `<variable>` `<arith_op>` `<variable>` \| `<variable>` `<arith_op>` `<expression>` \| `<variable>` `<arith_op>` constant \| `<expression>` `<arith_op>` constant |
| `<arith_op>`              | + \| - \| * \| / \| %                                           |
| `<increment>`             | `<incr_op>` `<variable>`                                         |
| `<incr_op>`               | ++                                                              |
| `<decrement>`             | `<incr_op>` `<variable>`                                         |
| `<decr_op>`               | --                                                              |
| `<rel_exp>`               | `<expression>` `<rel_op>` `<expression>` \| `<variable>` `<rel_op>` `<variable>` \| `<variable>` `<rel_op>` `<expression>` \| `<variable>` `<rel_op>` constant \| `<expression>` `<rel_op>` constant |
| `<rel_op>`                | < \|> \| <= \| >= \| == \| !=                                   |
| `<log_exp>`               | `<log_op>` `<expression>` \| `<expression>` `<log_op>` `<expression>` |
| `<log_op>`                | hindi \| at \| o_kaya                                           |
| `<conditional_statement>` | kung (`<expression>`) `<statement>` [kundi `<statement>`] \| kung (`<expression>`) `<statement>` kundi_kung (`<expression>`) `<statement>` [kundi `<statement>`] |
| `<loop_statement>`        | hanggang (`<expression>`;`<expression>`;`<expression>`;) \| habang (`<expression>`) `<statement>` \| gawin `<statement>` habang (`<expression>`) |