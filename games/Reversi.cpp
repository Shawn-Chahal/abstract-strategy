#include "Reversi.h"

#include <iostream>
#include <vector>
#include <string>


std::vector<int> Reversi::check_link(std::vector<std::vector<int>> game_state, int row, int col) {
    std::vector<int> link = std::vector<int>(8, 0);
    int player = game_state[row][col];
    int opponent = switch_player(player);

    // Check right [0]
    if (col < N_COL - 2) {
        if (game_state[row][col + 1] == opponent) {
            for (int k = 2; col + k < N_COL; k++) {
                if (game_state[row][col + k] == 0) {
                    break;
                } else if (game_state[row][col + k] == player) {
                    link[0] = 1;
                    break;
                }
            }
        }
    }

    // Check up-right [1]
    if ((row > 1) && (col < N_COL - 2)) {
        if (game_state[row - 1][col + 1] == opponent) {
            for (int k = 2; (row - k >= 0) && (col + k < N_COL); k++) {
                if (game_state[row - k][col + k] == 0) {
                    break;
                } else if (game_state[row - k][col + k] == player) {
                    link[1] = 1;
                    break;
                }
            }
        }
    }

    // Check up [2]
    if (row > 1) {
        if (game_state[row - 1][col] == opponent) {
            for (int k = 2; row - k >= 0; k++) {
                if (game_state[row - k][col] == 0) {
                    break;
                } else if (game_state[row - k][col] == player) {
                    link[2] = 1;
                    break;
                }
            }
        }
    }

    // Check up-left [3]
    if ((row > 1) && (col > 1)) {
        if (game_state[row - 1][col - 1] == opponent) {
            for (int k = 2; (row - k >= 0) && (col - k >= 0); k++) {
                if (game_state[row - k][col - k] == 0) {
                    break;
                } else if (game_state[row - k][col - k] == player) {
                    link[3] = 1;
                    break;
                }
            }
        }
    }

    // Check left [4]
    if (col > 1) {
        if (game_state[row][col - 1] == opponent) {
            for (int k = 2; col - k >= 0; k++) {
                if (game_state[row][col - k] == 0) {
                    break;
                } else if (game_state[row][col - k] == player) {
                    link[4] = 1;
                    break;
                }
            }
        }
    }

    // Check down-left [5]
    if ((row < N_ROW - 2) && (col > 1)) {
        if (game_state[row + 1][col - 1] == opponent) {
            for (int k = 2; (row + k < N_ROW) && (col - k >= 0); k++) {
                if (game_state[row + k][col - k] == 0) {
                    break;
                } else if (game_state[row + k][col - k] == player) {
                    link[5] = 1;
                    break;
                }
            }
        }
    }

    // Check down [6]
    if (row < N_ROW - 2) {
        if (game_state[row + 1][col] == opponent) {
            for (int k = 2; row + k < N_ROW; k++) {
                if (game_state[row + k][col] == 0) {
                    break;
                } else if (game_state[row + k][col] == player) {
                    link[6] = 1;
                    break;
                }
            }
        }
    }


    // Check down-right [7]
    if ((row < N_ROW - 2) && (col < N_COL - 2)) {
        if (game_state[row + 1][col + 1] == opponent) {
            for (int k = 2; (row + k < N_ROW) && (col + k < N_COL); k++) {
                if (game_state[row + k][col + k] == 0) {
                    break;
                } else if (game_state[row + k][col + k] == player) {
                    link[7] = 1;
                    break;
                }
            }
        }
    }
    
    return link;
}

