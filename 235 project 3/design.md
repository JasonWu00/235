# PROJECT INSTRUCTIONS
Write an interpreter for the made-up programming language 'HUNLAN'.

## WHAT WILL BE DONE TO TEST INTERPRETER
I will take your program and compile it. Then, the resulting executable will be used to run program files, same way you do it in Python. From your source code, I will create an executable named hunlan with the following command
    >>> g++  -std=c++17  *.cpp  -o hunlan

Later, I create a plain txt file mycode.hun with the program code in HUNLAN. Then, I execute this code the following way
    >>> ./hunlan  mycode.hun

## INCORRECT / INVALID INSTRUCTION
In case the interpreter finds incorrect instruction in the source code, it shows an error message with the line number where the error occurred.
    ERROR: Bad instruction in Line 28

Specifing the exact problem is not necessary.
Program lines are enumerated starting from 1. 
Empty lines and ones with comments are also enumerated.

NOTE: should we report the error message for every line in which there is an invalid instruction, or just


## DESCRIPTION OF HUNLAN LANGUAGE
* *ONLY* one instruction per line
* empty lines without instructions are allowed
* everything starting with # is ignored until the end of the line,
    one line comment
* case-sensitive
* separators including space and tabs are allowed
* instructions can have multiple leading and trailing separators

## VARIABLES AND DATA-TYPES
* *NUMBER* 8-byte integer, long long in C++
* *STRING* is a string

*variable declaration* looks like:
    datatype  variable_name

*variable naming* follows C++ variable naming rules

* *numeric literals* 
    * consisting of only digits
    * no negative values of literals (however, negative values for variables and expressions is allowed)

* *string literals* 
    * consisting of any ASCII characters *except* double-quotation marks
    * string literals must be enclosed in double-quotation marks
    * *escape sequences* 
        * behave just like C++ strings

* *assignment operator =*  
* assigning the value of one string variable to another string variable

    **prohibited operations**  
        * assignment of numeric values to strings
        * assignment of string values to numeric variables

## MATHEMATICAL EXPRESSIONS
* + , - , and * are valid operators
* precedence rules work as normal (PEMDAS)
    
    **prohibited**
    * usage of strings or string literals anywhere in the expression is prohibited
    * no negative value literals in HUNLAN, however negative values of variables and expressions are allowed

## PRINT COMMAND
* prints one single variable or literal of any type

    **prohibited**
    * using PRINT with more than one variable or literal
    * supplying mathematical expressions to PRINT

## MULTIPLE VARIABLE DECLARATIONS
* means declaring variable with the same name more than once
    * causes unspecified behaviour
    * our program is free to react on it in any way
        * program crashes, error messages, or silent execution

---
# STEPS
1. get file name
    * make sure it is of the right file extension
2. *open* file
3. *parse* the string
4. break it down into *tokens*
5. *lexical analysis*, does it make sense?
    a. if not, return the *first* line in which there is an error
        TODO: clarify with shostak: 
            do we have to return all errors or just the first one we encounter?
    b. otherwise, execute program as normal

---
# MILESTONES

---
# ISSUES / TODO LIST



---
# NOTES