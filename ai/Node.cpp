#include "Node.h"
#include "GameBoard.h"

#include <iostream>
#include <vector>
#include <cmath>
    
Node::Node(int parent_input, GameBoard &board_ref) {
    
    board = board_ref.clone();
    parent_node_id = parent_input;
    win = 0;
    loss = 0;
    draw = 0;
    total = 0;
    child_node_id = std::vector<int>(board->get_num_moves(), -1);
}

void Node::add_child(int new_child_node, int move) {
    child_node_id[move] = new_child_node;
}

double Node::get_score(int player_parent) {
    if (player_parent == board->get_player()) {
        return (win + 0.5 * draw + 0.0) / (total + EPSILON);
    } else {
        return (loss + 0.5 * draw + 0.0) / (total + EPSILON);
    }
}

double Node::get_UCB1(int player_parent, int total_parent) {            
    return get_score(player_parent) + sqrt(E_PARAM * log(total_parent + 1.0 + EPSILON) / (total + EPSILON));
}

void Node::update(int result) {
    last_result = result;
    total++;

    if (result == board->get_player()) {
        win++;
    } else if (result == 0) {
        draw++;
    } else {
        loss++;
    }
}
