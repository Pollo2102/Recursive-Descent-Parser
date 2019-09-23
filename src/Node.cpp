

#include "Node.h"

Node::Node() {}

Node::Node(std::string sName, std::initializer_list<Node> Nodes) 
{
    stateName = sName;
    for(auto var : Nodes)
    {
        children.push_back(var);
    }
}

Node::Node(std::string sName) 
{
    stateName = sName;
}

Node::~Node() 
{

}

//std::ostream& operator<<(std::ostream& out, Node node) { return out << node.getStateName(); }; 

void Node::printAllNodes()
{
    std::cout << stateName << std::endl;
    for (size_t i = 0; i < children.size(); i++)
    {
        children.at(i).printAllNodes();
    }
}

std::string Node::getChildrenNames()
{
    std::string names;

    for(auto var : children)
    {
        names += var.getStateName() + " ";
    }

    return names;
}

void Node::addChild(Node child)
{
    children.push_back(child);
}

int Node::countChildren()
{
    return children.size();
}