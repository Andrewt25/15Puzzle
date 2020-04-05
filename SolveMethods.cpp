

#include <iostream>
#include "SolveMethods.h"
#include "FifteenPuzzle.h"
#include"SolveMethods.h"
#include "PatternDatabase.h"

void driver()
{
    std::unordered_map <unsigned  long long, int>db1;
    std::unordered_map <unsigned  long long, int>db2;
    std::unordered_map <unsigned  long long, int>db3;
    //load precalulated sub problems into program
    db1 = loadPattern("subset1.bin");
    db2 = loadPattern("subset2.bin");
    db3 = loadPattern("subset3.bin");

    int test[16] = {1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,0};
    int t[16] = {6,12,1,13,14,8,4,2,0,11,10,5,15,7,9,3};
    FifteenPuzzle p(db1,db2,db3);
    Node *n = IDA(&p);
    int in = 1;
    while(in != 0)
    {
        std::cout<<"Please Choose Option 1: Random Puzzle, 2: Enter Puzzle or 0: Exit";
        std::cin>>in;
        if(in == 1)
        {
            p = FifteenPuzzle(db1,db2,db3);
            n = IDA(&p);
        }

        else if(in == 2)
        {
            std::cout<<"Please enter Tile numbers in the order you would like them to appear 0 for blank tile";
            int state[16];
            for(int i = 0; i < 16; i++)
            {
                std::cin>>state[i];
            }
            p = FifteenPuzzle(state,db1,db2,db3);
            if(p.getInitial()[0] != -1)
            {
                n = IDA(&p);
            }
        }
    }


}

Node* IDA(FifteenPuzzle *problem)
{
    //initial max set to 80
    int max = 1;
    Node *result = NULL;
    double t1 = time(NULL);
    //max number of moves to optimal solution is 80
    //if max exceeds 80 optimal solution won't be found
    while(result == NULL && max <= 80)
    {
        Node *node = new Node(problem->getInitial());
       result = LimitedDepth(node, problem, max);
       max++;
    }
    double t2 = time(NULL) -t1;
    std::cout<<"Solve Time: "<< t2<<"secs"<<std::endl;

}

Node* LimitedDepth(Node* node, FifteenPuzzle *problem, int max)
{
//initilize first node and needed pointers
    Node *child;
    std::string *actions;
    Node *result = NULL;
    //find the h value using additive pattern database
    int h = problem->hCost(node->getState());
    //find the f by adding depth of node with h value
    int f = node->getdepth() + h;

   if(f > max){
       //free memory from node being discarded
       if(node->getAction() != "")
           node->freeState();
      delete node;

       return NULL;
    // h == 0 iff  current state is goal state ie solution found
   }else if(h == 0){
       std::cout<<"Moves to Solution: "<<node->getdepth()<<std::endl;
       return node;
   } else{
       //get actions of current node
       actions = problem->getAction(node->getState());
       for(int i = 0; i < 4; ++i){
           //checks if action at position i is valid
           if(actions[i] != "" && actions[i] != node->getAction())
           {
               //create child with valid action
               child = node->getChild(actions[i], problem);
               //recursively call LimitedDepth with increasing depth
               result = LimitedDepth(child, problem, max);
               //result != NULL when a solution is found so remaining children can be skipped
               if(result != NULL)
                  i = i+4;
           }
       }
   }
   //free memory for current node
    if(node->getAction() != "")
        node->freeState();
    delete node;
    delete[] actions;
    //return result either solution or NULL
   return result;

}


