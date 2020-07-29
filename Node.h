#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <string>


class Node {

    public:

    int parent;
    int player;
    int win;
    int loss;
    int draw;
    int total;
    std::vector<int> children;

    Node(int parent_input, int player_input) {
        parent = parent_input;
        player = player_input;
        win = 0;
        loss = 0;
        draw = 0;
        total = 0;
    }

    void add_child (int child) {
        children.push_back(child);
    }

    int children_size () {
        return children.size();
    }






};