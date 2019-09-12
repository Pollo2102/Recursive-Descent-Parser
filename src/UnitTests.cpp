#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>

#include "doctest.h"

#include "Node.h"
#include "Parser.h"


Node child1 = Node("child1");
Node child2 = Node("child2");
Node parentNode = Node({child1, child2});

TEST_CASE("operator<< Overload Test Case") //FIX
{
    std::cout << &child1 << std::endl;
}

TEST_CASE("operator[] Overload Test Case") 
{
    parentNode[0].printStateName();
}

TEST_CASE("Initializer List Constructor Test Case") 
{
    Node testNode = Node({child1, child2});
    CHECK(testNode.isChildrenEmpty() == false);

    Node testNode2 = Node();
    CHECK(testNode2.isChildrenEmpty() == true);
}

/* TEST_CASE("Print All Nodes Test Case") 
{
    parentNode.printAllNodes();
} */