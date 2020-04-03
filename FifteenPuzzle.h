//
// Created by Andre on 4/2/2020.
//

#ifndef INC_15PUZZLE_FIFTEENPUZZLE_H
#define INC_15PUZZLE_FIFTEENPUZZLE_H


class FifteenPuzzle {
    private:
        //goal state of the 15 puzzle
        int goal[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
        //current state of the puzzle
        int initState[16];
    public:
        FifteenPuzzle();
        void displayState(int state[16]);
        bool solvability();
        int getBlankIndex(int state[16]);
        std::string * getAction(int state[16]);
        std::string * takeAction(int state[16], std::string actions[4]);
};





#endif //INC_15PUZZLE_FIFTEENPUZZLE_H
