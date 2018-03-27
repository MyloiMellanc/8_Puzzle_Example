//
//  PuzzleNode.cpp
//  EightPuzzle
//
//  Created by Myloi Mellanc on 2018. 3. 27..
//  Copyright © 2018년 MyloiMellanc. All rights reserved.
//

#include "PuzzleNode.hpp"

int PuzzleNode::_goal[BOARD_SIZE];
int PuzzleNode::_problem_number;
std::vector<PuzzleNode*> PuzzleNode::_visited_nodes;
bool PuzzleNode::_finished = false;


bool PuzzleNode::compare(PuzzleNode* node)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        if(_board[i] != node->_board[i])
            return false;
    }
    
    return true;
}


bool PuzzleNode::isVisited(PuzzleNode* node)
{
    for(int i = 0; i < _visited_nodes.size(); i++)
        if(_visited_nodes[i]->compare(node) == true)
            return true;
    
    return false;
}


PuzzleNode::PuzzleNode(int arr[], int depth)
: _depth(depth)
{
    for(int i = 0; i < BOARD_SIZE; i++)
        _board[i] = arr[i];
}

PuzzleNode::~PuzzleNode()
{
    
}

bool PuzzleNode::compareGoal()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        if(_board[i] != _goal[i])
            return false;
    }
    
    return true;
}

bool PuzzleNode::isFinished()
{
    return _finished;
}

void PuzzleNode::initGoal(int arr[])
{
    for(int i = 0; i < BOARD_SIZE; i++)
        _goal[i] = arr[i];
}

void PuzzleNode::clearVisitedNodes()
{
    std::for_each(_visited_nodes.begin(), _visited_nodes.end(), [](PuzzleNode* node)
                  {
                      delete node;
                  });
    
    _visited_nodes.clear();
}

void PuzzleNode::run()
{
    //골이 안 나왔다면 계속 진행
    if(PuzzleNode::_finished == true)
        return;
    
    //자신이 골이라면 진행 토글 후 종료
    if(compareGoal() == true)
    {
        printResult();
        
        PuzzleNode::_finished = true;
        return;
    }
    
    //Visited에 달기
    _visited_nodes.push_back(this);
    
    
    
    //골이 아니라면, 확장해서 스택에 푸시 - 단, Visited에 없어야함
    expand();
}


void PuzzleNode::setFinished(bool finished)
{
    _finished = finished;
}

void PuzzleNode::setProblemNumber(int number)
{
    _problem_number = number;
}


std::stack<DFSNode*> DFSNode::_node_stack;
unsigned long DFSNode::_stack_max_count = 0;


DFSNode::DFSNode(int arr[], int depth)
: PuzzleNode(arr, depth)
{
    
}

DFSNode::~DFSNode()
{
    
}

DFSNode* DFSNode::createMovedNode(int direction_x, int direction_y)
{
    int position;
    for(int i = 0; i < BOARD_SIZE; i++)
        if (_board[i] == 0)
            position = i;
    
    int y = position / INTERVAL;
    int x = position % INTERVAL;
    
    int moved_y = y + direction_y;
    int moved_x = x + direction_x;
    
    if((0 <= moved_y) && (moved_y < INTERVAL) && (0 <= moved_x) && (moved_x < INTERVAL))
    {
        int arr[BOARD_SIZE];
        for(int i = 0; i < BOARD_SIZE; i++)
            arr[i] = _board[i];
        
        int temp = arr[y * INTERVAL + x];
        arr[y * INTERVAL + x] = arr[moved_y * INTERVAL + moved_x];
        arr[moved_y * INTERVAL + moved_x] = temp;
        
        return new DFSNode(arr, _depth + 1);
    }
    
    return nullptr;
}

void DFSNode::updateStackMaxCount()
{
    if(_stack_max_count < _node_stack.size())
        _stack_max_count = _node_stack.size();
}


PuzzleNode* DFSNode::getNextNode()
{
    DFSNode* node = _node_stack.top();
    _node_stack.pop();
    
    return node;
}

