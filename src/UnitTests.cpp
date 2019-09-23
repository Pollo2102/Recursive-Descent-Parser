#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>

#include "doctest.h"

#include "Node.h"
#include "Parser.h"


Node cmp1 = Node("cmp");
Node cmp2 = Node("cmp");
Node child1 = Node("child1");
Node child2 = Node("child2");
Node parentNode = Node("Parent", {child1, child2});

std::ostream& operator<<(std::ostream& out, Node node) { return out << node.getStateName(); }; 

TEST_CASE("operator<< Overload Test Case") //FIX
{
    std::cout <<  "Operator<< Overload Test: " << child1 << std::endl;
}

TEST_CASE("operator[] Overload Test Case") 
{
    std::cout << "Operator[] Overload Test: ";
    parentNode[0].printStateName();
}

TEST_CASE("operator== Overload Test Case") 
{
    std::cout << "Operator== Overload Test: ";
    CHECK((child1 == child2) == false);
    CHECK((cmp1 == cmp2) == true);
}

TEST_CASE("Initializer List Constructor Test Case") 
{
    Node testNode = Node("TestNode", {child1, child2});
    CHECK(testNode.isChildrenEmpty() == false);
    CHECK(testNode.countChildren() == 2);

    Node testNode2 = Node();
    CHECK(testNode2.isChildrenEmpty() == true);
}

TEST_CASE("Print All Nodes Test Case") 
{
    parentNode.printAllNodes();
}

// **************************************************************************
// Parser Test Cases
// **************************************************************************


TEST_CASE("Load File Test Case")
{
    Parser p;

    p.loadExpression(TEST_FILENAME);
    p.printCurrentToken();
    CHECK(p.getNumberOfTokens() == 11);
    p.setInitialToken();
}

