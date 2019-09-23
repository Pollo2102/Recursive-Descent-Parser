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
    Node(std::string stateName, std::initializer_list<Node> Nodes);
    Node(std::string stateName);
    ~Node();

    void printAllNodes();
    void addChild(Node child);
    int countChildren();
    void printStateName() { std::cout << stateName << std::endl; };
    std::string getStateName() { return stateName; };
    void setStateName(std::string sName) { stateName = sName; };

    std::string getChildrenNames();

    bool isChildrenEmpty() { return children.empty(); }

    Node& operator[](int index) { return children.at(index); };
    bool operator==(Node node){ return node.getStateName() == stateName; };
};

//std::ostream& operator<<(std::ostream& out, Node node) { return out << node.getStateName(); }; //Test if it works on the Node.cpp

#endif // !NODE_H