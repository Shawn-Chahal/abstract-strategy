#include <iostream>
#include <vector>
#include <random>
#include <cmath>


class ConnectFour: public StrategyGame {
    
    public:
        
        const std::string NAME = "Connect Four";
        std::vector<int> difficulty = {6, 8, 10};

        const int N_ROW = 6;
        const int N_COL = 7;
        const int N_MOVES = N_COL;
        

        void print_board(std::vector<std::vector<int>> game_state, std::vector<int> available_moves, const int N_ROW, const int N_COL) {
            
            std::cout << INDENT;
            
            for (int j = 0; j < N_MOVES; j++) {
                if (available_moves[j] == 1) {
                    std::cout << "  " << j << " ";
                } else {
                    std::cout << "    ";
                }
            }

            std::cout << " " << std::endl;
            
            for (int i = 0; i < N_ROW; i++) {
                std::cout << INDENT;
                for (int j = 0; j < N_COL; j++) {
                    switch (game_state[i][j]) {
                        case 0:
                            std::cout << "|   ";
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
                std::cout << INDENT;

                for (int j = 0; j < N_COL; j++) {
                    std::cout << "----";
                }

                std::cout << "-" << std::endl;
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


        int get_result(std::vector<std::vector<int>> game_state) {

            const int CONNECT = 4;
            int player, count;
            int check_draw = 0;

            for (int i = 0; i < N_ROW; i++) {
                for (int j = 0; j < N_COL; j++) {
                    if (game_state[i][j] > 0) {
                        if (i == 0) {
                            check_draw++;
                        }

                        player = game_state[i][j];

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

            if (check_draw == N_COL) {
                /* Declare a draw */
                return 0;
            } else {
                /* Game continues */
                return -1;
            }
        }


        void run() {
         
            run_internal(NAME, difficulty, N_ROW, N_COL, N_MOVES);
        }
    
};

