#include <math.h>
#include <random>
#include <chrono>
#include <algorithm>
#include "BoardState.h"

using namespace std;



class MCTS_Node {
    private:
        BoardState boardState;  // The board state of this board

        vector<int> untried_child_moves;  // The untried child moves of the board state of this node, init: all child moves

        MCTS_Node* parent;     // The parent of this node
        vector<MCTS_Node*> children;   // The children of this node

        vector<int> children_move;  // The corresponding move to the children of this node

        int num_visits;     // The number of visits of this node
        unsigned long long total_result;   // The sum of results of this node
        unsigned long long total_squared_result;   // The sum of squared results of this node
        int top_score;  // The top score achieved

    public:
        MCTS_Node(BoardState &board_state);    // The MCTS node constructor given a board state
        void assignParentNode(MCTS_Node* &parent_node);     // Assign the parent node to this node
        double computeUCT();    // Compute the uct value of this child
        BoardState& getBoardState();    // Get the board state of this node
        int getNumVisits();  // Return the number of visits of this node
        unsigned long long getTotalReuslt();    // Return the total result
        unsigned long long getTotalSquaredResult();     // Return the total squared results
        int getTopScore();  // Get the top score achieved by this node
        double getAvgScore();    // Get the average score
        double getVariance();    // Get the variance of this node
        MCTS_Node* getParentPtr();  // Get the pointer of the parent node
        bool isChildrenEmpty();     // Check if the children of this node is empty
        vector<int>& getUntriedChildMoves();      // The untried child moves of the board state of this node
        int getNumUntriedChildMoves();   // Get the number of untried child modes of the node
        int getChildMove(int i);     // Get the ith child move of the child nodes of this node
        MCTS_Node* getChildNodePtr(int i);    // Get the ith pointer of the child nodes of this node
        int getNumChildNodes();     // Get the number of child nodes of this nodes
        void appendChildNode(MCTS_Node* child_node_ptr, int child_move);     // Append the child node to the children of this node
        void increase_NumVisits();   // Increase the number of visits by 1
        void increase_Results(int given_result);     // Increase the total result, squared total result by the given score
        void update_TopScore(int given_result);      // Update the top score achieved by this node
};


class MCTS {
    private:
        static const int MAX_NODES_NUM = 1000000;  // The max number of nodes stored in the MCT

        BoardState boardState;     // Assign the initial game board state of the MCT

    public:
        MCTS(BoardState &board_state);     // The MCTS constructor
        void selection(MCTS_Node* &selected_node_ptr);      // The selection operator of MCTS
        void selection_heuristic(MCTS_Node* &selected_node_ptr);   // The selection operator of MCTS with game heuristic (prior knowledge), return the pointer to the selected MCTS_Node
        void selection_ProgressivePruning(MCTS_Node* &selected_node_ptr);     // The selection operator of MCTS using progressive pruning
        void expansion(MCTS_Node* &parent_node_ptr, vector<MCTS_Node> &MCT);     // The expansion operator of MCTS
        int rollout_Random(MCTS_Node* &given_node_ptr);     // The rollout operator of MCTS using the random policy
        int rollout_TabuRandom(MCTS_Node* &given_node_ptr);   // The rollout operator of MCTS using the TabuRandom policy
        int rollout_TabuColorRandom(MCTS_Node* &given_node_ptr);   // The rollout operator of MCTS using the TabuColorRandom policy
        void backpropagation(MCTS_Node* &given_node_ptr, int rollout_result);     // The backpropagation operator of MCTS
        void search(int &this_topscore, double &this_avgscore);     // Start the MCTS
};
