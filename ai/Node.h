#ifndef H_NODE
#define H_NODE

#include <iostream>
#include <vector>
#include <cmath>


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
    
    
        Node(int parent_input, int player_input, const int N_MOVES) {

            parent = parent_input;
            player = player_input;
            win = 0;
            loss = 0;
            draw = 0;
            total = 0;
            children = std::vector<int>(N_MOVES, -1);
        }


        void add_child(int new_child_node, int move) {

            children[move] = new_child_node;
        }


        double get_score(int player_parent) {

            double score;

            if (player_parent == player) {
                score = (win + 0.5 * draw + 0.0) / (total + EPSILON);
            } else {
                score = (loss + 0.5 * draw + 0.0) / (total + EPSILON);
            }

            return score;
        }


        double get_UCB1(int player_parent, int total_parent) {

            double score = get_score(player_parent);
            
            return score + sqrt(E_PARAM * log(total_parent + 1.0 + EPSILON) / (total + EPSILON));
        }


        void update(int result) {
            
            last_result = result;

            if (result == player) {
                win++;
            } else if (result == 0) {
                draw++;
            } else {
                loss++;
            }

            total++;
        }


};

#endif