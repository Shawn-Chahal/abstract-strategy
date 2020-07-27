#include <iostream>
#include <vector>
#include <random>
#include <cmath>


class Hex: public OneStepGame {
    private:


    public:
        
        const std::string NAME = "Hex";   
        std::vector<int> difficulty = {2, 4, 6, 8, 10};

        const int N_ROW = 11;
        const int N_COL = 11;
        const int N_MOVES = N_ROW * N_COL;
        
        // Need to finish
        double intermediate_score(std::vector<std::vector<int>> game_state) {
            
            int player1_score = 0;
            int player2_score = 0;
            

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

            return (player2_score - player1_score + 0.0) / (player1_score + player2_score + 0.0);

        }


        int transform_input(std::string user_input, const int N_ROW, const int N_COL) {

            int row = user_input[1] - '0';
            int col = user_input[0] - 'a';
            int move = row * N_COL + col;

            return move;
        }


        int check_input(std::vector<int> available_moves, std::string user_input, const int N_ROW, const int N_COL) {
            
            if (user_input.length() != 3) {
                return 0;
            }

            int row = user_input[1] - '0';
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

        // Need to finish
        void print_board(std::vector<std::vector<int>> game_state, std::vector<int> available_moves, const int N_ROW, const int N_COL) {
            
            char col_index = 'a';

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

                    std::cout << "\\       /     ";
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
                std::cout << "   |O/       ";

                for (int j = 0; (j < i) && (j < N_COL / 2); j++) {
                    std::cout << "\\_____/       ";
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
                std::cout << "   |O\\       ";

                for (int j = 0; (j < i) && (j < N_COL / 2); j++) {

                    std::cout << "/     \\       ";
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
                    std::cout << "       \\_____/";
                }

                

                if (col_index - 'a' < N_COL) {
                    std::cout << "       \\_____XXX   XXXX"; 
                } else if (col_index - 'a' == N_COL) {
                    std::cout << "       \\_____OOO|";
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

            std::cout << std::endl;
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

        // Need to finish
        int get_result(std::vector<std::vector<int>> game_state) {

            int player1_score = 0;
            int player2_score = 0;

            std::vector<int> available_moves = std::vector<int>(N_MOVES, 0);

            for (int p = 1; p <= 2; p++) {
                available_moves = get_available_moves(game_state, p);

                for (int m = 0; m < N_MOVES; m++) {
                    if (available_moves[m]) {
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


        void run() {
          
            run_internal(NAME, difficulty, N_ROW, N_COL, N_MOVES);
        }
    
};

