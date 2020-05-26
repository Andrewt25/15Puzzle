
#ifndef INC_15PUZZLE_FIFTEENPUZZLE_H
#define INC_15PUZZLE_FIFTEENPUZZLE_H

#include <unordered_map>
#include "string"

class FifteenPuzzle {
    private:
        //goal state of the 15 puzzle
        int goalState[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
        //initial state of the puzzle
        int initState[16];
        std::unordered_map <unsigned long long, int> db1;
        std::unordered_map <unsigned long long, int> db2;
        std::unordered_map <unsigned long long, int> db3;
    public:
        FifteenPuzzle(const std::unordered_map <unsigned long long, int>& db1, const std::unordered_map <unsigned long long, int>& db2, const std::unordered_map <unsigned long long, int>& db3 );
        FifteenPuzzle(int state[16], const std::unordered_map <unsigned long long, int>& db1, const std::unordered_map <unsigned long long, int>& db2, const std::unordered_map <unsigned long long, int>& db3);
        FifteenPuzzle(int state[16], int goal[16]);
        int *getInitial();
        void displayState(int state[16]);
        bool solvability(int state[16]);
        int getBlankIndex(int state[16]);
        std::string * getAction(int state[16]);
        int * takeAction(int state[16], std::string action);
        bool check_solved(int *state);
        int hCost(int state[16]);
        int *copyState(int *state);

};





#endif //INC_15PUZZLE_FIFTEENPUZZLE_H
