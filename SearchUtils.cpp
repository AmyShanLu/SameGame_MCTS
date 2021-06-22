#include "SearchUtils.h"



// The MCTS node constructor
MCTS_Node::MCTS_Node(BoardState &board_state) {
    boardState = board_state;   // Store the board state of this board

    untried_child_moves = board_state.generateChildMoves();  // The untried child moves of the board state of this node, init: all child moves

    parent = nullptr;   // Init the parent node of this node
    children.clear();   // Init the child nodes of this node

    children_move.clear();  // Init the move to each child node of this node

    num_visits = 0;     // Init the number of visits of this node
    total_result = 0;   // Init the sum of results of this node
    total_squared_result = 0;   // Init the sum of squared results of this node
    top_score = 0;  // Init the top score achieved by this node
}

// Assign the parent node to this node
void MCTS_Node::assignParentNode(MCTS_Node* &parent_node) {
    parent = parent_node;
}

// Compute the uct value of this child
double MCTS_Node::computeUCT() {
    double v_i = (double) total_result / (double) num_visits;  // Average result of this node

    int num_parent_visits;  // The number of visits of this node's parent

    if (parent != nullptr) {
        num_parent_visits = parent->getNumVisits();
    } else {
        num_parent_visits = num_visits;
    }

    double C = 0.5;

    double second_term_UCT = C * sqrt(log(num_parent_visits) / num_visits);   // The second term of the UCT formula

    double D = 10000;

    double mod_term_UCT = sqrt((total_squared_result - num_visits*pow(v_i, 2) + D) / num_visits);  // The last term in the modified UCT formula

    // return (v_i / 5000.0) + 0.02 * sqrt(log(num_parent_visits) / num_visits);    // static normalization
    // return v_i + second_term_UCT + mod_term_UCT;    // Modified UCT
    return 0.98*v_i + 0.02*(double) top_score + second_term_UCT + mod_term_UCT;    // Modified UCT with weighted top score added to the average score
}

 // Get the board state of this node
BoardState& MCTS_Node::getBoardState() {
    return boardState;
}

// Return the number of visits of this node
int MCTS_Node::getNumVisits() {
    return num_visits;
}

// Return the total result
unsigned long long MCTS_Node::getTotalReuslt() {
    return total_result;
}

// Return the total squared results
unsigned long long MCTS_Node::getTotalSquaredResult() {
    return total_squared_result;
}

// Get the top score achieved by this node
int MCTS_Node::getTopScore() {
    return top_score;
}

// Get the average score
double MCTS_Node::getAvgScore() {
    return (double) total_result / (double) num_visits;
}

// Get the variance of this node
double MCTS_Node::getVariance() {
    double variance = (total_squared_result - num_visits*pow(((double) total_result / (double) num_visits), 2) + boardState.getMaxPossibleScore()) / (double) (num_visits+1);

    return variance;
}

// Get the pointer of the parent node
MCTS_Node* MCTS_Node::getParentPtr() {
    return parent;
}

// Check if the children of this node is empty
bool MCTS_Node::isChildrenEmpty() {
    return children.empty();
}

// The untried child moves of the board state of this node
vector<int>& MCTS_Node::getUntriedChildMoves() {
    return untried_child_moves;
}

// Get the number of untried child modes of the node
int MCTS_Node::getNumUntriedChildMoves() {
    return (int) untried_child_moves.size();
}

// Get the ith child move of the child nodes of this node
int MCTS_Node::getChildMove(int i) {
    return children_move[i];
}

// Get the ith pointer of the child nodes of this node
MCTS_Node* MCTS_Node::getChildNodePtr(int i) {
    return children[i];
}

// Get the number of child nodes of this nodes
int MCTS_Node::getNumChildNodes() {
    return (int) children.size();
}

// Append the child node to the children of this node
void MCTS_Node::appendChildNode(MCTS_Node* child_node_ptr, int child_move) {
    children.push_back(child_node_ptr);
    children_move.push_back(child_move);   // Append the corresponding child move
}

// Increase the number of visits by 1
void MCTS_Node::increase_NumVisits() {
    num_visits += 1;
}

// Increase the total result, squared total result by the given score
void MCTS_Node::increase_Results(int given_result) {
    total_result += given_result;
    total_squared_result += pow(given_result, 2);
}

// Update the top score achieved by this node
void MCTS_Node::update_TopScore(int given_result) {
    if (given_result > top_score) {
        top_score = given_result;
    }
}



