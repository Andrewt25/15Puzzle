
#include <iostream>
#include "Node.h"

//constructor for initial node in search
Node::Node(int *state)
{
    this->state = state;
    this->action = "";
    this->depth = 0;
    this->pathCost = 0;
}
//constructor for nodes that are not initial postition
Node::Node(int *state, Node *parent, std::string action)
{
    this->state = state;
    this->action = action;
    this->depth = parent->getdepth() + 1;
    //takes parent pathcost add together with cost supplied from heuristic (pathcost param) then add one for increased depth
    //if no db supplied defaults to 0 for supplied pathcost
    this->pathCost = parent->getPathCost() + 1;
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
Node *Node::getChild(std::string action, FifteenPuzzle *problem)
{
    int *state = problem->takeAction(this->state, action);
    if(action == "up")
        action = "down";
    else if(action == "down")
        action = "up";
    else if(action == "right")
        action = "left";
    else
        action = "right";
    Node *child = new Node(state, this, action);
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

int Node::getdepth() {
    return this->depth;
}
