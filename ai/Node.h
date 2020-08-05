#ifndef H_NODE
#define H_NODE

#include "GameBoard.h"

#include <vector>

class Node {
    private:

        const double E_PARAM = 2.0;
        const double EPSILON = 0.000001;

        int parent_node_id; // The parent_node_id of the root node is -1
        int win, loss, draw;

    public:

        int total;
        int last_result; // for backpropagation
        std::vector<int> child_node_id; // index = move, value = child node id for that move
        GameBoard *board;
        
        Node(int parent_input, GameBoard &board_ref);

        double get_score(int player_parent);
        double get_UCB1(int player_parent, int total_parent);
        void add_child(int new_child_node, int move);
        void update(int result);
};

#endif