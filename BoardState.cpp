#include "BoardState.h"



// The default BoardState constructor
BoardState::BoardState() {;}

// The BoardState constructor
BoardState::BoardState(int random_seed) {
    initBoard(random_seed);   // Initialize the game board
}

// Initialize the game board
void BoardState::initBoard(int random_seed) {
    max_col_idx = board_size-1;   // The initial value for the maximum column index that has a colored position is 14
    score = 0;  // The initial value of the score of the board

    board_config = vector<vector<int> >(board_size, vector<int>(board_size));   // Initialize the board of the fixed size, 15 x 15

    colors_num = vector<int>(5, 0);     // Initialize the number of positions for each color

    mt19937 generator(random_seed);

    uniform_int_distribution<int> distribution(1,5);

    for (int row_i = 0; row_i < board_size; row_i++) {
        for (int col_j = 0; col_j < board_size; col_j++) {
            // The five colors in the game board are represented by the integers from 1 to 5
            board_config[row_i][col_j] = distribution(generator); // Select an integer from 1 to 5 randomly to fill this position

            colors_num[board_config[row_i][col_j]-1] += 1;  // Increase the corresponding color number by 1
        }
    }
}

// Generate child moves for the game board. Each child move represents a block with the same color (size >= 2).
// And it is represented by one of its colored positions which is an integer indicating the position in the board.
// The position integer equals row_idx*100 + col_idx. And to convert this integer to row_idx and col_idx: row_idx = (int) position_int / 100; col_idx = position_int - row_idx*100
vector<int> BoardState::generateChildMoves() {
    vector<int> childMoves;     // The vector of child moves
    bitset<board_size*board_size> ifChecked;    // A bitset to determine if a position in the board has been checked. 1: Checked; 0: Not chekced

    // Iterate the board from the min_row_idx row until the max_col_idx column
    for (int row_i = 0; row_i < board_size; row_i++) {
        for (int col_j = 0; col_j <= max_col_idx; col_j++) {
            if (!ifChecked[row_i*board_size+col_j] && board_config[row_i][col_j] != 0) {
                // When the colored position is not checked, find the orthogonally connected positions with the same color
                bool isBlock = find_connectedBlock(ifChecked, row_i, col_j);

                if (isBlock) {
                    // This position is inside a block of the same color with size >= 2
                    childMoves.push_back(row_i*100 + col_j);
                }
            }
        }
    }

    return childMoves;
}

// Find the orthogonally connected positions with the same color, set the ifChecked bit of connected positions of the given initial position to 1
// Return true, if the size of the block > 2. Otherwise, return false
bool BoardState::find_connectedBlock(bitset<board_size*board_size> &ifChecked, const int &row_i, const int &col_j) {
    int block_size = 0;     // The number of orthogonally connected positions with the same color
    int color_int = board_config[row_i][col_j];

    ifChecked.set(row_i*board_size+col_j);  // Set the ifChecked bit of the initial given position to 1

    queue<int> uncheckedPositions;  // Store the position that has not been checked neighbors

    uncheckedPositions.push(row_i*100 + col_j);     // The position integer equals row_idx*100 + col_idx.

    while (!uncheckedPositions.empty()) {
        int position_int = uncheckedPositions.front();   // The position with unchecked neighbors
        uncheckedPositions.pop();

        block_size++;   // Increase the block_size by 1

        // Convert the position integer to row_idx and col_idx: row_idx = (int) position_int / 100; col_idx = position_int - row_idx*100
        int this_position_row_i = (int) position_int / 100;
        int this_position_col_j = position_int - this_position_row_i*100;

        // Check the neighbors of this position
        if (this_position_row_i-1 >= 0) {
            // The up neighbor
            if (!ifChecked[(this_position_row_i-1)*board_size+this_position_col_j] && board_config[this_position_row_i-1][this_position_col_j] == color_int) {
                // This up neighbor is not checked and has the same color
                ifChecked.set((this_position_row_i-1)*board_size+this_position_col_j);  // Now the up neighbor is checked
                uncheckedPositions.push((this_position_row_i-1)*100 + this_position_col_j);     // Push to the queue to check its neighbors
            }
        }

        if (this_position_row_i+1 < board_size) {
            // The down neighbor
            if (!ifChecked[(this_position_row_i+1)*board_size+this_position_col_j] && board_config[this_position_row_i+1][this_position_col_j] == color_int) {
                // This down neighbor is not checked and has the same color
                ifChecked.set((this_position_row_i+1)*board_size+this_position_col_j);  // Now the down neighbor is checked
                uncheckedPositions.push((this_position_row_i+1)*100 + this_position_col_j);     // Push to the queue to check its neighbors
            }
        }

        if (this_position_col_j-1 >= 0) {
            // The left neighbor
            if (!ifChecked[this_position_row_i*board_size+this_position_col_j-1] && board_config[this_position_row_i][this_position_col_j-1] == color_int) {
                // This left neighbor is not checked and has the same color
                ifChecked.set(this_position_row_i*board_size+this_position_col_j-1);  // Now the left neighbor is checked
                uncheckedPositions.push(this_position_row_i*100 + this_position_col_j-1);     // Push to the queue to check its neighbors
            }
        }

        if (this_position_col_j+1 < board_size) {
            // The right neighbor
            if (!ifChecked[this_position_row_i*board_size+this_position_col_j+1] && board_config[this_position_row_i][this_position_col_j+1] == color_int) {
                // This right neighbor is not checked and has the same color
                ifChecked.set(this_position_row_i*board_size+this_position_col_j+1);  // Now the right neighbor is checked
                uncheckedPositions.push(this_position_row_i*100 + this_position_col_j+1);     // Push to the queue to check its neighbors
            }
        }
    }

    if (block_size >= 2) {
        return true;    // A block of the same color with size >= 2
    } else {
        return false;
    }
}

