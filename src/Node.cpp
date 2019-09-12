

#include "Node.h"

Node::Node() {}

Node::Node(std::initializer_list<Node> Nodes) 
{
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

void Node::printAllNodes()
{
    std::cout << this << std::endl;
    for (size_t i = 0; i < children.size(); i++)
    {
        if (&this[i] != nullptr)
        {
            this[i].printAllNodes();
        }
    }
}

void Node::addChild(Node child)
{
    children.push_back(child);
}