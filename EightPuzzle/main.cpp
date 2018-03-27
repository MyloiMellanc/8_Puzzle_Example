//
//  main.cpp
//  EightPuzzle
//
//  Created by Myloi Mellanc on 2018. 3. 27..
//  Copyright © 2018년 MyloiMellanc. All rights reserved.
//

#include "PuzzleNode.hpp"

#include <iostream>

#define NUMBER_OF_PROBLEM 4
int problems[NUMBER_OF_PROBLEM][BOARD_SIZE] = {{4,1,0,6,3,2,7,5,8},{4,3,1,6,5,2,0,7,8},{3,1,0,4,5,2,6,7,8},{0,1,2,3,4,5,6,7,8}};


void runDepthFirstSearchExample(int problem_num)
{
    DFSNode* start_node = new DFSNode(problems[problem_num], 0);
    
    DFSNode::_node_stack.push(start_node);
    
    while(PuzzleNode::isFinished() == false)
    {
        PuzzleNode* node = DFSNode::getNextNode();
        node->run();
    }
}


void runBreathFirstSearchExample(int problem_num)
{
    BFSNode* start_node = new BFSNode(problems[problem_num], 0);
    
    BFSNode::_node_queue.push(start_node);
    
    while(PuzzleNode::isFinished() == false)
    {
        PuzzleNode* node = BFSNode::getNextNode();
        node->run();
    }
}

void runAStarSearchExample(int problem_num)
{
    AStarNode* start_node = new AStarNode(problems[problem_num], 0);
    start_node->setHeuristicCost();
    AStarNode::_node_list.push_back(start_node);
    
    while(PuzzleNode::isFinished() == false)
    {
        PuzzleNode* node = AStarNode::getNextNode();
        node->run();
    }
    
}

void printDepthFirstSearchResult()
{
    for(int i = 0; i < NUMBER_OF_PROBLEM; i++)
    {
        PuzzleNode::setProblemNumber(i + 1);
        PuzzleNode::clearVisitedNodes();
        PuzzleNode::setFinished(false);
        
        DFSNode::clearNodeStack();
        runDepthFirstSearchExample(i);
    }
}

void printBreathFirstSearchResult()
{
    for(int i = 0; i < NUMBER_OF_PROBLEM; i++)
    {
        PuzzleNode::setProblemNumber(i + 1);
        PuzzleNode::clearVisitedNodes();
        PuzzleNode::setFinished(false);
        
        BFSNode::clearNodeQueue();
        runBreathFirstSearchExample(i);
    }
}


void printAStarSearchResult(int type)
{
    AStarNode::setHeuristicType(type);
    
    for(int i = 0; i < NUMBER_OF_PROBLEM; i++)
    {
        PuzzleNode::setProblemNumber(i + 1);
        PuzzleNode::clearVisitedNodes();
        PuzzleNode:: setFinished(false);
        
        AStarNode::clearNodeList();
        runAStarSearchExample(i);
    }
}


int main(int argc, const char * argv[]) {
    int arr[] = {1,2,3,4,5,6,7,8,0};
    PuzzleNode::initGoal(arr);
    
    printDepthFirstSearchResult();
    printBreathFirstSearchResult();
    printAStarSearchResult(HEURISTIC_TYPE::NUMBER_OF_TILES_OUT_OF_PLACE);
    printAStarSearchResult(HEURISTIC_TYPE::SUM_OF_MANHATTAN_DISTANCE);
    
    return 0;
}





