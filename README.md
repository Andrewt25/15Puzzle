# 15Puzzle solver

# FIFTEENPUZZLE.CPP
  Constructor and relevant methods for solving a random puzzle
  includes functions for
    -getting next action
    -creating starting state
    -finding heuristic values 
    -various helper functions
    
# NODE.CPP  
  Creates Nodes for curent puzzle Nodes represent given state of a puzzle
    - Contains info of state value, available actions, pathCost and depth
    - contains helper functions to get children states and free memory when
      state is no longer needed
      
# PatternDatabase.CPP
  Pattern Database generates the pattern database by using a breadth first search starting at the goal state
  working backwards until all nodes are exhausted and stores the results in a 5-5-5 structure {1,2,3,4,5}. {6,7,8,9,10} and      {11,12,13,14,15} this info in binaryfiles that can quickly be retrieved later for use by SolveMethods.
  
# SOLVEMETHODS.CPP
  Solve Method uses a  IDA* pattern dataabase heuristic search to solve a given puzzle state in minimal number of moves
