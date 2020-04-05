
#ifndef INC_15PUZZLE_PATTERNDATABASE_H
#define INC_15PUZZLE_PATTERNDATABASE_H

#include "FifteenPuzzle.h"
#include "Node.h"
#include <unordered_map>
void generatePattern();
void savePattern(std::unordered_map<unsigned long long,int> db, const char* name);
std::unordered_map<unsigned long long,int> loadPattern(const char *name);
unsigned long long hashFunction(int state[16], int subset[5], bool blank);
std::unordered_map<unsigned long long,int> BFSBack(FifteenPuzzle *problem, int subset[5]);
void checkGeneric(Node* n, FifteenPuzzle p);


#endif //INC_15PUZZLE_PATTERNDATABASE_H