// Make the move, given a valid position integer
void BoardState::makeMove(const int &init_position_int) {
    // Convert the position integer to row_idx and col_idx: row_idx = (int) position_int / 100; col_idx = position_int - row_idx*100
    int init_position_row_i = (int) init_position_int / 100;
    int init_position_col_j = init_position_int - init_position_row_i*100;

    unordered_map<int, int> blockCol_MaxRowIdx;   // Key: the column index of the block, Value: the max row index of the block in this column
    unordered_map<int, int>::iterator col_it;

    int removed_block_size = 0;     // The size of the removed block

    int color_int = board_config[init_position_row_i][init_position_col_j];     // The initial color of the given position

    board_config[init_position_row_i][init_position_col_j] = 0;   // Uncolored the given position (equals 0)

    removed_block_size += 1;

    colors_num[color_int-1] -= 1;   // Decrease the corresponding color number by 1

    queue<int> uncheckedPositions;  // Store the position that has not been checked neighbors

    uncheckedPositions.push(init_position_int);

    while (!uncheckedPositions.empty()) {
        int position_int = uncheckedPositions.front();   // The position with unchecked neighbors
        uncheckedPositions.pop();

        // Convert the position integer to row_idx and col_idx: row_idx = (int) position_int / 100; col_idx = position_int - row_idx*100
        int this_position_row_i = (int) position_int / 100;
        int this_position_col_j = position_int - this_position_row_i*100;

        // Check if this column is recorded
        col_it = blockCol_MaxRowIdx.find(this_position_col_j);

        if (col_it != blockCol_MaxRowIdx.end()) {
            // Update the max row index
            int this_col_max_row_idx = col_it->second;


            if (this_position_row_i > this_col_max_row_idx) {
                col_it->second = this_position_row_i;    // Update the max row index for this column
            }
        } else {
            // Record this column info
            blockCol_MaxRowIdx.insert(pair<int, int>(this_position_col_j, this_position_row_i));
        }

        // Check the neighbors of this position
        if (this_position_row_i-1 >= 0) {
            // The up neighbor
            if (board_config[this_position_row_i-1][this_position_col_j] == color_int) {
                // This up neighbor has the same color
                board_config[this_position_row_i-1][this_position_col_j] = 0;   // Uncolored the up neighbor

                removed_block_size += 1;

                colors_num[color_int-1] -= 1;   // Decrease the corresponding color number by 1

                uncheckedPositions.push((this_position_row_i-1)*100 + this_position_col_j);     // Push to the queue to check its neighbors
            }
        }

        if (this_position_row_i+1 < board_size) {
            // The down neighbor
            if (board_config[this_position_row_i+1][this_position_col_j] == color_int) {
                // This down neighbor has the same color
                board_config[this_position_row_i+1][this_position_col_j] = 0;   // Uncolored the down neighbor

                removed_block_size += 1;

                colors_num[color_int-1] -= 1;   // Decrease the corresponding color number by 1

                uncheckedPositions.push((this_position_row_i+1)*100 + this_position_col_j);     // Push to the queue to check its neighbors
            }
        }

        if (this_position_col_j-1 >= 0) {
            // The left neighbor
            if (board_config[this_position_row_i][this_position_col_j-1] == color_int) {
                // This left neighbor has the same color
                board_config[this_position_row_i][this_position_col_j-1] = 0;   // Uncolored the left neighbor

                removed_block_size += 1;

                colors_num[color_int-1] -= 1;   // Decrease the corresponding color number by 1

                uncheckedPositions.push(this_position_row_i*100 + this_position_col_j-1);     // Push to the queue to check its neighbors
            }
        }

        if (this_position_col_j+1 < board_size) {
            // The right neighbor
            if (board_config[this_position_row_i][this_position_col_j+1] == color_int) {
                // This right neighbor has the same color
                board_config[this_position_row_i][this_position_col_j+1] = 0;   // Uncolored the right neighbor

                removed_block_size += 1;

                colors_num[color_int-1] -= 1;   // Decrease the corresponding color number by 1

                uncheckedPositions.push(this_position_row_i*100 + this_position_col_j+1);     // Push to the queue to check its neighbors
            }
        }
    }

    // Update the score of the board
    score += pow(removed_block_size-2, 2);

    // Move the colored pieces above the uncolored block down, if empty columns appear, move the colored pieces on the right of the empty to the left to fill the empty columns
    compactBoard(blockCol_MaxRowIdx);
}