void DFSNode::expand()
{
    //4개 방향의 노드를 만든 뒤, visited에 있는지 검사후 등록
    
    DFSNode* childs[4];
    childs[0] = createMovedNode(-1,0);
    childs[1] = createMovedNode(1,0);
    childs[2] = createMovedNode(0,-1);
    childs[3] = createMovedNode(0,1);
    
    
    for(int i = 0; i < 4; i++)
        if ((childs[i] != nullptr) && (isVisited(childs[i])) == false)
        {
            _node_stack.push(childs[i]);
            updateStackMaxCount();
        }
}

void DFSNode::printResult()
{
    std::cout << "Solution of Problem " << _problem_number << " using DFS" << std::endl;
    std::cout << "Total number of Visited Nodes : " << PuzzleNode::_visited_nodes.size() << std::endl;
    std::cout << "Maximum size of Stack : " << _stack_max_count << std::endl;
    std::cout << "Solution length : " << _depth << std::endl;
}

void DFSNode::clearNodeStack()
{
    while(_node_stack.empty() != true)
    {
        DFSNode* node = _node_stack.top();
        _node_stack.pop();
        
        delete node;
    }
}


std::queue<BFSNode*> BFSNode::_node_queue;
unsigned long BFSNode::_queue_max_count = 0;

BFSNode::BFSNode(int arr[], int depth)
: PuzzleNode(arr, depth)
{
    
}

BFSNode::~BFSNode()
{
    
}

BFSNode* BFSNode::createMovedNode(int direction_x, int direction_y)
{
    int position;
    for(int i = 0; i < BOARD_SIZE; i++)
        if (_board[i] == 0)
            position = i;
    
    int y = position / INTERVAL;
    int x = position % INTERVAL;
    
    int moved_y = y + direction_y;
    int moved_x = x + direction_x;
    
    if((0 <= moved_y) && (moved_y < INTERVAL) && (0 <= moved_x) && (moved_x < INTERVAL))
    {
        int arr[BOARD_SIZE];
        for(int i = 0; i < BOARD_SIZE; i++)
            arr[i] = _board[i];
        
        int temp = arr[y * INTERVAL + x];
        arr[y * INTERVAL + x] = arr[moved_y * INTERVAL + moved_x];
        arr[moved_y * INTERVAL + moved_x] = temp;
        
        return new BFSNode(arr, _depth + 1);
    }
    
    return nullptr;
}


PuzzleNode* BFSNode::getNextNode()
{
    BFSNode* node = _node_queue.front();
    _node_queue.pop();
    
    return node;
}

void BFSNode::expand()
{
    BFSNode* childs[4];
    childs[0] = createMovedNode(-1,0);
    childs[1] = createMovedNode(1,0);
    childs[2] = createMovedNode(0,-1);
    childs[3] = createMovedNode(0,1);
    
    
    for(int i = 0; i < 4; i++)
        if ((childs[i] != nullptr) && (isVisited(childs[i])) == false)
        {
            _node_queue.push(childs[i]);
            updateQueueMaxCount();
        }
}


void BFSNode::printResult()
{
    std::cout << "Solution of Problem " << _problem_number << " using BFS" << std::endl;
    std::cout << "Total number of Visited Nodes : " << PuzzleNode::_visited_nodes.size() << std::endl;
    std::cout << "Maximum size of Stack : " << _queue_max_count << std::endl;
    std::cout << "Solution length : " << _depth << std::endl;
}



void BFSNode::updateQueueMaxCount()
{
    if(_queue_max_count < _node_queue.size())
        _queue_max_count = _node_queue.size();
}

void BFSNode::clearNodeQueue()
{
    while(_node_queue.empty() != true)
    {
        BFSNode* node = _node_queue.front();
        _node_queue.pop();
        
        delete node;
    }
}



std::list<AStarNode*> AStarNode::_node_list;
unsigned long AStarNode::_list_max_count = 0;
int AStarNode::_heuristic_type;


AStarNode::AStarNode(int arr[], int depth)
: PuzzleNode(arr, depth)
{
    
}

AStarNode::~AStarNode()
{
    
}

