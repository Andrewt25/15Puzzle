//
// Created by Andre on 4/3/2020.
//

#ifndef INC_15PUZZLE_NODE_H
#define INC_15PUZZLE_NODE_H

#include "string"
#include "FifteenPuzzle.h"

class Node{
    private:
        Node *parent;
        int *state;
        std::string action;
        int depth;
        int pathCost;
    public:
        Node(int *state);
        Node(int *state, Node *parent, std::string action, int pathCost);
        int getDepth();
        int getPathCost();
        int *getState();
        std::string getAction();
        Node *getChild(std::string action, FifteenPuzzle problem);
        void decPathCost();
        void removeParent();
        void freeState();
};



#endif //INC_15PUZZLE_NODE_H
