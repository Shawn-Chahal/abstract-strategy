#include <iostream>
#include <vector>
#include <random>
#include <cmath>


class TicTacToe: public StrategyGame {
    
    public:
        
        const int N_ROW = 3;
        const int N_COL = 3;
        const int N_MOVES = N_ROW * N_COL;
        const int CONNECT = 3;
        
        const std::string NAME = "Tic-Tac-Toe";

        int result = -1;
        int max_depth = 1;
        std::vector<std::vector<int>> game_state = std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0));
        std::vector<int> available_moves = std::vector<int>(N_MOVES, 1);
        std::vector<int> difficulty = {2, 6, 10};


        void print_board(std::vector<std::vector<int>> game_state, std::vector<int> available_moves, const int N_ROW, const int N_COL) {
            
            for (int i = 0; i < N_ROW; i++) {
                std::cout << INDENT;
                for (int j = 0; j < N_COL; j++) {
                    switch (game_state[i][j]) {
                        case 0:
                            std::cout << "| " << i * N_COL + j << " ";
                            break;
                        case 1:
                            std::cout << "| " << P1_MARKER << " ";
                            break;
                        case 2:
                            std::cout << "| " << P2_MARKER << " ";
                            break;
                    }
                }

                std::cout << "|" << std::endl;
                

                if (i < N_ROW - 1) {
                    std::cout << INDENT;
                    for (int j = 0; j < N_COL; j++) {
                        std::cout << "----";
                    }
                    std::cout << "-" << std::endl;
                }
            }
            std::cout << std::endl;
        }


        std::vector<std::vector<int>> update_state(std::vector<std::vector<int>> game_state, int player, int move) {

            game_state[move / N_COL][move % N_COL] = player;
            
            return game_state;
        }


        std::vector<int> update_available_moves(std::vector<std::vector<int>> game_state, std::vector<int> available_moves) {
            
            for (int i = 0; i < N_ROW ; i++) {
                for (int j = 0; j < N_COL ; j++) {
                    if (game_state[i][j] > 0) {
                        available_moves[i * N_COL + j] = 0;
                    }
                }
            }
            return available_moves;
        }


        int get_result(std::vector<std::vector<int>> game_state) {

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


        void run() {
          
            run_internal(NAME, difficulty, max_depth, result, game_state, available_moves, N_ROW, N_COL);

        }
    
};

