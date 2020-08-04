#include "Node.h"

#include <iostream>
#include <vector>
#include <cmath>
    
Node::Node(int parent_input, int player_input, const int N_MOVES) {

    parent = parent_input;
    player = player_input;
    win = 0;
    loss = 0;
    draw = 0;
    total = 0;
    children = std::vector<int>(N_MOVES, -1);
}


void Node::add_child(int new_child_node, int move) {
    children[move] = new_child_node;
}


double Node::get_score(int player_parent) {
    if (player_parent == player) {
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

    if (result == player) {
        win++;
    } else if (result == 0) {
        draw++;
    } else {
        loss++;
    }
}
