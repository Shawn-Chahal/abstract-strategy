#include <iostream>
#include <vector>
#include <random>
#include <cmath>


class Hex: public OneStepGame {
    private:

        void print_spaces(int n_spaces) {

            for (int i = 0; i < n_spaces; i++) {
                std::cout << " ";
            }
        }


        std::string print_tile(int player) {
            std::string tile = "   ";

            switch (player) {
                case 0:
                    return tile;
                    break;
                
                case 1:
                    tile[0] = P1_MARKER;
                    tile[2] = P1_MARKER;
                    return tile;
                    break;

                case 2:
                    tile[0] = P2_MARKER;
                    tile[2] = P2_MARKER;
                    return tile;
                    break;
                
                default:
                    return "err";
                    break;
            }

            
        }

        
        int check_link(std::vector<std::vector<int>> game_state, int player, std::vector<std::vector<int>> link_history, int tile_row, int tile_col) {
            
            link_history[tile_row][tile_col] = 1;

            if ((player == 1) && (tile_col == N_COL - 1)) {
                return 1;
            }
            
            if ((player == 2) && (tile_row == N_ROW - 1)) {
                return 1;
            }
            
            std::vector<int> neighbours = std::vector<int>(6, 0);

            // Check position 0
            if ((tile_row > 0) && (tile_col < N_COL - 1)) {
                if (game_state[tile_row - 1][tile_col + 1] == player) {
                    neighbours[0] = 1;
                }
            }

            // Check position 1
            if (tile_row > 0) {
                if (game_state[tile_row - 1][tile_col] == player) {
                    neighbours[1] = 1;
                }
            }

            // Check position 2
            if (tile_col > 0) {
                if (game_state[tile_row][tile_col - 1] == player) {
                    neighbours[2] = 1;
                }
            }

            // Check position 3
            if ((tile_row < N_ROW - 1) && (tile_col > 0)) {
                if (game_state[tile_row + 1][tile_col - 1] == player) {
                    neighbours[3] = 1;
                }
            }

            // Check position 4
            if (tile_row < N_ROW - 1) {
                if (game_state[tile_row + 1][tile_col] == player) {
                    neighbours[4] = 1;
                }
            }

            // Check position 5
            if (tile_col < N_COL - 1) {
                if (game_state[tile_row][tile_col + 1] == player) {
                    neighbours[5] = 1;
                }
            }


            // This section repeats...


            // Check position 0 for link
            if (neighbours[0] && !link_history[tile_row - 1][tile_col + 1]) {
                if (check_link(game_state, player, link_history, tile_row - 1, tile_col + 1)) {
                    return 1;
                }
            }

            // Check position 1 for link
            if (neighbours[1] && !link_history[tile_row - 1][tile_col]) {
                if (check_link(game_state, player, link_history, tile_row - 1, tile_col)) {
                    return 1;
                }
            }

            // Check position 2 for link
            if (neighbours[2] && !link_history[tile_row][tile_col - 1]) {
                if (check_link(game_state, player, link_history, tile_row, tile_col - 1)) {
                    return 1;
                }
            }

            // Check position 3 for link
            if (neighbours[3] && !link_history[tile_row + 1][tile_col - 1]) {
                if (check_link(game_state, player, link_history, tile_row + 1, tile_col - 1)) {
                    return 1;
                }
            }
            
            // Check position 4 for link
            if (neighbours[4] && !link_history[tile_row + 1][tile_col]) {
                if (check_link(game_state, player, link_history, tile_row + 1, tile_col)) {
                    return 1;
                }
            }

            // Check position 5 for link
            if (neighbours[5] && !link_history[tile_row][tile_col + 1]) {
                if (check_link(game_state, player, link_history, tile_row, tile_col + 1)) {
                    return 1;
                }
            }
            
            return 0;

        }


    public:
        
        const std::string NAME = "Hex";   
        std::vector<double> difficulty = {5, 15, 30, 60, 120};

        const int N_ROW = 11;
        const int N_COL = 11;
        const int N_MOVES = N_ROW * N_COL;


