# Compiler Suite

## General Flow

Main flow of the program is in `main.cc` inside the src folder

 1. Get Grammar from file
 2. Pass Grammar to Parser for building
     - Errors like ShiftReduceException or ReduceReduceException may be raised
 3. Input is given to the Parser to check if it satisfies the grammar
 4. Output is given according to whether the given string is accepted or not

## Building

 - Run `make` in the root directory to build the project, object files go inside the build directory
 - Generates a final binary in the root directory `shadow-parser`
 - `make clean` removes all build files and cleans up the project

## Grammar
The Grammar file will be of the format
```
S->aBc
```
where S is the left hand side of the production and aBc is the right hand side of the production
Capital letters are considered to be Variables and small letters are considered to be terminals

## Classes and Special Files

### Types <types.h>
```
ProdType : pair<char, string>
Grammar : vector<ProdType>
ParseRowType : vector<string>
ParseTableType: vector<ParseRowType>
```

### Grammar
 - parseFile takes in a filename and builds the grammar
 - parseSymbols extracts the terminals and variables from the grammar
 - getGrammar returns the grammar built

### Parser

 - Abstract class for all the parsers to build on

#### parseGrammar(Grammar, set<char>, set<char>)
 - Takes Grammar, terminals and variables as input
 - builds a parse table as a variable in the class

### ParseTable
 - Length of ParseRow is same as the number of Alphabets
 - The int in ParseCell gives the next state
 - The char in ParseCell can be:
   - s : shift
   - r : reduce
   - a : accept
   - e : error ( default )
 - The index of the ParseRow in a ParseTable signifies the state when the row is considered

## Folder and File Structure
 - All source files go inside the src folder
 - All header files go inside the include folder
 - All parser files go inside the parser folder inside the corresponding folder
 - All C++ files use the extension .cc and all headers use the extension .h
 - `main.cc` file inside the src folder handles the general flow of the program

## Contributing
 Wanna be part of the team? Feel free to contact and chip in.
