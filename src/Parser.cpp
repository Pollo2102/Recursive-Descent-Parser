#include <iostream>

#include "Parser.h"

Parser::Parser()
{
    grammarFile = std::ifstream(FILENAME, std::fstream::in);
}

Parser::~Parser() {}

void Parser::parseGrammar()
{
    currentToken.clear();
}

void error(std::string errorMessage)
{
    std::cout << errorMessage << std::endl;

    std::exit(1);
}