// Move the colored pieces above the uncolored block down, if empty columns appear, move the colored pieces on the right of the empty to the left to fill the empty columns
void BoardState::compactBoard(unordered_map<int, int> &blockCol_MaxRowIdx) {
    int block_min_emp_col_idx = -1;     // The min empty column index of the block

    for (auto it = blockCol_MaxRowIdx.begin(); it != blockCol_MaxRowIdx.end(); it++) {
        int max_emp_row_idx = it->second;     // The max empty row index that the colored piece should be moved to

        for (int this_row_i = it->second-1; this_row_i >= 0; this_row_i--) {
            // Check the pieces above the max row of this column
            if (board_config[this_row_i][it->first] != 0) {
                // Move this colored piece down
                board_config[max_emp_row_idx][it->first] = board_config[this_row_i][it->first];
                board_config[this_row_i][it->first] = 0;    // Uncolor the original position
                max_emp_row_idx--;  // Decrease the max empty row index
            }
        }

        // Check if this column is empty
        if (board_config[board_size-1][it->first] == 0) {
            // Update the min empty column index
            if (it->first < block_min_emp_col_idx || block_min_emp_col_idx == -1) {
                block_min_emp_col_idx = it->first;
            }
        }
    }

    if (block_min_emp_col_idx != -1) {
        // Move all columns on the right of the min empty column to left to fill the empty columns
        for (int col_j = block_min_emp_col_idx+1; col_j <= max_col_idx; col_j++) {
            for (int row_i = board_size-1; row_i >= 0; row_i--) {
                if (board_config[row_i][col_j] == 0) {
                    // Above is empty, check if this column is initially empty
                    if (row_i == board_size-1) {
                        ;   // Do not increase the min empty column index
                    } else {
                        block_min_emp_col_idx++;
                    }
                    break;
                }

                // Move this piece to the min empty column
                board_config[row_i][block_min_emp_col_idx] = board_config[row_i][col_j];
                board_config[row_i][col_j] = 0;     // Uncolor the original position

                if (row_i == 0) {
                    block_min_emp_col_idx++;    // Finish check the whole column
                }
            }
        }

        // Update the max_col_idx (the max column index with colored positions)
        max_col_idx = block_min_emp_col_idx - 1;
    }
}

// Given a move, get the color of the removed block
int BoardState::getMoveColor(const int &init_position_int) {
    // Convert the position integer to row_idx and col_idx: row_idx = (int) position_int / 100; col_idx = position_int - row_idx*100
    int init_position_row_i = (int) init_position_int / 100;
    int init_position_col_j = init_position_int - init_position_row_i*100;

    // The initial color of the given position
    return board_config[init_position_row_i][init_position_col_j];
}

// Get the score of the game board
int BoardState::getScore() {
    return score;
}

// Get the color with the largest number of positions
int BoardState::getMaxColor() {
    int maxIndex = 0;
    int maxNum = colors_num[maxIndex];

    for (int i = 1; i < 5; i++) {
        if (colors_num[i] > maxNum) {
            maxIndex = i;
            maxNum = colors_num[i];
        }
    }

    return maxIndex+1;  // The number of the color with the largest number of positions
}

// Get the heuristic score
int BoardState::getHeuristicScore() {
    // Return the heuristic score = current score + (colored positions num - 2) ^2 for the max color
    int heuristic_score = score;

    int maxColor = getMaxColor();

    heuristic_score += pow(colors_num[maxColor-1] - 2, 2);  // Assume colored positions for the max color are all connected

    return heuristic_score;
}

// Get the max possible score
int BoardState::getMaxPossibleScore() {
    int max_possible_score = score;

    for (int i = 0; i < 5; i++) {
        max_possible_score += pow(colors_num[i]-2, 2);
    }

    return max_possible_score;
}

// Print the game board
void BoardState::printBoard() {
    cout << "max_col_idx: " << max_col_idx << endl;

    cout << "Game Board: " << endl;

    for (int row_i = 0; row_i < board_size; row_i++) {
        for (int col_j = 0; col_j < board_size; col_j++) {
            cout << board_config[row_i][col_j];
        }
        cout << endl;
    }

    for (int i = 0; i < 5; i++) {
        cout << "Number of Color " << i+1 << ": " << colors_num[i] << endl;
    }

    cout << "Current Score: " << score << endl;
}
