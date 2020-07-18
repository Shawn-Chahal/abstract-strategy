#include <iostream>
#include <vector>
#include <cmath>
#include "strategy-game.h"


class ConnectFour: public StrategyGame {
    
    public:
        
        const int N_ROW = 6;
        const int N_COL = 7;
        const int N_MOVES = N_COL;
        const int CONNECT = 4;
        const double S_INITIAL = 1000000.0;
        const double DECAY = 0.9;
        const char P1_MARKER = 'O';
        const char P2_MARKER = 'X';
        const std::string INDENT = "   ";
        const std::string NAME = "Connect Four";

        int result = -1;
        int max_depth = 1;
        std::vector<std::vector<int>> game_state = std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0));
        std::vector<int> available_moves = std::vector<int>(N_MOVES, 1);
        std::vector<int> difficulty = {6, 8, 10};

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution = std::uniform_int_distribution<int>(0, N_MOVES - 1);   


        void set_difficulty(int d_index) {
            max_depth = difficulty[d_index - 1];
        }


        int check_input(int move) {
        
            if (move >= 0 && move < N_MOVES) {
                return available_moves[move];
            } else {
                return 0;
            }
        }


        void print_board() {
            
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







        int get_result(std::vector<std::vector<int>> game_state) {

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


        double get_score(std::vector<std::vector<int>> game_state, std::vector<int> available_moves, int player, int move, int depth, int max_depth, double ab) {

            game_state = update_state(game_state, player, move);
            available_moves = update_available_moves(game_state, available_moves);
            double score;

            switch (get_result(game_state)) {
                case 2:
                    return pow(DECAY, depth);
                    break;
                
                case 1:
                    return -pow(DECAY, depth);
                    break;

                case 0:
                    return 0.0;
                    break;

                default:

                    if (depth == max_depth) {  
                        return 0.0;
                    }

                    player = switch_player(player);

                    if (player == 1) {
                        
                        double min_score = S_INITIAL;

                        for (int j = 0; j < N_MOVES; j++) {
                            if (available_moves[j] == 1) {
                                score = get_score(game_state, available_moves, player, j, depth + 1, max_depth, min_score);

                                if (score < min_score) {
                                    min_score = score;
                                }

                                if (min_score <= ab) {
                                    break;
                                }
                            }
                        }
                        return min_score;
                    }  else /* if (player == 2) */ {

                        double max_score = -S_INITIAL;

                        for (int j = 0; j < N_MOVES; j++) {
                            if (available_moves[j] == 1) {
                                score = get_score(game_state, available_moves, player, j, depth + 1, max_depth, max_score);

                                if (score > max_score) {
                                    max_score = score;
                                }

                                if (max_score >= ab) {
                                    break;
                                }
                            }
                        }
                        return max_score;


                    }

                    break;
            }

            
        
        }


        int get_move(int player) {

                std::cout << INDENT << "Computer is thinking.";
                std::vector<int> attempted_moves = std::vector<int>(N_MOVES, 0);
                double max_score = -S_INITIAL;
                double score;
                int move;

                while (!check_moves(attempted_moves)) {
                    int j = distribution(generator);

                    if (j >=0 && j < N_MOVES){
                        if (!attempted_moves[j]) {

                            attempted_moves[j] = 1;
                            std::cout << ".";
                            
                            if (available_moves[j] == 1) {
                                score = get_score(game_state, available_moves, player, j, 1, max_depth, max_score);
                
                                if (score > max_score) {
                                    max_score = score;
                                    move = j;
                                }
                            }
                        }
                    }
                }
                
                std::cout << std::endl;
                std::cout << INDENT << "Computer's move: " << move << std::endl;

                return move;
        }


        void end_turn(int player, int move) {

            game_state = update_state(game_state, player, move);
            available_moves = update_available_moves(game_state, available_moves);
            print_board();
            result = get_result(game_state);
        }

};

