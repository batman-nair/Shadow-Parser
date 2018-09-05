# Compiler Suite

## General Flow

 1. Get Grammar from file
 2. Pass Grammar to Parser for building
   - Errors like ShiftReduceException or ReduceReduceException may be raised
 3. Input is given to the ParseTable to check if it satisfies the grammar
 4. Output is given according to whether the given string is accepted or not

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
Alphabet : set<char>
ParseCell : pair<char, int>
ParseRow : vector<ParseCell>
ParseTable: vector<ParseRow>
```

### Alphabet
 - Will have functions like isTerminal(char), isVariable(char)

### Parser

#### build(Grammar) -> ParseTable
 - Called as Constructor
 - Takes Grammar as input and outputs a ParseTable

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
 - All parser files go inside the parser folder inside the src folder
 - All C++ files use the extension .cc and all headers use the extension .h
 - `main.cc` file inside the src folder handles the general flow of the program

## Contributing
 Wanna be part of the team? Feel free to contact and chip in.