int Reversi::move_available(std::vector<std::vector<int>> game_state, int player, int move) {
    
    int row = move / N_COL;
    int col = move % N_COL;
    game_state[row][col] = player;
    int opponent = switch_player(player);

    // Check right [0]
    if (col < N_COL - 2) {
        if (game_state[row][col + 1] == opponent) {
            for (int k = 2; col + k < N_COL; k++) {
                if (game_state[row][col + k] == 0) {
                    break;
                } else if (game_state[row][col + k] == player) {
                    return 1;
                }
            }
        }
    }

    // Check up-right [1]
    if ((row > 1) && (col < N_COL - 2)) {
        if (game_state[row - 1][col + 1] == opponent) {
            for (int k = 2; (row - k >= 0) && (col + k < N_COL); k++) {
                if (game_state[row - k][col + k] == 0) {
                    break;
                } else if (game_state[row - k][col + k] == player) {
                    return 1;
                }
            }
        }
    }

    // Check up [2]
    if (row > 1) {
        if (game_state[row - 1][col] == opponent) {
            for (int k = 2; row - k >= 0; k++) {
                if (game_state[row - k][col] == 0) {
                    break;
                } else if (game_state[row - k][col] == player) {
                    return 1;
                }
            }
        }
    }

    // Check up-left [3]
    if ((row > 1) && (col > 1)) {
        if (game_state[row - 1][col - 1] == opponent) {
            for (int k = 2; (row - k >= 0) && (col - k >= 0); k++) {
                if (game_state[row - k][col - k] == 0) {
                    break;
                } else if (game_state[row - k][col - k] == player) {
                    return 1;
                }
            }
        }
    }

    // Check left [4]
    if (col > 1) {
        if (game_state[row][col - 1] == opponent) {
            for (int k = 2; col - k >= 0; k++) {
                if (game_state[row][col - k] == 0) {
                    break;
                } else if (game_state[row][col - k] == player) {
                    return 1;
                }
            }
        }
    }

    // Check down-left [5]
    if ((row < N_ROW - 2) && (col > 1)) {
        if (game_state[row + 1][col - 1] == opponent) {
            for (int k = 2; (row + k < N_ROW) && (col - k >= 0); k++) {
                if (game_state[row + k][col - k] == 0) {
                    break;
                } else if (game_state[row + k][col - k] == player) {
                    return 1;
                }
            }
        }
    }

    // Check down [6]
    if (row < N_ROW - 2) {
        if (game_state[row + 1][col] == opponent) {
            for (int k = 2; row + k < N_ROW; k++) {
                if (game_state[row + k][col] == 0) {
                    break;
                } else if (game_state[row + k][col] == player) {
                    return 1;
                }
            }
        }
    }


    // Check down-right [7]
    if ((row < N_ROW - 2) && (col < N_COL - 2)) {
        if (game_state[row + 1][col + 1] == opponent) {
            for (int k = 2; (row + k < N_ROW) && (col + k < N_COL); k++) {
                if (game_state[row + k][col + k] == 0) {
                    break;
                } else if (game_state[row + k][col + k] == player) {
                    return 1;
                }
            }
        }
    }
    
    return 0;
}

std::vector<int> Reversi::update_local_available_moves(int local_player) {

    std::vector<int> local_available_moves = std::vector<int>(N_MOVES, 0);

    for (int m = 0; m < N_MOVES; m++) {
        if (game_state[m / N_COL][m % N_COL] == 0) {
            local_available_moves[m] = move_available(game_state, local_player, m);
        }
    }

    return local_available_moves;
}


std::string Reversi::initialize_name() {
    return "Reversi (Othello)";
}

std::vector<double> Reversi::initialize_difficulty() {
    return {5, 15, 30, 60, 120};
}

std::vector<std::vector<int>> Reversi::initialize_game_state() {

    game_state = std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0));
    game_state[N_ROW / 2 - 1][N_COL / 2 - 1] = 2;
    game_state[N_ROW / 2 - 1][N_COL / 2    ] = 1;
    game_state[N_ROW / 2    ][N_COL / 2 - 1] = 1;
    game_state[N_ROW / 2    ][N_COL / 2    ] = 2;

    return game_state;
}

std::vector<int> Reversi::initialize_available_moves() {
    available_moves = update_available_moves(-1);
    return available_moves;
}

