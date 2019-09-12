#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <iostream>

#define FILENAME "grammar.txt"

class Parser{
    Parser();
    ~Parser();

    std::string currentToken;
    std::ifstream grammarFile;

    void parseGrammar();
    void error(std::string errorMessage);
};

#endif // !PARSER_H