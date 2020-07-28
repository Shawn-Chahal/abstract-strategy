#include <iostream>
#include <vector>
#include <random>
#include <cmath>


class ConnectFour: public OneStepGame {
    
    public:
        
        const std::string NAME = "Connect Four";
        std::vector<int> difficulty = {4, 6, 8, 10, 12};

        const int N_ROW = 6;
        const int N_COL = 7;
        const int N_MOVES = N_COL;
        
        
        double intermediate_score(std::vector<std::vector<int>> game_state) {
            
            return 0.0;
        }

        int transform_input(std::string user_input, const int N_ROW, const int N_COL) {

            int move = user_input[0] - '1';

            return move;
        }


        int check_input(std::vector<int> available_moves, std::string user_input, const int N_ROW, const int N_COL) {
            
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

        void print_board(std::vector<std::vector<int>> game_state, std::vector<int> available_moves, const int N_ROW, const int N_COL) {
            
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


        std::vector<std::vector<int>> update_state(std::vector<std::vector<int>> game_state, int player, int move) {

            for (int row = game_state.size() - 1; row >= 0; row--) {
                if (game_state[row][move] == 0) {
                    game_state[row][move] = player;
                    break;
                }
            }   
            return game_state;
        }


        std::vector<int> get_available_moves(std::vector<std::vector<int>> game_state, int player) {
            
            std::vector<int> available_moves = std::vector<int>(N_MOVES, 1);

            for (int j=0; j < available_moves.size(); j++) {
                if (game_state[0][j] > 0) {
                    available_moves[j] = 0;
                }
            }
            return available_moves;
        }


        int get_result(std::vector<std::vector<int>> game_state, int last_player) {

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


        std::vector<std::vector<int>> initialize_state(const int N_ROW, const int N_COL) {

            return std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0));

            }


        void run() {
         
            run_internal(NAME, difficulty, N_ROW, N_COL, N_MOVES);
        }
    
};