int Reversi::input_check(std::string user_input) {
    
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

int Reversi::input_transform(std::string user_input) {

    int row = user_input[1] - '1';
    int col = user_input[0] - 'a';
    int move = row * N_COL + col;

    return move;
}

void Reversi::print_ai_move(int move) {

    int row = move / N_COL + 1;
    char col = (move % N_COL) + 'a';

    std::cout << col << row;
}

void Reversi::print_rules() {

    std::cout << "\t" << "Occupy as many tiles as possible before both players run out of moves." << std::endl;
    std::cout << "\t" << "You may only play on an empty tile which is connected in a straight line" << std::endl;
    std::cout << "\t" << "to another one of your tiles. However, all the tiles in between your two" << std::endl;
    std::cout << "\t" << "tiles must be occupied by your opponent. The straight line can be" << std::endl;
    std::cout << "\t" << "horizontal, vertical, or diagonal. If you have no available moves," << std::endl;
    std::cout << "\t" << "your turn will be passed." << std::endl;
    std::cout << "\t" << "Each tile is represnted by an alphanumeric value." << std::endl;
    std::cout << "\t" << "E.g., if you want to play on column = a and row = 1," << std::endl; 
    std::cout << "\t" << "then input a1 when prompted." << std::endl;
}

void Reversi::print_board() {
    
    char col_index = 'a';

    std::cout << "\t" << "  ";
    
    for (int j = 0; j < N_COL; j++) {  
        
        std::cout << "  " << col_index++ << " ";
    }

    std::cout << " " << std::endl;

    std::cout << "\t" << "  |";
        for (int j = 0; j < N_COL; j++) {
            
            std::cout << "---|";
        }
    std::cout << std::endl;

    for (int i = 0; i < N_ROW; i++) {
        std::cout << "\t";

        for (int j = 0; j < N_COL; j++) {

            if (j == 0) {
                std::cout << i + 1 << " | ";
            } else {
                std::cout << "| ";
            }
            
            switch (game_state[i][j]) {
                case 0:
                    std::cout << " ";
                    break;
                case 1:
                    std::cout << get_player_marker(1);
                    break;
                case 2:
                    std::cout << get_player_marker(2);
                    break;
            }

            std::cout << " ";
        }

        std::cout << "|" << std::endl;
        
        
        std::cout << "\t" << "  |";
        for (int j = 0; j < N_COL; j++) {
            
            std::cout << "---|";
        }
        std::cout << std::endl;
    
    }
    std::cout << std::endl;
}


std::vector<std::vector<int>> Reversi::update_game_state(int move) {

    int row = move / N_COL;
    int col = move % N_COL;

    game_state[row][col] = player;

    std::vector<int> link = check_link(game_state, row, col);

    // Check right [0]
    if (link[0]) {
        for (int k = 1; col + k < N_COL; k++) {
            if (game_state[row][col + k] == player) {
                break;
            } else {
                game_state[row][col + k] = player;
            }
        }
    }

    // Check up-right [1]
    if (link[1]) {
        for (int k = 1; (row - k >= 0) && (col + k < N_COL); k++) {
            if (game_state[row - k][col + k] == player) {
                break;
            } else {
                game_state[row - k][col + k] = player;
            }
        }
    }

    // Check up [2]
    if (link[2]) {
        for (int k = 1; row - k >= 0; k++) {
            if (game_state[row - k][col] == player) {
                break;
            } else {
                game_state[row - k][col] = player;
            }
        }
    }

    // Check up-left [3]
    if (link[3]) {
        for (int k = 1; (row - k >= 0) && (col - k >= 0); k++) {
            if (game_state[row - k][col - k] == player) {
                break;
            } else {
                game_state[row - k][col - k] = player;
            }
        }
    }

    // Check left [4]
    if (link[4]) {
        for (int k = 1; col - k >= 0; k++) {
            if (game_state[row][col - k] == player) {
                break;
            } else {
                game_state[row][col - k] = player;
            }
        }
    }

    // Check down-left [5]
    if (link[5]) {
        for (int k = 1; (row + k < N_ROW) && (col - k >= 0); k++) {
            if (game_state[row + k][col - k] == player) {
                break;
            } else {
                game_state[row + k][col - k] = player;
            }
        }
    }

    // Check down [6]
    if (link[6]) {
        for (int k = 1; row + k < N_ROW; k++) {
            if (game_state[row + k][col] == player) {
                break;
            } else {
                game_state[row + k][col] = player;
            }
        }
    }

    // Check down-right [7]
    if (link[7]) {
        for (int k = 1; (row + k < N_ROW) && (col + k < N_COL); k++) {
            if (game_state[row + k][col + k] == player) {
                break;
            } else {
                game_state[row + k][col + k] = player;
            }
        }
    }
    
    return game_state;
}

int Reversi::update_result(int move) {

    int player1_score = 0;
    int player2_score = 0;

    std::vector<int> local_available_moves;

    for (int p = 1; p <= 2; p++) {
        local_available_moves = update_local_available_moves(p);

        for (int m = 0; m < N_MOVES; m++) {
            if (local_available_moves[m]) {
                return -1;
            }
        }
    }
    
    for (int i = 0; i < N_ROW; i++) {
        for (int j = 0; j < N_COL; j++) {
            switch (game_state[i][j]) {
                case 1:
                    player1_score++;
                    break;
                case 2:
                    player2_score++;
                    break;
                default:
                    break;
            }
        }
    }

    if (player1_score > player2_score) {
        return 1;
    } else if (player2_score > player1_score) {
        return 2;
    } else {
        return 0;
    }
}

int Reversi::update_player(int move) {

    int local_player = switch_player(player);
    std::vector<int> local_available_moves = update_local_available_moves(local_player);

    for (int m = 0; m < local_available_moves.size(); m++) {
        if (local_available_moves[m]) {
            return local_player;
        }
    }

    return switch_player(local_player);
}

std::vector<int> Reversi::update_available_moves(int move) {
    
    available_moves = std::vector<int>(N_MOVES, 0);

    for (int m = 0; m < N_MOVES; m++) {
        if (game_state[m / N_COL][m % N_COL] == 0) {
            available_moves[m] = move_available(game_state, player, m);
        }
    }

    return available_moves;
}
