//
// Created by Andre on 4/3/2020.
//

#include "Node.h"

//constructor for initial node in search
Node::Node(int *state)
{
    this->state = state;
    this->parent = NULL;
    this->action = "";
    this->depth = 0;
    this->pathCost = 0;
}
//constructor for nodes that are not initial postition
Node::Node(int *state, Node *parent, std::string action, int pathCost)
{
    this->state = state;
    this->parent = parent;
    this->action = action;
    this->depth = parent->getDepth() + 1;
    //takes parent pathcost add together with cost supplied from heuristic (pathcost param) then add one for increased depth
    this->pathCost = parent->getPathCost() + pathCost + 1;
}

int Node::getDepth() {
    return this->depth;
}
int Node::getPathCost() {
    return this->pathCost;
}
int *Node::getState() {
    return this->state;
}
std::string Node::getAction() {
    return this->action;
}
//create child node using designated action
Node *Node::getChild(std::string action, FifteenPuzzle problem)
{
    int *state = problem.takeAction(this->state, action);
    Node *child = new Node(state, this, action, problem.hCost(state));
    return child;
}

void Node::decPathCost()
{
    this->pathCost--;
}

void Node::freeState() {
    delete[] this->state;
    this->state = NULL;
}

void Node::removeParent() {
    this->parent = NULL;
}
