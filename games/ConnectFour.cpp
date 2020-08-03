#include "ConnectFour.h"

#include <iostream>
#include <vector>
#include <string>

// Private members

int ConnectFour::update_result(std::vector<std::vector<int>> game_state, int last_player, int last_move) {

    const int CONNECT = 4;
    int count;

    for (int i = 0; i < N_ROW; i++) {
        for (int j = 0; j < N_COL; j++) {
            if (game_state[i][j] == last_player) {
                

                /* Check right */
                if (j <= N_COL - CONNECT) {
                    count = 1;

                    for (int k = 1; k < CONNECT; k++) {
                        if (game_state[i][j + k] == last_player) {
                            count++;
                        } else {
                            break;
                        }
                    }
                    
                    if (count == CONNECT) {
                        return last_player;
                    }
                }

                /* Check down */
                if (i <= N_ROW - CONNECT) {
                    count = 1;

                    for (int k = 1; k < CONNECT; k++) {
                        if (game_state[i + k][j] == last_player) {
                            count++;
                        } else {
                            break;
                        }
                    }

                    if (count == CONNECT) {
                        return last_player;
                    }
                }

                /* Check right-down */
                if (i <= N_ROW - CONNECT && j <= N_COL - CONNECT) {
                    count = 1;
                    
                    for (int k = 1; k < CONNECT; k++) {
                        if (game_state[i + k][j + k] == last_player) {
                            count++;
                        } else {
                            break;
                        }
                    }
                    
                    if (count == CONNECT) {
                        return last_player;
                    }
                }

                /* Check left-down */
                if (i <= N_ROW - CONNECT && j >= CONNECT - 1) {
                    count = 1;
                    
                    for (int k = 1; k < CONNECT; k++) {
                        if (game_state[i + k][j - k] == last_player) {
                            count++;
                        } else {
                            break;
                        }
                    }

                    if (count == CONNECT) {
                        return last_player;
                    }
                }
            }
        }
    }

    for (int j = 0 ; j < N_COL; j++) {
        if (game_state[0][j] == 0) {
            return -1;
        }
    }
    
    return 0;

}


// Public members

int ConnectFour::transform_input(std::string user_input) {

    int move = user_input[0] - '1';

    return move;
}


int ConnectFour::check_input(std::string user_input) {
    
    if (user_input.length() != 1) {
        return 0;
    }

    int move = user_input[0] - '1';

    if (move >= 0 && move < available_moves.size()) {
        return available_moves[move];
    } else {
        return 0;
    }
}


void ConnectFour::initialize_board() {
    result = -1;
    player = 1;
    game_state = std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0));
    available_moves = std::vector<int>(N_MOVES, 1);
    difficulty = {3, 5, 10, 15, 30};
}


void ConnectFour::display() {
    
    std::cout << INDENT;
    
    for (int j = 0; j < N_COL; j++) {

        std::cout << "   " << j + 1 << "  ";
    }

    std::cout << " " << std::endl;
    
    std::cout << INDENT;
    for (int j = 0; j < N_COL; j++) {

        std::cout << "|     ";
    }

    std::cout << "|" << std::endl;


    for (int i = 0; i < N_ROW; i++) {
        std::cout << INDENT;
        for (int j = 0; j < N_COL; j++) {
            switch (game_state[i][j]) {
                case 0:
                    std::cout << "|     ";
                    break;
                case 1:
                    std::cout << "|  " << P1_MARKER << "  ";
                    break;
                case 2:
                    std::cout << "|  " << P2_MARKER << "  ";
                    break;
            }
        }

        std::cout << "|" << std::endl;
        std::cout << INDENT << "|";

        for (int j = 0; j < N_COL; j++) {
            std::cout << "-----|";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}


void ConnectFour::how_to_play() {

    std::cout << INDENT << "Connect four consecutive tiles in a straight line." << std::endl;
    std::cout << INDENT << "The tiles can be horizontal, vertical, or diagonal." << std::endl;
    std::cout << INDENT << "Token are inserted from the top of the column." << std::endl;
    std::cout << INDENT << "E.g., if you want to play on column = 1," << std::endl; 
    std::cout << INDENT << "then input 1 when prompted." << std::endl;

}


void ConnectFour::ai_output(int move) {
    std::cout << move + 1;
}


void ConnectFour::print_name() {
    std::cout << NAME;
}


void ConnectFour::update(int move) {
    last_move = move;
                
    // Update game_state
    for (int row = game_state.size() - 1; row >= 0; row--) {
        if (game_state[row][move] == 0) {
            game_state[row][move] = player;
            break;
        }
    }  

    // Update result
    result = update_result(game_state, player, move);

    // Update player
    player = switch_player(player);
    
    // Update available_moves
    if (game_state[0][move] > 0) {
        available_moves[move] = 0;
    }

}

