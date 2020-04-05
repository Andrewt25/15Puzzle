
#include <queue>
#include <iostream>
#include <unordered_set>
#include "PatternDatabase.h"


void generatePattern()
{
    int goal1[16] = {1,2,3,4,5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0};
    FifteenPuzzle p1(goal1, goal1);
    int subseta[5]= {1,2,3,4,5};
    std::unordered_map< unsigned long long,int> db = BFSBack(&p1, subseta);
    savePattern(db, "subset1.bin");

    int goal2[16] = {-1,-1,-1,-1,-1,6,7,8,-1,-1,11,12,-1,-1,-1,0};
    FifteenPuzzle p2(goal2, goal2);
    int subsetb[5]= {6,7,8,11,12};
    db = BFSBack(&p2, subsetb);
    savePattern(db, "subset2.bin");

    int goal3[16] = {-1,-1,-1,-1,-1,-1,-1,-1,9,10,-1,-1,13,14,15,0};
    FifteenPuzzle p3(goal3, goal3);
    int subsetc[5]= {9,10,13,14,15};
    db= BFSBack(&p3, subsetc);
    savePattern(db, "subset3.bin");
}

//saves unordered_map into supplied binary file
void savePattern(std::unordered_map<unsigned long long,int> db, const char *name)
{
    FILE * file;
    file = fopen(name, "w");
    if(file != NULL)
    {
        for(auto it = db.begin(); it != db.end(); it++)
        {
            fwrite(&(it->first), sizeof(unsigned long long), 1, file);
            fwrite(&(it->second), sizeof(int), 1, file);

        }
        fclose(file);
    }
}
//read supplied binary file into a unordered_map
std::unordered_map<unsigned long long,int> loadPattern(const char *name)
{
    FILE *file;
    file = fopen(name, "r");
    std::unordered_map< unsigned long long,int> db;
    if(file == NULL){fputs("File Error", stderr); exit(1);}
    unsigned long long key;
    int val;
    while(fread(&key, sizeof(unsigned long long), 1, file))
    {
        fread(&val, sizeof(int), 1, file );
        db[key] = val;
    }
    return db;
}
//converts positions of designated tiles into hash key
unsigned long long hashFunction(int *state, int *subset, bool blank)
{
    std::unordered_map <int, unsigned long long> positions;
//find all positions of interest
    for(int i = 0; i < 16; i++)
    {
        if(state[i] != -1)
        {
            //add 10 to i so each position is 2 digits
            unsigned long long j = i+10;
            positions[state[i]] = j;
        }
    }

//convers positons into key of form pos1pos2pos3pos4pos5 or pos0pos1pos2pos3pos4pos5 if position of blank is of interest
    unsigned long long key = 0;
    if(blank)
    {
        key = key +(positions[0]*10000000000);
    }
    key = key + (positions[subset[0]]*100000000);
    key = key + (positions[subset[1]]*1000000);
    key = key + (positions[subset[2]]*10000);
    key = key + (positions[subset[3]]*100);
    key = key + (positions[subset[4]]);

    return key;
}

//use queue data type for frontier then perform a depth first search on a partial problem starting at solution working
//backwards until all options are exhausted create pattern database
//only save first instance i.e lowest move count to db ignore any permutations that match with blank in different spot
//in the interest of memory only save nodes to be evaluated once they are evaluated they are removed from memory
//ie can't find solved path once solved
std::unordered_map<unsigned long long,int> BFSBack(FifteenPuzzle *problem, int subset[16])
{
    std::queue <Node *> frontier;
    std::unordered_map<unsigned long long, int>patternDb;
    std::unordered_set<unsigned long long>explored;
    Node *node, *child;
    Node *initial = new Node(problem->getInitial());
    frontier.push(initial);
    std::string *actions;
    unsigned long long key, parentKey;

    //keeps adding children to frontier queue until nodes are exhausted
    //or finds all permutations possible
    while(!frontier.empty()){
        //get value of first item in queue
        node = frontier.front();
        frontier.pop();

        //get actions of node
        actions = problem->getAction(node->getState());
        parentKey = hashFunction(node->getState(), subset, false);
        for(int i = 0; i < 4; i++){
            //gets children via all actions it can perform

            if(actions[i] != ""){
                child = node->getChild(actions[i], problem);
                //create key with blank position
                key = hashFunction(child->getState(), subset, true);

                //check if that node has already been explored if it has skip it
                if(explored.count(key) == 0){


                    explored.insert(key);
                    //add key without blank to database
                    key = hashFunction(child->getState(), subset, false);
                    //checks if blank switched with a generic tile decrements pathcost if is did
                    if(key == parentKey)
                        child->decPathCost();
                    frontier.push(child);
                    if(patternDb.count(key) == 0){
                        patternDb[key] = child->getPathCost();
                    } else{
                        //if the key already exists checks if existing key value is larger
                        //if it is replace it with new value to ensure heuristic will be
                        //admissible
                        if (patternDb[key] > child->getPathCost())
                            patternDb[key] = child->getPathCost();
                    }
                } else{
                    //free memory if child wasn't added to frontier
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

    std::cout<< patternDb.size()<<std::endl;
    std::cout<< explored.size()<<std::endl;
    return patternDb;
}



