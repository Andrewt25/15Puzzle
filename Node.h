//
// Created by Andre on 4/3/2020.
//

#ifndef INC_15PUZZLE_NODE_H
#define INC_15PUZZLE_NODE_H

#include "string"
#include "FifteenPuzzle.h"

class Node{
    private:
        int *state;
        std::string action;
        int pathCost;
        int depth;
    public:
        Node(int *state);
        Node(int state[16], Node *parent, std::string action);
        int getPathCost();
        int *getState();
        int getdepth();
        std::string getAction();
        Node *getChild(std::string action, FifteenPuzzle *problem);
        void decPathCost();
        void freeState();
};



#endif //INC_15PUZZLE_NODE_H
