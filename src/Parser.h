#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "Node.h"

#define FILENAME "grammar.txt"
#define TEST_FILENAME "testFile.txt"

class Parser{

    std::string currentToken;
    uint32_t currentIndex;    
    std::vector<std::string> expression;

public:
    Node rootNode;
    Parser();
    ~Parser();

    void parseGrammar(std::string filename);
    int getNumberOfTokens() { return expression.size(); };
    void restartParser();
    void printToken(std::string token) { std::cout << token; };
    void printCurrentToken() { std::cout << currentToken; };
    void loadExpression(std::string filename);
    void setInitialToken();
    void getNextToken();
    bool hasToken(std::vector<std::string> tokenList);
    void error(std::string errorMessage);
    void printCurrentFunction(std::string message);
    bool isID(std::string token);

    Node optional_func_declaration();
    Node func_head();
    Node body();
    Node func_name();
    Node func_type();
    Node param_list();
    Node decl_param();
    Node stmts();
    Node stmt();
    Node func_mods();
    Node decl_type();
    Node compound_stmt();
    Node while_stmt();
    Node if_stmt();
    Node expr_stmt();
    Node return_stmt();
    Node while_test();
    Node else_stmt();
    Node if_conds();
    Node id_opts();
    Node bool_expr();
    Node if_cond();
    Node assign_stmt();
    Node id_opt();
    Node expr();
    Node par_list();
    Node simple_expr();
    Node term();
    Node factor();
    Node constant();
    Node field();
    Node function();
    Node eval();
    Node qualifier();
    Node eval_name();
    Node prm_list();
};

#endif // !PARSER_H