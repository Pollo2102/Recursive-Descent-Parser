#include <iostream>

#include "Parser.h"

static const std::vector<std::string> INITIAL_TOKENS({"int", "void", "anytype", "boolean", "date", "real", "String"});

Parser::Parser()
{
    restartParser();
}

Parser::~Parser() {}


void Parser::setInitialToken() 
{
    currentToken = expression.at(0);
    currentIndex = 0;
}

void Parser::error(std::string errorMessage)
{
    std::cout << errorMessage << std::endl;

    std::exit(1);
}

void Parser::restartParser()
{
    currentIndex = 0;
    expression.clear();
    currentToken.clear();
}

void Parser::parseGrammar(std::string filename)
{
    restartParser();
    loadExpression(filename);
    setInitialToken();

    if (currentToken.empty())
        error("Expression is Empty");

    /* if (currentToken == "static")
        getNextToken(); */

    rootNode.addChild(optional_func_declaration());
    rootNode.setStateName(rootNode.getChildrenNames());
    rootNode.printAllNodes();
}

Node Parser::optional_func_declaration()
{
    printCurrentFunction("optional_func_declaration");
    Node tempNode;

    tempNode.addChild(func_head());
    tempNode.addChild(body());
    optional_func_declaration();

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::func_head()
{
    printCurrentFunction("func_head");
    Node tempNode;

    tempNode.addChild(func_name());
    tempNode.addChild(param_list());

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::body()
{
    printCurrentFunction("body");
    Node tempNode;

    if (currentToken == "{")
        tempNode.addChild(Node("{"));
    else
        error("Expected \"{\" but got " + currentToken);
    
    getNextToken();
    tempNode.addChild(stmts());

    if (currentToken == "}")
        tempNode.addChild(Node("}"));
    else
        error("Expected \"}\" but got " + currentToken);

    tempNode.setStateName(tempNode.getChildrenNames());
    getNextToken();
    return tempNode;
}


Node Parser::func_name()
{
    printCurrentFunction("func_name");
    Node tempNode;

    tempNode.addChild(func_type());

    if (isID(currentToken))
        tempNode.addChild(Node(currentToken));
    else
        error("Expected an ID but got " + currentToken);
    
    tempNode.setStateName(tempNode.getChildrenNames());
    getNextToken();
    return tempNode;
}

Node Parser::param_list()
{
    printCurrentFunction("param_list");
    Node tempNode;

    tempNode.addChild(decl_param());

    while (currentToken == ",")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
        tempNode.addChild(decl_param());
    }

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::stmts()
{
    printCurrentFunction("stmts");
    Node tempNode;

    tempNode.addChild(stmt());

    while (currentToken == "{" || currentToken == "while" 
        || currentToken == "if" || isID(currentToken) 
        || currentToken == "EXIT")
        {
            tempNode.addChild(stmt());
            getNextToken();
        }
    
    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::func_type()
{
    printCurrentFunction("func_type");
    Node tempNode;

    if (currentToken == "static")
    {
        tempNode.addChild(func_mods());
    }
    tempNode.addChild(decl_type());

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::decl_param()
{
    printCurrentFunction("decl_param");
    Node tempNode;

    tempNode.addChild(decl_type());
    if (isID(currentToken))
    {
        tempNode.addChild(Node(currentToken));
        tempNode.setStateName(tempNode.getChildrenNames());
        getNextToken();
    }
    else
        error("Expected an ID but got: " + currentToken);

    return tempNode;
}

Node Parser::stmt()
{
    printCurrentFunction("stmt");
    Node tempNode;

    if (currentToken == "{")
    {
        tempNode.addChild(Node(compound_stmt()));
    }
    else if (currentToken == "while")
    {
        tempNode.addChild(Node(while_stmt()));
    }
    else if (currentToken == "if")
    {
        tempNode.addChild(Node(if_stmt()));
    }
    else if (isID(currentToken)) // Expr stmt
    {
        tempNode.addChild(Node(expr_stmt()));
    }
    else if(currentToken == "EXIT")
    {
        tempNode.addChild(Node(return_stmt()));
    }
    else
        error("Expected a statement, but got: " + currentToken);

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::func_mods()
{
    printCurrentFunction("func_mods");
    Node tempNode;

    if (currentToken == "static")
        tempNode.setStateName("static");
    else
        error("Expected \"static\" but got: " + currentToken);

    tempNode.setStateName(tempNode.getChildrenNames());
    getNextToken();
    return tempNode;
}

Node Parser::decl_type()
{
    printCurrentFunction("decl_type");
    Node tempNode;

    if (currentToken == "int" || currentToken == "anytype"
        || currentToken == "boolean" || currentToken == "void"
        || currentToken == "real" || currentToken == "String"
        || currentToken == "date")
        tempNode.setStateName(currentToken);
    else
        error("Expected a Type Declaration but got: " + currentToken);

    tempNode.setStateName(tempNode.getChildrenNames());
    getNextToken();
    return tempNode;
}

Node Parser::compound_stmt()
{
    printCurrentFunction("compound_stmt");
    Node tempNode;

    if (currentToken == "{")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
    }
    else
        error("Expected a { but got: " + currentToken);

    tempNode.addChild(stmts());
    if (currentToken == "}")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
    }
    else
        error("Expected a } but got: " + currentToken);

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::while_stmt()
{
    printCurrentFunction("while_stmt");
    Node tempNode;

    tempNode.addChild(while_test());
    tempNode.addChild(stmt());

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::if_stmt()
{
    printCurrentFunction("if_stmt");
    Node tempNode;

    tempNode.addChild(if_conds());
    if (currentToken == "else")
    {
        tempNode.addChild(else_stmt());
    }
    tempNode.setStateName(tempNode.getChildrenNames());

    return tempNode;
}

Node Parser::expr_stmt()
{
    printCurrentFunction("expr_stmt");
    Node tempNode;

    if (isID(currentToken))
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
    }
    tempNode.addChild(id_opts());

    if (currentToken == ";")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
    }
    else
        error("Expected \';\' but got: " + currentToken);

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::return_stmt()
{
    printCurrentFunction("return_stmt");
    Node tempNode;

    if (currentToken == "EXIT")
    {
        tempNode.addChild(Node("EXIT"));
        getNextToken();
    }
    else
        error("Expected EXIT but got: " + currentToken);

    tempNode.addChild(bool_expr());
    
    if (currentToken == ";")
    {
        tempNode.addChild(Node(";"));
        getNextToken();
    }
    else
        error("Expected \';\' but got: " + currentToken);

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::while_test()
{
    printCurrentFunction("while_test");
    Node tempNode;

    if (currentToken == "while")
    {
        tempNode.addChild(Node("while"));
        getNextToken();
    }
    else
        error("Expected \'while\' but got: " + currentToken);
    
    if (currentToken == "(")
    {
        tempNode.addChild(Node("("));
        getNextToken();
    }
    else
        error("Expected \'(\' but got: " + currentToken);

    tempNode.addChild(bool_expr());

    if (currentToken == ")")
    {
        tempNode.addChild(Node(")"));
        getNextToken();
    }
    else
        error("Expected \')\' but got: " + currentToken);

    tempNode.setStateName(tempNode.getChildrenNames());

    return tempNode;
}

Node Parser::else_stmt()
{
    printCurrentFunction("else_stmt");
    Node tempNode;

    if (currentToken == "else")
    {
        tempNode.addChild(Node("else"));
        getNextToken();
    }
    else
        error("Expected \'else\' but got: " + currentToken);

    tempNode.addChild(stmt());

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::if_conds()
{
    printCurrentFunction("if_conds");
    Node tempNode;

    tempNode.addChild(if_cond());
    tempNode.addChild(stmt());
    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::id_opts()
{
    printCurrentFunction("id_opts");
    Node tempNode;

    tempNode.addChild(assign_stmt());
    tempNode.addChild(id_opt());
    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::bool_expr()
{
    printCurrentFunction("bool_expr");
    Node tempNode;

    tempNode.addChild(expr());
    
    while (currentToken == "||" || currentToken == "&&")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
        tempNode.addChild(expr());
    }
    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::if_cond()
{
    printCurrentFunction("if_cond");
    Node tempNode;

    if (currentToken == "if")
    {
        tempNode.addChild(Node("if"));
        getNextToken();
    }
    else
        error("Expected \'if\' but got: " + currentToken);

    if (currentToken == "(")
    {
        tempNode.addChild(Node("("));
        getNextToken();
    }
    else
        error("Expected \'(\' but got: " + currentToken);

    tempNode.addChild(bool_expr());

    if (currentToken == ")")
    {
        tempNode.addChild(Node(")"));
        getNextToken();
    }
    else
        error("Expected \')\' but got: " + currentToken);

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::assign_stmt()
{
    printCurrentFunction("assign_stmt");
    Node tempNode;

    if (currentToken == ":=")
    {
        tempNode.addChild(Node(":="));
        getNextToken();
    }

    tempNode.addChild(bool_expr());

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::id_opt() // Adapt everything to this
{
    printCurrentFunction("id_opt");
    Node tempNode;

    if (currentToken == ":")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
        if (isID(currentToken))
            tempNode.addChild(Node(currentToken));
        else
            error("Expected an ID but got: " + currentToken);
        getNextToken();
    }
    else if (currentToken == "::")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
        if (isID(currentToken))
            tempNode.addChild(Node(currentToken));
        else
            error("Expected an ID but got: " + currentToken);
        getNextToken();
    }
    else if (currentToken == "(")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
        tempNode.addChild(par_list());
        if (currentToken == ")")
        {
            tempNode.addChild(Node(currentToken));
            getNextToken();
        }
        else
            error("Expected \')\' but got: " + currentToken);
    }
    else if (currentToken == ":=")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
        tempNode.addChild(bool_expr());
    }
    else
        error("Expected ID_OPT but got: " + currentToken);

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::expr()
{
    printCurrentFunction("expr");
    Node tempNode;

    tempNode.addChild(simple_expr());

    if (currentToken == ">" || currentToken == "<"
        || currentToken == "==" || currentToken == "<="
        || currentToken == ">=")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
        tempNode.addChild(simple_expr());
    }

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::par_list()
{
    printCurrentFunction("par_list");
    Node tempNode;

    tempNode.addChild(bool_expr());

    if (currentToken == ",")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
        tempNode.addChild(bool_expr());
    }

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::simple_expr()
{
    printCurrentFunction("simple_expr");
    Node tempNode;

    tempNode.addChild(term());

    if (currentToken == "+" || currentToken == "-")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
        tempNode.addChild(term());
    }

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::term()
{
    printCurrentFunction("term");
    Node tempNode;

    tempNode.addChild(factor());

    if (currentToken == "*" || currentToken == "/")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
        tempNode.addChild(factor());
    }

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::factor()
{
    printCurrentFunction("factor");
    Node tempNode;

    if (currentToken == "(")
    {
        tempNode.addChild(Node("("));
        getNextToken();
        std::cout << "paso1\n";
        tempNode.addChild(bool_expr());
        std::cout << "paso2\n";
        if (currentToken == ")")
        {
            tempNode.addChild(currentToken);
            getNextToken();
        }
        else
            error("Expected a \')\' but got: " + currentToken);
    }
    else if ((isID(currentToken) 
            && (expression.at(currentIndex + 1) == "::" 
            || expression.at(currentIndex + 1) == "."))
            )
    {
        tempNode.addChild(qualifier());
        if (isID(currentToken))
            tempNode.addChild(Node(currentToken));
        else
            error("Expected ID but got: " + currentToken);
        getNextToken();
    }
    else if ((currentToken[0] > 47 && currentToken[0] < 58)
            || currentToken == "true" || currentToken == "false"
            || isID(currentToken))
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
    }
    else
        error("Expected an ID or a \'(\' but got: " + currentToken);

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::qualifier()
{
    printCurrentFunction("qualifier");
    Node tempNode;

    if (isID(currentToken))
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
        if (currentToken == "." || currentToken == "::")
        {
            tempNode.addChild(Node(currentToken));
            getNextToken();
        }
        else
            error("Expected a \'.\' or a \':\' but got: " + currentToken);
    }
    else
        error("Expected an ID but got: " + currentToken);

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::eval()
{
    printCurrentFunction("eval");
    Node tempNode;

    tempNode.addChild(eval_name());
    tempNode.addChild(prm_list());

    if (currentToken == ")")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
    }
    else
        error("Expected a \')\' but got: " + currentToken);

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::eval_name()
{
    printCurrentFunction("eval_name");
    Node tempNode;

    if (isID(currentToken))
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
    }
    else
        error("Expected an ID but got: " + currentToken);

    if (currentToken == "(")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
    }
    else
        error("Expected a \'(\' but got: " + currentToken);

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

Node Parser::prm_list()
{
    printCurrentFunction("prm_list");
    Node tempNode;

    tempNode.addChild(bool_expr());

    if (currentToken == ",")
    {
        tempNode.addChild(Node(currentToken));
        getNextToken();
        tempNode.addChild(bool_expr());
    }

    tempNode.setStateName(tempNode.getChildrenNames());
    return tempNode;
}

void Parser::printCurrentFunction(std::string message)
{
    std::cout << message << std::endl;
}

bool Parser::isID(std::string token)
{
    if (token[0] == '_' || (token[0] > 64 && token[0] < 90) 
    || (token[0] > 96 && token[0] < 123))
        return true;
    return false;
}

bool Parser::hasToken(std::vector<std::string> tokenList)
{
    for(auto var : tokenList)
    {
        if (var == currentToken)
            return true;
    }

    return false;
}

void Parser::getNextToken()
{
    if ((expression.empty()) || !(++currentIndex < expression.size()))
    {
        currentToken = "";
        currentIndex++;
        std::cout << "End of input\n\n";
        std::cout << "Printing all Tokens: ...\n";
        rootNode.printAllNodes();
        exit(0);
    }
    else
        currentToken = expression.at(currentIndex);
}

void Parser::loadExpression(std::string filename) // Make a test case
{ 
    std::fstream file(TEST_FILENAME, std::ios::in);
    // Node tempNode;


    if (!file)
    {
        std::cout << "Failed to load file.\n";
        return;
    }
    std::string stream;

    file.seekg(std::ios::beg);

    while(std::getline(file, stream))
    {
        expression.push_back(stream);
        /* Node tempChild("stream");
        tempNode.addChild(tempChild); */
        stream.clear();
    }
    // rootNode = tempNode;
}