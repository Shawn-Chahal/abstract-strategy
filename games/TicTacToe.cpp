#include "TicTacToe.h"

#include <iostream>
#include <vector>
#include <string>


// Private members

int TicTacToe::update_result(std::vector<std::vector<int>> game_state, int last_player, int last_move) {

    const int CONNECT = 3;
    int player, count;
    int check_draw = 0;

    /* Check horizontal */
    for (int i = 0; i < N_ROW ; i++) {
        
        player = game_state[i][0];

        if (player > 0){
            count = 1;

            for (int j = 1; j < N_COL ; j++) {
                
                if (game_state[i][j] == player) {
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

    /* Check vertical */
    for (int j = 0; j < N_COL ; j++) {
        
        player = game_state[0][j];

        if (player > 0){
            count = 1;

            for (int i = 1; i < N_ROW ; i++) {
                
                if (game_state[i][j] == player) {
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

    /* Check top-left to bottom-right diagonal */
    player = game_state[0][0];

    if (player > 0){
        count = 1;

        for (int k = 1; k < N_COL; k++){
            if (game_state[k][k] == player) {
                count++;
            
            } else {
                break;
            }
        }

        if (count == CONNECT) {
            return player;
        }
    }
    

    /* Check bottom-left to top-right diagonal */
    player = game_state[N_ROW - 1][0];

    if (player > 0){
        count = 1;

        for (int k = 1; k < N_COL; k++){
            if (game_state[N_ROW - 1 - k][k] == player) {
                count++;
            } else {
                break;
            }
        }
        
        if (count == CONNECT) {
            return player;
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


// Public members

void TicTacToe::initialize_board() {
    result = -1;
    player = 1;
    game_state = std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0));
    available_moves = std::vector<int>(N_MOVES, 1);
    difficulty = {1, 2, 3, 4, 5};
    line_length = 42;
}


int TicTacToe::transform_input(std::string user_input) {

    int row = user_input[1] - '1';
    int col = user_input[0] - 'a';
    int move = row * N_COL + col;

    return move;
}


int TicTacToe::check_input(std::string user_input) {
    
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


void TicTacToe::display() {
    
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


void TicTacToe::how_to_play() {

    std::cout << "\t" << "Connect three consecutive tiles in a straight line." << std::endl;
    std::cout << "\t" << "The tiles can be horizontal, vertical, or diagonal." << std::endl;
    std::cout << "\t" << "Each tile is represnted by an alphanumeric value." << std::endl;
    std::cout << "\t" << "E.g., if you want to play on column = a and row = 1," << std::endl; 
    std::cout << "\t" << "then input a1 when prompted." << std::endl;

}


void TicTacToe::ai_output(int move) {

    int row = move / N_COL + 1;
    char col = (move % N_COL) + 'a';

    std::cout << col << row;

}


void TicTacToe::print_name() {
    std::cout << NAME;
}


void TicTacToe::update(int move) {
    last_move = move;

    // Update game_state
    game_state[move / N_COL][move % N_COL] = player;

    // Update result
    result = update_result(game_state, player, move);

    // Update player
    player = switch_player(player);

    // Update available_moves
    available_moves[move] = 0;

}

