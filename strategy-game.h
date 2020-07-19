#include <iostream>
#include <vector>
#include <random>
#include <cmath>


class StrategyGame {
    public:

        const double S_INITIAL = 1000000.0;
        const double DECAY = 0.9;
        const char P1_MARKER = 'O';
        const char P2_MARKER = 'X';
        const std::string INDENT = "   ";


        int check_input(int move, std::vector<int> available_moves) {
        
            if (move >= 0 && move < available_moves.size()) {
                return available_moves[move];
            } else {
                return 0;
            }
        }


        int check_moves(std::vector<int> attempted_moves) {

                for (int i = 0; i < attempted_moves.size(); i++) {
                    if (attempted_moves[i] == 0) {
                        return 0;
                    }
                }

                return 1;
            }
        
        int switch_player(int player) {
            
            if (player == 1) {
                return 2;
            } else {
                return 1;
            }
        }    
};

