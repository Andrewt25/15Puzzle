
#ifndef INC_15PUZZLE_SOLVEMETHODS_H
#define INC_15PUZZLE_SOLVEMETHODS_H

#include "Node.h"
#include "FifteenPuzzle.h"

void driver();
//used to find optimal solution
Node* IDA(FifteenPuzzle *problem);
Node* LimitedDepth(Node *node, FifteenPuzzle *problem, int max);



#endif //INC_15PUZZLE_SOLVEMETHODS_H
