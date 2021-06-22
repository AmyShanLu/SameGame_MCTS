#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <random>
#include <math.h>
#include <bitset>

using namespace std;



class BoardState {
    private:
        static const int board_size = 15;    // The board of the same game is 15 x 15
        vector<vector<int> > board_config;   // The board configration

        vector<int> colors_num;     // The number of positions for each color

        int max_col_idx;    // The maximum column index that has a colored position. Initially equals to 14

        int score;  // The score of the board state

    public:
        BoardState();   // The default constructor
        BoardState(int random_seed);   // The BoardState constructor
        void initBoard(int random_seed);   // Initialize the game board
        // Generate child moves for the game board. Each child move represents a block with the same color (size >= 2)
        // and it is represented by one of its colored positions which is an integer indicating the position in the board
        vector<int> generateChildMoves();
        // Find the orthogonally connected positions with the same color, set the ifChecked bit of connected positions of the given initial position to 1
        // Return true, if the size of the block > 2. Otherwise, return false
        bool find_connectedBlock(bitset<board_size*board_size> &ifChecked, const int &row_i, const int &col_j);
        // Make the move, given a valid position integer
        void makeMove(const int &init_position_int);
        // Move the colored pieces above the uncolored block down, if empty columns appear, move the colored pieces on the right of the empty to the left to fill the empty columns
        void compactBoard(unordered_map<int, int> &blockCol_MaxRowIdx);
        // Given a move, get the color of the removed block
        int getMoveColor(const int &init_position_int);
        int getScore();     // Get the score of the game board
        int getMaxColor();  // Get the color with the largest number of positions
        int getHeuristicScore();   // Get the heuristic score
        int getMaxPossibleScore();  // Get the max possible score
        void printBoard();     // Print the game board
};
