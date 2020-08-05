#include "ConnectFour.h"

#include <iostream>
#include <vector>
#include <string>


std::vector<std::vector<int>> ConnectFour::initialize_game_state() {
    return std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0));
}

std::vector<int> ConnectFour::initialize_available_moves() {
    return std::vector<int>(N_MOVES, 1);
}

int ConnectFour::check_input(std::string user_input) {
    if (user_input.length() != 1) {
        return 0;
    }

    int move = transform_input(user_input);

    if (move >= 0 && move < available_moves.size()) {
        return available_moves[move];
    } else {
        return 0;
    }
}

int ConnectFour::transform_input(std::string user_input) {
    return user_input[0] - '1';
}

void ConnectFour::ai_output(int move) {
    std::cout << move + 1;
}

void ConnectFour::how_to_play() {

    std::cout << "\t" << "Connect four consecutive tiles in a straight line." << std::endl;
    std::cout << "\t" << "The tiles can be horizontal, vertical, or diagonal." << std::endl;
    std::cout << "\t" << "Token are inserted from the top of the column." << std::endl;
    std::cout << "\t" << "E.g., if you want to play on column = 1," << std::endl; 
    std::cout << "\t" << "then input 1 when prompted." << std::endl;
}

void ConnectFour::print_board() {
    
    std::cout << "\t";
    
    for (int j = 0; j < N_COL; j++) {

        std::cout << "   " << j + 1 << "  ";
    }

    std::cout << " " << std::endl;
    
    std::cout << "\t";
    for (int j = 0; j < N_COL; j++) {

        std::cout << "|     ";
    }

    std::cout << "|" << std::endl;


    for (int i = 0; i < N_ROW; i++) {
        std::cout << "\t";
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
        std::cout << "\t" << "|";

        for (int j = 0; j < N_COL; j++) {
            std::cout << "-----|";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void ConnectFour::print_name() {
    std::cout << NAME;
}

void ConnectFour::initialize_board() {
    result = -1;
    player = 1;
    game_state = initialize_game_state();
    available_moves = initialize_available_moves();
    difficulty = {3, 5, 10, 15, 30};
}


std::vector<std::vector<int>> ConnectFour::update_game_state(int move) {
    for (int row = game_state.size() - 1; row >= 0; row--) {
        if (game_state[row][move] == 0) {
            game_state[row][move] = player;
            break;
        }
    }   
    return game_state;
}

int ConnectFour::update_result(int move) {

    const int CONNECT = 4;
    int count;

    for (int i = 0; i < N_ROW; i++) {
        for (int j = 0; j < N_COL; j++) {
            if (game_state[i][j] == player) {
                

                /* Check right */
                if (j <= N_COL - CONNECT) {
                    count = 1;

                    for (int k = 1; k < CONNECT; k++) {
                        if (game_state[i][j + k] == player) {
                            count++;
                        } else {
                            break;
                        }
                    }
                    
                    if (count == CONNECT) {
                        return player;
                    }
                }

                /* Check down */
                if (i <= N_ROW - CONNECT) {
                    count = 1;

                    for (int k = 1; k < CONNECT; k++) {
                        if (game_state[i + k][j] == player) {
                            count++;
                        } else {
                            break;
                        }
                    }

                    if (count == CONNECT) {
                        return player;
                    }
                }

                /* Check right-down */
                if (i <= N_ROW - CONNECT && j <= N_COL - CONNECT) {
                    count = 1;
                    
                    for (int k = 1; k < CONNECT; k++) {
                        if (game_state[i + k][j + k] == player) {
                            count++;
                        } else {
                            break;
                        }
                    }
                    
                    if (count == CONNECT) {
                        return player;
                    }
                }

                /* Check left-down */
                if (i <= N_ROW - CONNECT && j >= CONNECT - 1) {
                    count = 1;
                    
                    for (int k = 1; k < CONNECT; k++) {
                        if (game_state[i + k][j - k] == player) {
                            count++;
                        } else {
                            break;
                        }
                    }

                    if (count == CONNECT) {
                        return player;
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

int ConnectFour::update_player(int move) {
    return switch_player(player);
}

std::vector<int> ConnectFour::update_available_moves(int move) {
    if (game_state[0][move] > 0) {
        available_moves[move] = 0;
    }
    return available_moves;
}
