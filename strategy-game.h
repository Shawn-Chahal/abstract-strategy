#include <iostream>
#include <vector>
#include <cmath>


class StrategyGame {
    public:

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

        std::vector<std::vector<int>> update_state(std::vector<std::vector<int>> game_state, int player, int move) {

            for (int row = game_state.size() - 1; row >= 0; row--) {
                if (game_state[row][move] == 0) {
                    game_state[row][move] = player;
                    break;
                }
            }   
            return game_state;
        }


        std::vector<int> update_available_moves(std::vector<std::vector<int>> game_state, std::vector<int> available_moves) {
            
            for (int j=0; j < available_moves.size(); j++) {
                if (game_state[0][j] > 0) {
                    available_moves[j] = 0;
                }
            }
            return available_moves;
        }

};

