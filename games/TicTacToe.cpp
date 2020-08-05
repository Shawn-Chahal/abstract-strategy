#include "TicTacToe.h"

#include <iostream>
#include <vector>
#include <string>


std::string TicTacToe::initialize_name() {
    return "Tic-Tac-Toe";
}

std::vector<double> TicTacToe::initialize_difficulty() {
    return {1, 2, 3, 4, 5};
}

std::vector<std::vector<int>> TicTacToe::initialize_game_state() {
    return std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0));
}

std::vector<int> TicTacToe::initialize_available_moves() {
    return std::vector<int>(N_MOVES, 1);
}

int TicTacToe::input_check(std::string user_input) {
    
    if (user_input.length() != 2) {
        return 0;
    }

    int row = user_input[1] - '1';
    int col = user_input[0] - 'a';
    int move = row * N_COL + col;

    if (row < 0 || row >= N_ROW || col < 0 || col >= N_COL ) {
        return 0;
    }

    if (move >= 0 && move < available_moves.size()) {
        return available_moves[move];
    } else {
        return 0;
    }
}

int TicTacToe::input_transform(std::string user_input) {

    int row = user_input[1] - '1';
    int col = user_input[0] - 'a';
    int move = row * N_COL + col;

    return move;
}

void TicTacToe::print_ai_move(int move) {

    int row = move / N_COL + 1;
    char col = (move % N_COL) + 'a';

    std::cout << col << row;
}

void TicTacToe::print_rules() {

    std::cout << "\t" << "Connect three consecutive tiles in a straight line." << std::endl;
    std::cout << "\t" << "The tiles can be horizontal, vertical, or diagonal." << std::endl;
    std::cout << "\t" << "Each tile is represnted by an alphanumeric value." << std::endl;
    std::cout << "\t" << "E.g., if you want to play on column = a and row = 1," << std::endl; 
    std::cout << "\t" << "then input a1 when prompted." << std::endl;
}

void TicTacToe::print_board() {
    
    char col_index = 'a';

    std::cout << "\t" << "  ";
    
    for (int j = 0; j < N_COL; j++) {  
        std::cout << "   " << col_index++ << "  ";
    }

    std::cout << " " << std::endl;
    std::cout << "\t";

    for (int j = 0; j < N_COL; j++) {
        if (j == 0) {
            std::cout  << "   ";
        } else {
            std::cout << "|";
        }
        
        std::cout << "     ";
    }

    std::cout << std::endl;

    for (int i = 0; i < N_ROW; i++) {
        std::cout << "\t";

        for (int j = 0; j < N_COL; j++) {
            if (j == 0) {
                std::cout << i + 1 << "    ";
            } else {
                std::cout << "|  ";
            }
            
            switch (game_state[i][j]) {
                case 0:
                    std::cout << " ";
                    break;
                case 1:
                    std::cout << P1_MARKER;
                    break;
                case 2:
                    std::cout << P2_MARKER;
                    break;
            }

            std::cout << "  ";
        }

        std::cout << std::endl;
        
        if (i < N_ROW - 1) {
            std::cout << "\t" << "   ";

            for (int j = 0; j < N_COL; j++) {
                if (j == N_COL - 1) {
                    std::cout << "-----";
                } else {
                    std::cout << "-----|";
                }
            }

            std::cout << std::endl;
        }
    }
    
    std::cout << "\t";

    for (int j = 0; j < N_COL; j++) {
        if (j == 0) {
            std::cout  << "   ";
        } else {
            std::cout << "|";
        }
        
        std::cout << "     ";
    }
    
    std::cout << std::endl;

    std::cout << std::endl;
}


std::vector<std::vector<int>> TicTacToe::update_game_state(int move) {
    game_state[move / N_COL][move % N_COL] = player;
    return game_state;
}

int TicTacToe::update_result(int move) {

    const int CONNECT = 3;
    int local_player, count;
    int check_draw = 0;

    /* Check horizontal */
    for (int i = 0; i < N_ROW ; i++) {
        
        local_player = game_state[i][0];

        if (local_player > 0){
            count = 1;

            for (int j = 1; j < N_COL ; j++) {
                
                if (game_state[i][j] == local_player) {
                    count++;
                } else {
                    break;
                }
            }

            if (count == CONNECT) {
                return local_player;
            }
        }
    }

    /* Check vertical */
    for (int j = 0; j < N_COL ; j++) {
        
        local_player = game_state[0][j];

        if (local_player > 0){
            count = 1;

            for (int i = 1; i < N_ROW ; i++) {
                
                if (game_state[i][j] == local_player) {
                    count++;
                } else {
                    break;
                }
            }

            if (count == CONNECT) {
                return local_player;
            }
        }
    }

    /* Check top-left to bottom-right diagonal */
    local_player = game_state[0][0];

    if (local_player > 0){
        count = 1;

        for (int k = 1; k < N_COL; k++){
            if (game_state[k][k] == local_player) {
                count++;
            
            } else {
                break;
            }
        }

        if (count == CONNECT) {
            return local_player;
        }
    }
    

    /* Check bottom-left to top-right diagonal */
    local_player = game_state[N_ROW - 1][0];

    if (local_player > 0){
        count = 1;

        for (int k = 1; k < N_COL; k++){
            if (game_state[N_ROW - 1 - k][k] == local_player) {
                count++;
            } else {
                break;
            }
        }
        
        if (count == CONNECT) {
            return local_player;
        }
    }


    for (int i = 0; i < N_ROW ; i++) {
        for (int j = 0; j < N_COL ; j++) {
            if (game_state[i][j] > 0) {
                check_draw++;
            }
        }
    }

    if (check_draw == N_MOVES) {
        /* Declare a draw */
        return 0;
    } else {
        /* Game continues */
        return -1;
    }
}

int TicTacToe::update_player(int move) {
    return switch_player(player);
}

std::vector<int> TicTacToe::update_available_moves(int move) {
    available_moves[move] = 0;
    return available_moves;
}
