#include "Hex.h"

#include <iostream>
#include <vector>
#include <string>

void Hex::print_spaces(int n_spaces) {

    for (int i = 0; i < n_spaces; i++) {
        std::cout << " ";
    }
}

std::string Hex::print_tile(int player) {
    std::string tile = "   ";

    switch (player) {
        case 0:
            return tile;
            break;
        
        case 1:
            tile[0] = get_player_marker(1);
            tile[2] = get_player_marker(1);
            return tile;
            break;

        case 2:
            tile[0] = get_player_marker(2);
            tile[2] = get_player_marker(2);
            return tile;
            break;
        
        default:
            return "err";
            break;
    }

    
}

int Hex::check_link(std::vector<std::vector<int>> game_state, int player, std::vector<std::vector<int>> link_history, int tile_row, int tile_col) {
    
    link_history[tile_row][tile_col] = 1;

    int link_1 = 0;
    int link_2 = 0;       
    
    if ((player == 1) && (tile_col == 0)) {
        link_1 = 1;
    }

    if ((player == 1) && (tile_col == N_COL - 1)) {
        link_2 = 2;
    }
    
    if ((player == 2) && (tile_row == 0)) {
        link_1 = 1;
    }

    if ((player == 2) && (tile_row == N_ROW - 1)) {
        link_2 = 2;
    }

    // Check position 0
    if ((tile_row > 0) && (tile_col < N_COL - 1)) {
        if (game_state[tile_row - 1][tile_col + 1] == player) {
            if (!link_history[tile_row - 1][tile_col + 1]) {
                switch (check_link(game_state, player, link_history, tile_row - 1, tile_col + 1)) {
                    case 1:
                        link_1 = 1;
                        break;
                    case 2:
                        link_2 = 2;
                        break;
                    case 3:
                        return 3;
                        break;
                    default:
                        break;
                }
            }
        }
    }


    if (link_1 + link_2 == 3) {
        return 3;
    }


    // Check position 1
    if (tile_row > 0) {
        if (game_state[tile_row - 1][tile_col] == player) {
            if (!link_history[tile_row - 1][tile_col]) {
                switch (check_link(game_state, player, link_history, tile_row - 1, tile_col)) {
                    case 1:
                        link_1 = 1;
                        break;
                    case 2:
                        link_2 = 2;
                        break;
                    case 3:
                        return 3;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    if (link_1 + link_2 == 3) {
        return 3;
    }

    // Check position 2
    if (tile_col > 0) {
        if (game_state[tile_row][tile_col - 1] == player) {
            if (!link_history[tile_row][tile_col - 1]) {
                switch (check_link(game_state, player, link_history, tile_row, tile_col - 1)) {
                    case 1:
                        link_1 = 1;
                        break;
                    case 2:
                        link_2 = 2;
                        break;
                    case 3:
                        return 3;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    if (link_1 + link_2 == 3) {
        return 3;
    }

    // Check position 3
    if ((tile_row < N_ROW - 1) && (tile_col > 0)) {
        if (game_state[tile_row + 1][tile_col - 1] == player) {
            if (!link_history[tile_row + 1][tile_col - 1]) {
                switch (check_link(game_state, player, link_history, tile_row + 1, tile_col - 1)) {
                    case 1:
                        link_1 = 1;
                        break;
                    case 2:
                        link_2 = 2;
                        break;
                    case 3:
                        return 3;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    if (link_1 + link_2 == 3) {
        return 3;
    }

    // Check position 4
    if (tile_row < N_ROW - 1) {
        if (game_state[tile_row + 1][tile_col] == player) {
            if (!link_history[tile_row + 1][tile_col]) {
                switch (check_link(game_state, player, link_history, tile_row + 1, tile_col)) {
                    case 1:
                        link_1 = 1;
                        break;
                    case 2:
                        link_2 = 2;
                        break;
                    case 3:
                        return 3;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    if (link_1 + link_2 == 3) {
        return 3;
    }

    // Check position 5
    if (tile_col < N_COL - 1) {
        if (game_state[tile_row][tile_col + 1] == player) {
            if (!link_history[tile_row][tile_col + 1]) {
                switch (check_link(game_state, player, link_history, tile_row, tile_col + 1)) {
                    case 1:
                        link_1 = 1;
                        break;
                    case 2:
                        link_2 = 2;
                        break;
                    case 3:
                        return 3;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    if (link_1 + link_2 == 3) {
        return 3;
    }

    return link_1 + link_2;

}


std::string Hex::initialize_name() {
    return "Hex (7 x 7)";
}

std::vector<double> Hex::initialize_difficulty() {
    return {5, 15, 30, 60, 120};
}

std::vector<std::vector<int>> Hex::initialize_game_state() {
    return std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0));
}

std::vector<int> Hex::initialize_available_moves() {
    return std::vector<int>(N_MOVES, 1);
}

int Hex::input_check(std::string user_input) {       
    if (user_input.length() != 3) {
        return 0;
    }

    int row = 10 * (user_input[1] - '0') + (user_input[2] - '0') - 1;
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

int Hex::input_transform(std::string user_input) {

    int row = 10 * (user_input[1] - '0') + (user_input[2] - '0') - 1;
    int col = user_input[0] - 'a';
    int move = row * N_COL + col;

    return move;
}

void Hex::print_ai_move(int move) {

    int row = move / N_COL + 1;
    char col = (move % N_COL) + 'a';

    std::cout << col;
    
    if (row < 10) {
        std::cout << 0 << row;
    } else {
        std::cout << row;
    }
}

void Hex::print_rules() {

    std::cout << "\t" << "Link the two sides of the board maching your token" << std::endl;
    std::cout << "\t" << "before your opponent. You may play on any empty tile." << std::endl;
    std::cout << "\t" << "Each tile is represnted by an alphanumeric value." << std::endl;
    std::cout << "\t" << "E.g., if you want to play on column = a and row = 01," << std::endl; 
    std::cout << "\t" << "then input a01 when prompted." << std::endl;
    std::cout << "\t" << "Pay careful attention to the row numbers as the game is" << std::endl;
    std::cout << "\t" << "played on a hexagonal grid in the shape of a rhombus." << std::endl;
}

void Hex::print_board() {
    
    char col_index = 'a';
    int n_spaces = 2;

    std::cout << "\t" << "   |XXXXXXX" << std::endl;
    std::cout << "\t" << "   |OXXX   XXXX" << std::endl;

    std::cout << "\t" << "   |OOX  " << col_index++ << "  XXXXXX" << std::endl;
    std::cout << "\t" << "   |OOO_____XXX   XXXX" << std::endl;
    
    for (int i = 0; i < N_ROW; i++) {

        // Line 1
        std::cout << "\t";
        if (i + 1 < 10) {
            std::cout << 0 << i + 1 << " ";
        } else if (i + 1 < 100) {
            std::cout << i + 1 << " ";
        } else {
            std::cout << i + 1;
        }

        std::cout << "|OO/     ";

        for (int j = 0; (j < i) && (j < N_COL / 2); j++) {

            std::cout << "\\  " << print_tile(game_state[i - 1 - j][2 * j + 1]) << "  /     ";
        }

        std::cout << "\\";

        if (col_index - 'a' < N_COL) {
            std::cout << "X  " << col_index++ << "  XXXXXX";
        } else if (i >= N_COL / 2) {
            std::cout << "OO|";
        }
        
        std::cout << std::endl;
        

        // Line 2
        std::cout << "\t";
        std::cout << "   |O/  " << print_tile(game_state[i][0]) << "  ";

        for (int j = 0; (j < i) && (j < N_COL / 2); j++) {
            std::cout << "\\_____/  " << print_tile(game_state[i - 1 - j][2 * j + 2]) << "  ";
        }

        std::cout << "\\";

        if (col_index - 'a' < N_COL) {
            std::cout << "_____XXX   XXX";
            if (col_index - 'a' == N_COL - 1) {
                std::cout << "O|";
            } else {
                std::cout << "X";
            }
        } else if (i >= N_COL / 2) {
            std::cout << "O|";
        }
        
        std::cout <<std::endl;


        // Line 3
        std::cout << "\t";
        std::cout << "   |O\\  " << print_tile(game_state[i][0]) << "  ";

        for (int j = 0; (j < i) && (j < N_COL / 2); j++) {

            std::cout << "/     \\  " << print_tile(game_state[i - 1 - j][2 * j + 2]) << "  "; //
        }

        std::cout << "/";

        if (col_index - 'a' < N_COL) {
            std::cout << "     \\X  " << col_index++ << "  X";
            if (col_index - 'a' == N_COL) {
                std::cout << "OO|";
            } else {
                std::cout << "XXXXX";
            }
            
        } else if (i >= N_COL / 2) {
            std::cout << "O|";
        }
        
        std::cout <<std::endl;


        // Line 4
        std::cout << "\t";
        std::cout << "   |OO\\_____/";

        for (int j = 0; (j < i) && (j < N_COL / 2); j++) {
            std::cout << "  " << print_tile(game_state[i - j][2 * j + 1]) << "  \\_____/";
        }

        
        if (col_index - 'a' < N_COL) {
            std::cout << "  " << print_tile(game_state[0][2 * i + 1]) << "  \\_____XXX   XXXX"; 
        } else if (col_index - 'a' == N_COL) {
            std::cout << "  " << print_tile(game_state[0][2 * i + 1]) << "  \\_____OOO|";
            col_index++;
        } else if (i >= N_COL / 2) {
            if (i + 1 - N_COL / 2 < 10) {
                std::cout << "OO| " << 0 << i + 1 - N_COL / 2;
            } else if (i + 1 < 100) {
                std::cout << "OO| " << i + 1 - N_COL / 2;
            } else {
                std::cout << "OO|" << i + 1 - N_COL / 2;
            }
        }

        std::cout <<std::endl;
    
    }



    for (int i = 0; i < N_ROW / 2; i++) {
        
        // Line 1
        std::cout << "\t";
        n_spaces +=4;
        print_spaces(n_spaces);
        std::cout << "XXXXXX\\";

        for (int j = i; j < N_COL / 2; j++) {
            std::cout << "  " << print_tile(game_state[N_ROW - 1 - (j - i)][2 * j + 1]) << "  /     \\";
        }

        std::cout << "OO|" << std::endl;


        // Line 2
        std::cout << "\t";
        n_spaces +=3;
        print_spaces(n_spaces);
        std::cout << "XXXX\\";

        for (int j = i; j < N_COL / 2; j++) {
            std::cout << "_____/  " << print_tile(game_state[N_ROW - 1 - (j - i)][2 * j + 2]) << "  \\";
        }

        std::cout << "O|" << std::endl;


        // Line 3
        std::cout << "\t";
        n_spaces +=4;
        print_spaces(n_spaces);
        std::cout << "XXXXXX\\";

        for (int j = i; j < N_COL / 2 - 1; j++) {
            std::cout << "  " << print_tile(game_state[N_ROW - 1 - (j - i)][2 * j + 2]) << "  /     \\";
        }

        std::cout << "  " << print_tile(game_state[N_ROW - 1 - (N_COL / 2 - 1 - i)][N_COL - 1]) << "  /O|" << std::endl;


        // Line 4
        std::cout << "\t";
        n_spaces +=3;
        print_spaces(n_spaces);
        std::cout << "XXXX\\";

        for (int j = i; j < N_COL / 2 - 1; j++) {
            std::cout << "_____/  " << print_tile(game_state[N_ROW - 1 - (j - i)][2 * j + 3]) << "  \\";
        }

        std::cout << "_____/OO|";

        if (i + 2 + N_COL / 2 < 10) {
            std::cout << " " << 0 << i + 2 + N_COL / 2;
        } else if (i + 2 + N_COL / 2 < 100) {
            std::cout << " " << i + 2 + N_COL / 2;
        } else {
            std::cout << "" << i + 2 + N_COL / 2;
        }

        std::cout << std::endl;
    
    }
    
    std::cout << "\t";
    n_spaces +=4;
    print_spaces(n_spaces);
    std::cout << "XXXXXXOOO|" << std::endl;
}


std::vector<std::vector<int>> Hex::update_game_state(int move) {
    game_state[move / N_COL][move % N_COL] = player;
    return game_state;
}

int Hex::update_result(int move) {

    if (check_link(game_state, player, std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0)), move / N_COL, move % N_COL) == 3) {
        return player;
    }

    for (int i = 0 ; i < N_ROW; i++) {
        for (int j = 0 ; j < N_COL; j++) {
            if (game_state[i][j] == 0) {
                return -1;
            }
        }
    }

    return 0;
}

int Hex::update_player(int move) {
    return switch_player(player);
}

std::vector<int> Hex::update_available_moves(int move) {
    available_moves[move] = 0;
    return available_moves;
}