// The MCTS constructor. Initialize the root node of the MCT, the boardState of the root is the given state
MCTS::MCTS(BoardState &board_state) {
    boardState = board_state;   // Assign the initial game board state of the MCT
}

// The selection operator of MCTS, return the pointer to the selected MCTS_Node
void MCTS::selection(MCTS_Node* &selected_node_ptr) {
    MCTS_Node* parent_node_ptr = selected_node_ptr; // The pointer to the parent node

    selected_node_ptr = parent_node_ptr->getChildNodePtr(0);    // The pointer to the first child node

    double max_uct_val = selected_node_ptr->computeUCT();

    for (int i = 1; i < (int) parent_node_ptr->getNumChildNodes(); i++) {
        double this_uct_val = parent_node_ptr->getChildNodePtr(i)->computeUCT();

        if (max_uct_val < this_uct_val) {
            selected_node_ptr = parent_node_ptr->getChildNodePtr(i);

            max_uct_val = this_uct_val;
        }
    }
}

// The selection operator of MCTS with game heuristic (prior knowledge), return the pointer to the selected MCTS_Node
void MCTS::selection_heuristic(MCTS_Node* &selected_node_ptr) {
    MCTS_Node* parent_node_ptr = selected_node_ptr; // The pointer to the parent node

    selected_node_ptr = parent_node_ptr->getChildNodePtr(0);    // The pointer to the first child node

    int max_heuristic_val = selected_node_ptr->getBoardState().getHeuristicScore();

    for (int i = 1; i < (int) parent_node_ptr->getNumChildNodes(); i++) {
        int this_heuristic_val = parent_node_ptr->getChildNodePtr(i)->getBoardState().getHeuristicScore();

        if (max_heuristic_val < this_heuristic_val) {
            selected_node_ptr = parent_node_ptr->getChildNodePtr(i);

            max_heuristic_val = this_heuristic_val;
        }
    }
}

// The selection operator of MCTS using progressive pruning
void MCTS::selection_ProgressivePruning(MCTS_Node* &selected_node_ptr) {
    MCTS_Node* parent_node_ptr = selected_node_ptr; // The pointer to the parent node

    int num_child_nodes = (int) parent_node_ptr->getNumChildNodes();    // The number of child nodes of this parent node

    vector<pair<double, int> > estimatedValue_Index_ChildNodes;     // The estimated value and the corresponding index of child moves, the estimated value is the opposite of the average score
    vector<double> variance_ChildNodes;     // The variance of child nodes

    estimatedValue_Index_ChildNodes.reserve(num_child_nodes);
    variance_ChildNodes.reserve(num_child_nodes);

    for (int i = 0; i < num_child_nodes; i++) {
        // Push the opposite of the average score (estimated value) and the corresponding index of this child to the vector
        // estimatedValue_Index_ChildNodes.push_back(pair<double, int>(parent_node_ptr->getChildNodePtr(i)->getAvgScore(), i));
        estimatedValue_Index_ChildNodes.push_back(pair<double, int>((double) parent_node_ptr->getChildNodePtr(i)->getTopScore(), i));
        // Get the variance of the child nodes
        variance_ChildNodes.push_back(parent_node_ptr->getChildNodePtr(i)->getVariance());
    }

    // Sort child nodes according to the estimated value
    sort(estimatedValue_Index_ChildNodes.begin(), estimatedValue_Index_ChildNodes.end());

    vector<double> Prob_ChildNodes;     // The probability of selecting the child nodes,    u_0, ..., u_N

    Prob_ChildNodes.reserve(num_child_nodes);

    double total_Prob = 0.0;    // The total probabilities of the child nodes

    for (int i = 0; i < num_child_nodes; i++) {
        // Compute the proportional probability of the child node: num_child_nodes-1-i
        double this_child_prob = exp((-10.0) * ((estimatedValue_Index_ChildNodes[num_child_nodes-1].first - estimatedValue_Index_ChildNodes[num_child_nodes-1-i].first) / sqrt(2*(variance_ChildNodes[estimatedValue_Index_ChildNodes[num_child_nodes-1].second]+variance_ChildNodes[estimatedValue_Index_ChildNodes[num_child_nodes-1-i].second])))) + ((0.1+pow(2, -i)) / num_child_nodes);

        Prob_ChildNodes.push_back(this_child_prob);
        total_Prob += this_child_prob;
    }

    random_device rd_prob;
    mt19937 generator_prob(rd_prob());

    uniform_real_distribution<> dist_prob(0, 1);     // Generate value between 0 and 1

    double generated_prob = dist_prob(generator_prob);  // The generated probability

    double cumulated_prob_val = Prob_ChildNodes[0]/total_Prob;  // The cumulated prob value of selected child, u_0+u_1+...

    if (generated_prob <= cumulated_prob_val) {
        selected_node_ptr = parent_node_ptr->getChildNodePtr(estimatedValue_Index_ChildNodes[num_child_nodes-1].second);    // The pointer to the child node with the max prob u_0
    } else {
        for (int i = 1; i < num_child_nodes; i++) {
            cumulated_prob_val += Prob_ChildNodes[i]/total_Prob;

            if (generated_prob <= cumulated_prob_val) {
                selected_node_ptr = parent_node_ptr->getChildNodePtr(estimatedValue_Index_ChildNodes[num_child_nodes-1-i].second);
                break;
            }
        }
    }
}

