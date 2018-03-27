//
//  PuzzleNode.hpp
//  EightPuzzle
//
//  Created by Myloi Mellanc on 2018. 3. 27..
//  Copyright © 2018년 MyloiMellanc. All rights reserved.
//

#ifndef PuzzleNode_hpp
#define PuzzleNode_hpp

#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <iostream>


#define BOARD_SIZE 9
#define INTERVAL 3



class DFSNode;
class BFSNode;
class AStarNode;

class PuzzleNode
{
public:
    friend PuzzleNode;
    friend DFSNode;
    friend BFSNode;
    friend AStarNode;
    
    bool compare(PuzzleNode* node);
    bool isVisited(PuzzleNode* node);
    bool compareGoal();
    
    void printNode()
    {
        for(int i = 0; i < BOARD_SIZE; i++)
            std::cout << _board[i] << " ";
        std::cout << std::endl;
    }
    
public:
    PuzzleNode(int arr[], int depth);
    virtual ~PuzzleNode();
    
    virtual void expand() = 0;
    virtual void printResult() = 0;
    
    void run();
    
    static void setProblemNumber(int number);
    static void setFinished(bool finished);
    
    static bool isFinished();
    static void initGoal(int arr[]);
    static void clearVisitedNodes();
    
    
private:
    static int _goal[BOARD_SIZE];
    static int _problem_number;
    static std::vector<PuzzleNode*> _visited_nodes;
    static bool _finished;
    
    
    int _depth;
    int _board[BOARD_SIZE];
    
};




class DFSNode : public PuzzleNode
{
public:
    DFSNode(int arr[], int depth);
    virtual ~DFSNode();
    
    DFSNode* createMovedNode(int direction_x, int direction_y);
    
    static PuzzleNode* getNextNode();
    virtual void expand();
    virtual void printResult();
    
    static std::stack<DFSNode*> _node_stack;
    static void clearNodeStack();
    
private:
    static unsigned long _stack_max_count;
    void updateStackMaxCount();
};


class BFSNode : public PuzzleNode
{
public:
    BFSNode(int arr[], int depth);
    virtual ~BFSNode();
    
    BFSNode* createMovedNode(int direction_x, int direction_y);
    
    static PuzzleNode* getNextNode();
    virtual void expand();
    virtual void printResult();
    
    static std::queue<BFSNode*> _node_queue;
    static void clearNodeQueue();
    
private:
    static unsigned long _queue_max_count;
    void updateQueueMaxCount();
};


enum HEURISTIC_TYPE
{
    NUMBER_OF_TILES_OUT_OF_PLACE = 1,
    SUM_OF_MANHATTAN_DISTANCE = 2
};

class AStarNode : public PuzzleNode
{
public:
    AStarNode(int arr[], int depth);
    virtual ~AStarNode();
    
    AStarNode* createMovedNode(int direction_x, int direction_y);
    
    static PuzzleNode* getNextNode();
    virtual void expand();
    virtual void printResult();
    
    static std::list<AStarNode*> _node_list;
    static void clearNodeList();
    
    static void setHeuristicType(int type);
    void setHeuristicCost();
private:
    static int _heuristic_type;
    int _heuristic_cost;
    
    
    static unsigned long _list_max_count;
    void updateListMaxCount();
};



#endif /* PuzzleNode_hpp */
