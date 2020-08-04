#ifndef H_STRATEGYGAME
#define H_STRATEGYGAME

#include "Node.h"
#include "GameBoard.h"

#include <vector>
#include <random>

class StrategyGame {
    private:

        int get_terminal_result(GameBoard &board_ref);
        int get_move(GameBoard &board_ref, double max_time);
        std::vector<Node> update_tree(GameBoard &board_ref, std::vector<Node> tree, int parent_node, int move);

    public:

        const double S_INITIAL = 1000000.0;
        std::default_random_engine generator;
             
        void run(GameBoard &board_ref);
};

#endif