// The expansion operator of MCTS
void MCTS::expansion(MCTS_Node* &parent_node_ptr, vector<MCTS_Node> &MCT) {
    // Expand the selected node by the last untried child mode
    int first_untried_child_move = parent_node_ptr->getUntriedChildMoves().back();
    parent_node_ptr->getUntriedChildMoves().pop_back();

    // The child board state
    BoardState child_boardState = parent_node_ptr->getBoardState();
    child_boardState.makeMove(first_untried_child_move);

    // Create a child node and push it to MCT
    MCT.push_back(MCTS_Node(child_boardState));

    // The address of the newly added child, assign the pointer to the parent node
    (&MCT[MCT.size()-1])->assignParentNode(parent_node_ptr);

    // Append the pointer of this child node to the parent children
    parent_node_ptr->appendChildNode(&MCT[MCT.size()-1], first_untried_child_move);

    // Update the pointer to the parent node to the pointer to the newly added child, and start the rollout process
    parent_node_ptr = &MCT[MCT.size()-1];
}

// The rollout operator of MCTS using the random policy
int MCTS::rollout_Random(MCTS_Node* &given_node_ptr) {
    random_device rd;
    mt19937 generator(rd());

    BoardState given_boardState = given_node_ptr->getBoardState();

    while (true) {
        vector<int> child_moves = given_boardState.generateChildMoves();

        if (child_moves.size() == 0) {
            // Game ends, returh the score
            return given_boardState.getScore();
        } else {
            // Select a random move and make move
            uniform_int_distribution<int> distribution_move(0, (int) child_moves.size()-1);

            given_boardState.makeMove(child_moves[distribution_move(generator)]);
        }
    }
}

// The rollout operator of MCTS using the TabuRandom policy
int MCTS::rollout_TabuRandom(MCTS_Node* &given_node_ptr) {
    random_device rd;
    mt19937 generator(rd());    // For generating a color randomly

    uniform_int_distribution<int> distribution_color(1, 5);

    int selected_color = distribution_color(generator);   // Select a color randomly

    random_device rd2;
    mt19937 generator2(rd2());   // For generating a move randomly

    random_device rd_ep;
    mt19937 generator_ep(rd_ep());

    uniform_real_distribution<> dist_prob(0, 1);     // Generate value between 0 and 1

    // epsilon-greedy to follow this policy
    double epsilon = 0.003;

    BoardState given_boardState = given_node_ptr->getBoardState();

    while (true) {
        vector<int> child_moves = given_boardState.generateChildMoves();

        if (child_moves.size() == 0) {
            // Game ends, returh the score
            return given_boardState.getScore();
        } else {
            if (dist_prob(generator_ep) < epsilon) {
                // Play a random move
                uniform_int_distribution<int> distribution_move(0, (int) child_moves.size()-1);

                given_boardState.makeMove(child_moves[distribution_move(generator2)]);
            } else {
                // Select a move to remove the block which is not the selected color
                bool madeMove = false;

                for (int i = 0; i < (int) child_moves.size(); i++) {
                    if (given_boardState.getMoveColor(child_moves[i]) != selected_color) {
                        given_boardState.makeMove(child_moves[i]);

                        madeMove = true;

                        break;
                    }
                }

                if (!madeMove) {
                    // Play the move to remove the block with the selected color
                    uniform_int_distribution<int> distribution_move(0, (int) child_moves.size()-1);

                    given_boardState.makeMove(child_moves[distribution_move(generator2)]);
                }
            }
        }
    }
}

