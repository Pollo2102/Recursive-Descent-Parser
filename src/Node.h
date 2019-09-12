#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <iostream>

class Node{
    std::string stateName;
    std::vector<Node> children;

public:
    Node();
    Node(std::string stateName);
    Node(std::initializer_list<Node> Nodes);
    ~Node();

    void printAllNodes();
    void addChild(Node child);
    void printStateName() { std::cout << stateName << std::endl; };

    bool isChildrenEmpty() { return children.empty(); }

    std::ostream& operator<<(std::ostream& out) { return out << &stateName;}; 
    Node& operator[](int index) { return children.at(index); };
};

#endif // !NODE_H