        int transform_input(std::string user_input, const int N_ROW, const int N_COL) {

            int row = 10 * (user_input[1] - '0') + (user_input[2] - '0') - 1;
            int col = user_input[0] - 'a';
            int move = row * N_COL + col;

            return move;
        }


        int check_input(std::vector<int> available_moves, std::string user_input, const int N_ROW, const int N_COL) {
            
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
        

        std::vector<std::vector<int>> initialize_state(const int N_ROW, const int N_COL) {

            std::vector<std::vector<int>> game_state = std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0));

            return game_state;
        }

        
        void print_board(std::vector<std::vector<int>> game_state, const int N_ROW, const int N_COL) {
            
            char col_index = 'a';
            int n_spaces = 2;

            std::cout << INDENT << "   |XXXXXXX" << std::endl;
            std::cout << INDENT << "   |OXXX   XXXX" << std::endl;

            std::cout << INDENT << "   |OOX  " << col_index++ << "  XXXXXX" << std::endl;
            std::cout << INDENT << "   |OOO_____XXX   XXXX" << std::endl;
            
            for (int i = 0; i < N_ROW; i++) {

                // Line 1
                std::cout << INDENT;
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
                std::cout << INDENT;
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
                std::cout << INDENT;
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
                std::cout << INDENT;
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
                std::cout << INDENT;
                n_spaces +=4;
                print_spaces(n_spaces);
                std::cout << "XXXXXX\\";

                for (int j = i; j < N_COL / 2; j++) {
                    std::cout << "  " << print_tile(game_state[N_ROW - 1 - (j - i)][2 * j + 1]) << "  /     \\";
                }

                std::cout << "OO|" << std::endl;


                // Line 2
                std::cout << INDENT;
                n_spaces +=3;
                print_spaces(n_spaces);
                std::cout << "XXXX\\";

                for (int j = i; j < N_COL / 2; j++) {
                    std::cout << "_____/  " << print_tile(game_state[N_ROW - 1 - (j - i)][2 * j + 2]) << "  \\";
                }

                std::cout << "O|" << std::endl;


                // Line 3
                std::cout << INDENT;
                n_spaces +=4;
                print_spaces(n_spaces);
                std::cout << "XXXXXX\\";

                for (int j = i; j < N_COL / 2 - 1; j++) {
                    std::cout << "  " << print_tile(game_state[N_ROW - 1 - (j - i)][2 * j + 2]) << "  /     \\";
                }

                std::cout << "  " << print_tile(game_state[N_ROW - 1 - (N_COL / 2 - 1 - i)][N_COL - 1]) << "  /O|" << std::endl;


                // Line 4
                std::cout << INDENT;
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
            
            std::cout << INDENT;
            n_spaces +=4;
            print_spaces(n_spaces);
            std::cout << "XXXXXXOOO|" << std::endl;
        }


        std::vector<std::vector<int>> update_state(std::vector<std::vector<int>> game_state, int player, int move) {

            int row = move / N_COL;
            int col = move % N_COL;

            game_state[row][col] = player;
            
            return game_state;
        }


        std::vector<int> get_available_moves(std::vector<std::vector<int>> game_state, int player) {
            
            std::vector<int> available_moves = std::vector<int>(N_MOVES, 0);

            for (int m = 0; m < N_MOVES; m++) {
                if (game_state[m / N_COL][m % N_COL] == 0) {
                    available_moves[m] = 1;
                }
            }

            return available_moves;
        }

        
        int get_result(std::vector<std::vector<int>> game_state, int last_player) {

            std::vector<std::vector<int>> link_history = std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0));

            if (last_player == 1) {
                for (int i = 0 ; i < N_ROW; i++) {
                    if (game_state[i][0] == last_player) {
                        if (check_link(game_state, last_player, link_history, i, 0)) {
                            return 1;
                        }
                    }
                }
            }          

            if (last_player == 2) {
                for (int j = 0 ; j < N_COL; j++) {
                    if (game_state[0][j] == last_player) {
                        if (check_link(game_state, last_player, link_history, 0, j)) {
                            return 2;
                        }
                    }
                }
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


        void run() {
          
            run_internal(NAME, difficulty, N_ROW, N_COL, N_MOVES);
        }
    
};

