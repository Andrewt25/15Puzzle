#include <iostream>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include "FifteenPuzzle.h"

//constructor creates random solvable starting state
FifteenPuzzle::FifteenPuzzle()
{
    bool solvable = false;
    //var used for random index
    int x;
    //use time to generate seed for rand()
    std::srand(time(NULL));

// create random board state until a solvable state is found
    while(!solvable)
    {
        //set array to -1 for placing elements
        std::memset(initState, -1, sizeof(initState) );

        //assigns number 0-15 a random position state array
        for(int i = 0; i <=15; i++)
        {
            //get random index
            x = rand()%16;
            //checks if index is empty
            if(initState[x] == -1)
                initState[x] = i;
            else
                //retries placing number if index already had a value
                i--;
        }
        solvable = solvability();
    }
    displayState(initState);
}
//display all 16 elements of array
void FifteenPuzzle::displayState(int *state)
{

    for(int i = 0; i < 16; i++)
    {
        if( i%4 == 3)
            std::cout << state[i] << std::endl;
        else
            std::cout << state[i] << " ";


    }
}
//checks if a given puzzle is solvable based on initial state
bool FifteenPuzzle::solvability()
{
    int inv = 0;
    int inv_sol = 0;
    for (int i  = 0; i < 16; i++)
    {
        for(int j = 0; j < 16; j ++)
        {
            if(initState[i] > initState[j] && initState[i] != 0 && initState[j] != 0)
                inv++;
        }
    }

    int index = getBlankIndex(initState);
    if(index < 4)
        inv_sol = 1;
    else if(index > 7 && index < 12 )
        inv_sol = 1;
    return (inv % 2 == inv_sol);
}
//find the position of blank square in given state
int FifteenPuzzle::getBlankIndex(int *state)
{
    int i = 0;
    bool found = false;
    while(!found)
    {
        if(state[i] == 0)
            found = true;
        else
            i++;
    }
    return i;
}
//return string array of valid moves for a given state
std::string * FifteenPuzzle::getAction(int *state)
{
   int blankIndex = getBlankIndex(state);
   std::string actions[4] = {"up", "down", "left", "right"};
   if(blankIndex < 4)
       actions[0] = "";
   if(blankIndex > 11)
       actions[1] = "";
   if(blankIndex%4 == 0)
       actions[2] = "";
   if(blankIndex%4 == 3)
       actions[3] = "";

    return actions;
}

