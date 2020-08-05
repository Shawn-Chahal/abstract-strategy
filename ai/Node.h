#ifndef H_NODE
#define H_NODE

#include "GameBoard.h"

#include <vector>

class Node {
    private:

        const double E_PARAM = 2.0; // Might need to be fine-tuned specifically for each game.
        const double EPSILON = 0.000001;

    public:

        int parent; // The parent of the root node is -1
        int player;
        int win;
        int loss;
        int draw;
        int total;
        int last_result; // for backpropagation
        std::vector<int> children; // index = move, value = child node id for that move
        GameBoard *board;
        
        Node(int parent_input, int player_input, const int N_MOVES, GameBoard &board_ref);

        double get_score(int player_parent);
        double get_UCB1(int player_parent, int total_parent);
        void add_child(int new_child_node, int move);
        void update(int result);
};

#endif