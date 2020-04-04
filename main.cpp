#include <iostream>
#include "FifteenPuzzle.h"
#include"SolveMethods.h"
#include "PatternDatabase.h"

int main() {
    int goal[16] = {1,2,3,4,5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0};
    int state[16] = {1,-1,3,4,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,5};
    int part[5] = {1,2,3,4,5};
    int key = hashFunction(goal, part, false);
    std::cout<<key<<std::endl;

    FifteenPuzzle p(goal, goal);
    std::unordered_map<int,int> *db = BFSPartial(p, part);



    return 0;
}