// The rollout operator of MCTS using the TabuColorRandom policy
int MCTS::rollout_TabuColorRandom(MCTS_Node* &given_node_ptr) {
    BoardState given_boardState = given_node_ptr->getBoardState();

    int selected_color = given_boardState.getMaxColor();   // The selected color

    random_device rd_ep;
    mt19937 generator_ep(rd_ep());

    uniform_real_distribution<> dist_prob(0, 1);     // Generate value between 0 and 1

    // epsilon-greedy to follow this policy
    double epsilon = 0.003;

    random_device rd;
    mt19937 generator(rd());    // For generate a move randomly

    while (true) {
        vector<int> child_moves = given_boardState.generateChildMoves();

        if (child_moves.size() == 0) {
            // Game ends, returh the score
            return given_boardState.getScore();
        } else {
            if (dist_prob(generator_ep) < epsilon) {
                // Play a random move
                uniform_int_distribution<int> distribution_move(0, (int) child_moves.size()-1);

                given_boardState.makeMove(child_moves[distribution_move(generator)]);
            } else {
                // Select a move to remove the block which is not the selected color
                bool madeMove = false;

                for (int i = 0; i < (int) child_moves.size(); i++) {
                    if (given_boardState.getMoveColor(child_moves[i]) != selected_color) {
                        given_boardState.makeMove(child_moves[i]);

                        madeMove = true;

                        break;
                    }
                }

                if (!madeMove) {
                    // Play the move to remove the block with the selected color
                    uniform_int_distribution<int> distribution_move(0, (int) child_moves.size()-1);

                    given_boardState.makeMove(child_moves[distribution_move(generator)]);
                }
            }
        }
    }
}

// The backpropagation operator of MCTS
void MCTS::backpropagation(MCTS_Node* &given_node_ptr, int rollout_result) {
    // Update the value for the newly expanded node
    given_node_ptr->increase_NumVisits();
    given_node_ptr->increase_Results(rollout_result);
    given_node_ptr->update_TopScore(rollout_result);

    while(given_node_ptr->getParentPtr() != nullptr) {
        // Update the parent nodes until the root of the MCT
        given_node_ptr = given_node_ptr->getParentPtr();

        given_node_ptr->increase_NumVisits();
        given_node_ptr->increase_Results(rollout_result);
        given_node_ptr->update_TopScore(rollout_result);
    }
}

// Start the MCTS
void MCTS::search(int &this_topscore, double &this_avgscore) {
    // The start time
    chrono::time_point<chrono::system_clock> startClocks = chrono::system_clock::now();

    vector<MCTS_Node> MCT;  // The MCT that stores the searched nodes
    MCT.reserve(MAX_NODES_NUM);     // Reserve the memory

    MCT.push_back(MCTS_Node(boardState));   // Store the root node of the MCT

    for (int i = 0; i < MAX_NODES_NUM-1; i++) {
        MCTS_Node* selected_node_ptr = &MCT[0];  // Start from the root node

        // When the selected node has no untried child moves and it has child nodes
        while(selected_node_ptr->getNumUntriedChildMoves() == 0 && selected_node_ptr->getNumChildNodes() != 0) {
            if (selected_node_ptr->getNumVisits() < 10) {
                selection_heuristic(selected_node_ptr);
            } else {
                selection(selected_node_ptr);    // Get the child pointer with the largest UCT value
                // selection_ProgressivePruning(selected_node_ptr);    // Select the child node according to the progressive pruning strategy
            }
        }

        if (selected_node_ptr->getNumUntriedChildMoves() != 0) {
            expansion(selected_node_ptr, MCT);  // Expand one child per playout
        }

        // Run the simulation for the selected child
        // int rollout_result = rollout_Random(selected_node_ptr);   // The result of the rollout using the random policy
        // int rollout_result = rollout_TabuRandom(selected_node_ptr);   // The result of the rollout using the TabuRandom policy
        int rollout_result = rollout_TabuColorRandom(selected_node_ptr);    // The result of the rollout using the TabuColorRandom policy

        // Backpropagation
        backpropagation(selected_node_ptr, rollout_result);
    }

    // Time used in the search
    int time_used = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - startClocks).count();

    cout << "Time Used: " << time_used*0.001 << " seconds" << endl;

    cout << (&MCT[0])->getNumVisits() << endl;
    cout << (&MCT[0])->getTotalReuslt() << endl;
    cout << (&MCT[0])->getTotalSquaredResult() << endl;

    cout << "Average score: " << (double) (&MCT[0])->getTotalReuslt() / (&MCT[0])->getNumVisits() << endl;
    cout << "Top score: " << (&MCT[0])->getTopScore() << endl;

    this_topscore = (&MCT[0])->getTopScore();
    this_avgscore = (double) (&MCT[0])->getTotalReuslt() / (&MCT[0])->getNumVisits();
}
