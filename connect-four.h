#include <iostream>
#include <vector>
#include <cmath>



class ConnectFour {
    private:
        /* data */
    public:
        
        const int N_ROW = 6;
        const int N_COL = 7;
        const int N_MOVES = N_COL;
        const int CONNECT = 4;
        const double S_INITIAL = 1000000.0;
        const double DECAY = 0.9;
        int player = 1;
        int result = -1;
        const char P1_MARKER = 'O';
        const char P2_MARKER = 'X';
        const std::string INDENT = "   ";
        const std::string NAME = "Connect Four";
        std::vector<std::vector<int>> game_state = std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0));
        std::vector<int> available_moves = std::vector<int>(N_MOVES, 1);
        std::vector<int> difficulty = {6, 8, 10};

                
        int check_moves(std::vector<int> attempted_moves) {

            for (int i = 0; i < attempted_moves.size(); i++) {
                if (attempted_moves[i] == 0) {
                    return 0;
                }
            }

            return 1;
        }


        int check_input(int col) {
        
            if (col >= 0 && col < N_MOVES) {
                return available_moves[col];
            } else {
                return 0;
            }
        }


        int switch_player(int player) {
            
            if (player == 1) {
                return 2;
            } else {
                return 1;
            }
        }


        void print_board(std::vector<std::vector<int>> game_state, std::vector<int> available_moves) {
            
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


        std::vector<std::vector<int>> update_state(std::vector<std::vector<int>> game_state, int player, int col) {

            for (int row = N_ROW - 1; row >= 0; row--) {
                if (game_state[row][col] == 0) {
                    game_state[row][col] = player;
                    break;
                }
            }   
            return game_state;
        }


        std::vector<int> update_available_moves(std::vector<std::vector<int>> game_state, std::vector<int> available_moves) {
            
            for (int j=0; j < N_MOVES; j++) {
                if (game_state[0][j] > 0) {
                    available_moves[j] = 0;
                }
            }
            return available_moves;
        }


        int check_state(std::vector<std::vector<int>> game_state) {

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


        double get_score(std::vector<std::vector<int>> game_state, std::vector<int> available_moves, int player, int col, int depth, int max_depth, double ab) {

            game_state = update_state(game_state, player, col);
            available_moves = update_available_moves(game_state, available_moves);
            int result = check_state(game_state);
            double score;

            if (result == 2) {
                return pow(DECAY, depth);
            } else if (result == 1) {  
                return -pow(DECAY, depth);
            } else if (result == 0) {
                return 0.0;
            } else if (depth == max_depth) {  
                return 0.0;
            } else {
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
            }
        }


        void end_turn(int player, int col) {

            game_state = update_state(game_state, player, col);
            available_moves = update_available_moves(game_state, available_moves);
            print_board(game_state, available_moves);
            result = check_state(game_state);
            player = switch_player(player);
        }

};

