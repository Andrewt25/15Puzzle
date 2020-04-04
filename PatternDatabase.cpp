//
// Created by Andre on 4/3/2020.
//


#include <queue>
#include <iostream>
#include <unordered_set>
#include "PatternDatabase.h"

void generatePatternTripleFive()
{
    std::unordered_map<int, int[16]> permutations;
}

void savePattern() {

}

void loadPattern() {

}

int hashFunction(int *state, int *subset, bool blank)
{
    std::unordered_map <int, int> positions;

    for(int i = 0; i < 16; i++)
    {
        if(state[i] != -1)
        {
            int j = i+4;
            positions[state[i]] = ((j/4)*10) + (j%4);
        }

    }

    int key = (positions[subset[0]]*100000000);
    key = key + (positions[subset[1]]*1000000);
    key = key + (positions[subset[2]]*10000);
    key = key + (positions[subset[3]]*100);
    key = key + (positions[subset[4]]*1);
    if(blank)
    {
        key = key + positions[0]*10000000000;
    }
   // std::cout<<key()
    return key;
}

//use queue data type for frontier then perform a depth first search on a partial problem starting at solution working
//backwards until all options are exhausted create pattern database
//only save first instance i.e lowest move count to db ignore any permutations that match with blank in different spot
//in the interest of memory only save nodes to be evaluated once they are evaluated they are removed from memory
//ie can't find solved path once solved
std::unordered_map<int,int> *BFSPartial(FifteenPuzzle problem, int * subset)
{
    std::queue <Node *> frontier;
    std::unordered_map<int, int>patternDb;
    std::unordered_set<int>explored;
    Node *node, *child;
    Node *initial = new Node(problem.getInitial());
    frontier.push(initial);
    std::string *actions;
    int key;

    //keeps adding children to frontier queue until nodes are exhausted
    //or finds all permutations possible
    while(!frontier.empty())
    {
        //get value of first item in queue
        node = frontier.front();
        frontier.pop();

        //get actions of node
        actions = problem.getAction(node->getState());

        for(int i = 0; i < 4; i++)
        {
            //gets children via all actions it can perform

            if(actions[i] != "" && actions[i] != node->getAction())
            {
                child = node->getChild(actions[i], problem);
                child->removeParent();
                //checks if blank switched with a generic tile decrements if is did


                key = hashFunction(child->getState(), subset, true);
                if(explored.count(key) == 0)
                {
                    checkGeneric(child, problem);
                    frontier.push(child);
                    explored.insert(key);
                    //add key without blank to database
                    key = hashFunction(child->getState(), subset, false);
                    if(patternDb.count(key) == 0)
                    {
                        patternDb[key] = child->getPathCost();
                    } else
                    {
                        if (patternDb[key] > child->getPathCost())
                            patternDb[key] = child->getPathCost();
                    }
                } else{
                    child->freeState();
                    delete child;
                }
            }
        }
        //free node after it has been evaluated
        if(node->getAction() != "")
            node->freeState();
        delete node;
        delete[] actions;
    }

    Node *clear;
    while(!frontier.empty())
    {
        clear = frontier.front();
        frontier.pop();
        if(clear->getAction() != "")
            clear->freeState();
        delete clear;
    }
    std::cout<< patternDb.size();
    return &patternDb;
}

void checkGeneric(Node *n, FifteenPuzzle p)
{
    std::string action = n->getAction();
    int blankIndex = p.getBlankIndex(n->getState());
    int change;
    if(action == "up")
        change = blankIndex + 4;
    else if(action == "down")
        change = blankIndex - 4;
    else if(action == "left")
        change = blankIndex + 1;
    else if(action == "right")
        change = blankIndex - 1;
    //std::cout<<blankIndex<<std::endl;

    if(n->getState()[change] == -1)
        n->decPathCost();

}
