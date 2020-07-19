#include <iostream>
#include <vector>
#include <random>
#include <cmath>


class ConnectFour: public StrategyGame {
    
    public:
        
        const int N_ROW = 6;
        const int N_COL = 7;
        const int N_MOVES = N_COL;
        const int CONNECT = 4;
        
        const std::string NAME = "Connect Four";

        int result = -1;
        int max_depth = 1;
        std::vector<std::vector<int>> game_state = std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0));
        std::vector<int> available_moves = std::vector<int>(N_MOVES, 1);
        std::vector<int> difficulty = {6, 8, 10};

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution = std::uniform_int_distribution<int>(0, N_MOVES - 1);   



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
                int m = distribution(generator);

                if (m >=0 && m < N_MOVES){
                    if (!attempted_moves[m]) {

                        attempted_moves[m] = 1;
                        std::cout << ".";
                        
                        if (available_moves[m] == 1) {
                            score = get_score(game_state, available_moves, player, m, 1, max_depth, max_score);
            
                            if (score > max_score) {
                                max_score = score;
                                move = m;
                            }
                        }
                    }
                }
            }
            
            std::cout << std::endl;
            std::cout << INDENT << "Computer's move: " << move << std::endl;

            return move;
        }


        void run() {
            
            double score, max_score;
            int move;
            int player = 1;
                    
            std::cout << std::endl << std::endl;
            std::cout << INDENT << NAME << std::endl << std::endl;
            std::cout << INDENT << "Select a difficulty." << std::endl << std::endl;
            std::cout << INDENT << "1) Easy" << std::endl;
            std::cout << INDENT << "2) Medium" << std::endl;
            std::cout << INDENT << "3) Hard" << std::endl << std::endl;
            std::cout << INDENT << "Enter a number: ";

            int d_index = -1;

            while (d_index == -1) {
                if (!(std::cin >> d_index)){
                    std::cout << INDENT << "Invalid input. Please enter a number: ";
                    std::cin.clear();
                    std::cin.ignore(10000,'\n');
                    d_index = -1;
                } else if (d_index < 1 || d_index > difficulty.size()) {
                    std::cout << INDENT << "Difficulty unavailable. Please enter a number between 1 and " << difficulty.size() << ": ";
                    std::cin.clear();
                    std::cin.ignore(10000,'\n');
                    d_index = -1;
                }
            }        
            
            max_depth = difficulty[d_index - 1];

            std::cout << std::endl << std::endl;
            std::cout << INDENT << "Player markers" << std::endl;
            std::cout << INDENT << "You:      " << P1_MARKER << std::endl;
            std::cout << INDENT << "Computer: " << P2_MARKER << std::endl << std::endl;

            print_board();

            while (result == -1) {

                if (player == 1) {
                    std::cout << INDENT << "Your turn. Enter a number: ";
                    move = -1;

                    while (move == -1) {
                        if (!(std::cin >> move)){
                            std::cout << INDENT << "Invalid input. Please enter a number: ";
                            std::cin.clear();
                            std::cin.ignore(10000,'\n');
                            move = -1;
                        } else if (!check_input(move, available_moves)) {
                            std::cout << INDENT << "Move unavailable. Please enter an available number:  ";
                            std::cin.clear();
                            std::cin.ignore(10000,'\n');
                            move = -1;
                        }
                    }              
                } else {
                    move = get_move(player);
                    
                }

                std::cout << std::endl;
                game_state = update_state(game_state, player, move);
                available_moves = update_available_moves(game_state, available_moves);
                print_board();
                result = get_result(game_state);
                player = switch_player(player);
            }
            
            switch (result) {

                case 0:
                    std::cout << INDENT << "Draw." << std::endl;
                    break;

                case 1:
                    std::cout << INDENT << "You win!" << std::endl;
                    break;

                case 2:
                    std::cout << INDENT << "You lose." << std::endl;
                    break;
            }


        }
    

};

