//
// Created by Andre on 4/3/2020.
//

#ifndef INC_15PUZZLE_PATTERNDATABASE_H
#define INC_15PUZZLE_PATTERNDATABASE_H

#include "FifteenPuzzle.h"
#include "Node.h"
#include <unordered_map>

void generatePatternTripleFive();
void savePattern();
void loadPattern();
int hashFunction(int state[16], int subset[5], bool blank);
std::unordered_map<int,int> *BFSPartial(FifteenPuzzle problem, int subset[5]);
void checkGeneric(Node* n, FifteenPuzzle p);


#endif //INC_15PUZZLE_PATTERNDATABASE_H
