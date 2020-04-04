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
        solvable = solvability(initState);
    }
    std::cout<<"Initial state of Puzzle"<<std::endl;
    displayState(initState);
}
//constructor to solve given state
FifteenPuzzle::FifteenPuzzle(int *state)
{
    if(!solvability(state))
    {
        std::cout<<"Initial state is not solvable";
    }
    else
    {
        std::cout<<"Initial state of Puzzle"<<std::endl;
        for (int i = 0; i < 16; i++)
        {
            initState[i] = state[i];
        }
        displayState(initState);
    }

}
//constructor for partial problems
FifteenPuzzle::FifteenPuzzle(int *state, int *goal)
{
    for (int i = 0; i < 16; i++)
    {
        initState[i] = state[i];
    }
    for (int i = 0; i < 16; i++)
    {
        goalState[i] = goal[i];
    }
    displayState(initState);
    displayState(goalState);
}
//return address of initial state
int *FifteenPuzzle::getInitial() {
    return initState;
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
bool FifteenPuzzle::solvability(int *state)
{
    int inv = 0;
    int inv_sol = 0;
    for (int i  = 0; i < 16; i++)
    {
        for(int j = i+1; j < 16; j ++)
        {
            if(state[i] > state[j] && state[i] != 0 && state[j] != 0)
                inv++;
        }
    }

    int index = getBlankIndex(state);
    if(index < 4)
        inv_sol = 1;
    else if(index > 7 && index < 12 )
        inv_sol = 1;
    std::cout<< index<< std::endl;
    std::cout<< inv<< std::endl;
    std::cout<< inv_sol<< std::endl;
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

   std::string *actions;
   actions = new std::string[4];
   actions[0] = "up";
   actions[1] = "down";
   actions[2] = "left";
   actions[3] = "right";

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
//return newstate after a given action was taken
int *FifteenPuzzle::takeAction(int *state, std::string action)
{
    int blankIndex = getBlankIndex(state);
    int *newState = copyState(state);
    int change;
    if(action == "up")
        change = blankIndex - 4;
    else if(action == "down")
        change = blankIndex + 4;
    else if(action == "left")
        change = blankIndex - 1;
    else if(action == "right")
        change = blankIndex + 1;

    int temp = newState[change];
    newState[change] = newState[blankIndex];
    newState[blankIndex] = temp;

    return newState;
}
//check if given state is equal to goal state
bool FifteenPuzzle::check_solved(int *state)
{
    for(int i = 0; i < 16; i++)
    {
        if(state[i] != goalState[i])
            return false;
    }
    return  true;
}

//return copy of given state
int *FifteenPuzzle::copyState(int *state)
{
    int* newstate = new int[16];
    for(int i = 0; i < 16; i++)
        newstate[i] = state[i];
    return newstate;

}

int FifteenPuzzle::hCost(int *state) {
    return 0;
}







//finish build
//ida* search
    //recursion
    //finding node
//node stuff
    //
//database

//would be nice
//update display to be prettier