AStarNode* AStarNode::createMovedNode(int direction_x, int direction_y)
{
    int position;
    for(int i = 0; i < BOARD_SIZE; i++)
        if (_board[i] == 0)
            position = i;
    
    int y = position / INTERVAL;
    int x = position % INTERVAL;
    
    int moved_y = y + direction_y;
    int moved_x = x + direction_x;
    
    if((0 <= moved_y) && (moved_y < INTERVAL) && (0 <= moved_x) && (moved_x < INTERVAL))
    {
        int arr[BOARD_SIZE];
        for(int i = 0; i < BOARD_SIZE; i++)
            arr[i] = _board[i];
        
        int temp = arr[y * INTERVAL + x];
        arr[y * INTERVAL + x] = arr[moved_y * INTERVAL + moved_x];
        arr[moved_y * INTERVAL + moved_x] = temp;
        
        AStarNode* node = new AStarNode(arr, _depth + 1);
        node->setHeuristicCost();
        
        return node;
    }
    
    return nullptr;
}

PuzzleNode* AStarNode::getNextNode()
{
    AStarNode* next_node = _node_list.front();
    std::for_each(_node_list.begin(), _node_list.end(), [&](AStarNode* node)
                  {
                      if(node->_heuristic_cost < next_node->_heuristic_cost)
                          next_node = node;
                  });
    
    _node_list.remove(next_node);
    
    return next_node;
}


void AStarNode::expand()
{
    AStarNode* childs[4];
    childs[0] = createMovedNode(-1,0);
    childs[1] = createMovedNode(1,0);
    childs[2] = createMovedNode(0,-1);
    childs[3] = createMovedNode(0,1);
    
    
    for(int i = 0; i < 4; i++)
        if ((childs[i] != nullptr) && (isVisited(childs[i])) == false)
        {
            _node_list.push_back(childs[i]);
            updateListMaxCount();
        }
}


void AStarNode::printResult()
{
    std::cout << "Solution of Problem " << _problem_number << " using A* - ";
    switch(_heuristic_type)
    {
        case HEURISTIC_TYPE::NUMBER_OF_TILES_OUT_OF_PLACE:
            std::cout << "# of tiles out of place" << std::endl;
        case HEURISTIC_TYPE::SUM_OF_MANHATTAN_DISTANCE:
            std::cout << "Sum of Manhattan Distance" << std::endl;
    }
    std::cout << "Total number of Visited Nodes : " << PuzzleNode::_visited_nodes.size() << std::endl;
    std::cout << "Maximum size of Stack : " << _list_max_count << std::endl;
    std::cout << "Solution length : " << _depth << std::endl;
}


void AStarNode::setHeuristicCost()
{
    switch(_heuristic_type)
    {
        case HEURISTIC_TYPE::NUMBER_OF_TILES_OUT_OF_PLACE:
        {
            int tile_count = 0;
            for(int i = 0; i < BOARD_SIZE; i++)
            {
                if(_board[i] != _goal[i])
                    tile_count++;
            }
            _heuristic_cost = tile_count;
            break;
        }
            
        case HEURISTIC_TYPE::SUM_OF_MANHATTAN_DISTANCE:
        {
            int distance_sum = 0;
            for(int i = 0; i < BOARD_SIZE; i++)
            {
                for(int j = 0; j < BOARD_SIZE; j++)
                {
                    if(_board[i] == _goal[j])
                    {
                        if(i == j)
                            break;
                        
                        int board_y = i / INTERVAL;
                        int board_x = i % INTERVAL;
                        int goal_y = j / INTERVAL;
                        int goal_x = j % INTERVAL;
                        
                        distance_sum += (std::abs(board_y - goal_y) + std::abs(board_x - goal_x));
                    }
                }
            }
            _heuristic_cost = distance_sum;
            break;
        }
            
        default:
            break;
    }
}

void AStarNode::updateListMaxCount()
{
    if(_list_max_count < _node_list.size())
        _list_max_count = _node_list.size();
}


void AStarNode::setHeuristicType(int type)
{
    _heuristic_type = type;
}


void AStarNode::clearNodeList()
{
    std::for_each(_node_list.begin(), _node_list.end(), [](AStarNode* node)
                  {
                      delete node;
                  });
    
    _node_list.clear();
}


