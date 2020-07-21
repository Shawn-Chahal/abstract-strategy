#include <iostream>
#include <vector>
#include <random>
#include <cmath>


class OneStepGame {
    private:

        int check_moves(std::vector<int> attempted_moves) {

                for (int i = 0; i < attempted_moves.size(); i++) {
                    if (attempted_moves[i] == 0) {
                        return 0;
                    }
                }

                return 1;
            }
        

        int switch_player(int player) {
            
            if (player == 1) {
                return 2;
            } else {
                return 1;
            }
        }    

        
        double get_score(std::vector<std::vector<int>> game_state, std::vector<int> available_moves, int player, int move, int depth, int max_depth, double ab) {

            game_state = update_state(game_state, player, move);
            available_moves = get_available_moves(game_state, player);
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

                        for (int j = 0; j < available_moves.size(); j++) {
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

                        for (int j = 0; j < available_moves.size(); j++) {
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


        int get_move(std::vector<std::vector<int>> game_state, int player, std::vector<int> available_moves, int max_depth) {

            std::cout << INDENT << "Computer is thinking.";
            std::vector<int> attempted_moves = std::vector<int>(available_moves.size(), 0);
            double max_score = -S_INITIAL;
            double score;
            int move;

            
            std::uniform_int_distribution<int> distribution = std::uniform_int_distribution<int>(0, available_moves.size() - 1);   

            while (!check_moves(attempted_moves)) {
                int m = distribution(generator);

                if (m >=0 && m < available_moves.size()){
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


    public:

        const double S_INITIAL = 1000000.0;
        const double DECAY = 0.9;
        const char P1_MARKER = 'O';
        const char P2_MARKER = 'X';
        const std::string INDENT = "   ";
        const std::string LINE_BREAK = "\n" + INDENT + "-----------------------------\n";
        std::default_random_engine generator;


        // Template virtual methods
        virtual void print_board(std::vector<std::vector<int>> game_state, std::vector<int> available_moves, const int N_ROW, const int N_COL) {}
        virtual std::vector<std::vector<int>> update_state(std::vector<std::vector<int>> game_state, int player, int move) { return game_state; }
        virtual std::vector<int> get_available_moves(std::vector<std::vector<int>> game_state, int player) { return std::vector<int>(1, -1); }
        virtual int get_result(std::vector<std::vector<int>> game_state) { return -1; }
        virtual std::vector<std::vector<int>> initialize_state(const int N_ROW, const int N_COL) { return std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0)); }
        virtual int check_input(std::vector<int> available_moves, int user_input, const int N_ROW, const int N_COL) { return -1; }
        virtual int transform_input(int user_input, const int N_ROW, const int N_COL) { return -1; }


        // Shared void method
        void run_internal(const std::string NAME, std::vector<int> difficulty, const int N_ROW, const int N_COL, const int N_MOVES) {
            
            double score, max_score;
            int move, user_input;
            int player = 1;
            int result = -1;
            int max_depth = 1;
            std::vector<std::vector<int>> game_state = initialize_state(N_ROW, N_COL);
            std::vector<int> available_moves = get_available_moves(game_state, player);

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

            std::cout << LINE_BREAK << std::endl;

            std::cout << INDENT << "Player markers" << std::endl;
            std::cout << INDENT << "You:      " << P1_MARKER << std::endl;
            std::cout << INDENT << "Computer: " << P2_MARKER << std::endl << std::endl;

            print_board(game_state, available_moves, N_ROW, N_COL);

            while (result == -1) {

                if (player == 1) {
                    std::cout << INDENT << "Your turn. Enter a number: ";
                    user_input = -1;

                    while (user_input == -1) {
                        if (!(std::cin >> user_input)){
                            std::cout << INDENT << "Invalid input. Please enter a number: ";
                            std::cin.clear();
                            std::cin.ignore(10000,'\n');
                            user_input = -1;
                        } else if (!check_input(available_moves, user_input, N_ROW, N_COL)) {
                            std::cout << INDENT << "Move unavailable. Please enter an available number:  ";
                            std::cin.clear();
                            std::cin.ignore(10000,'\n');
                            user_input = -1;
                        }
                    }              

                    move = transform_input(user_input, N_ROW, N_COL);

                } else {
                    move = get_move(game_state, player, available_moves, max_depth);
                    
                }

                std::cout << LINE_BREAK << std::endl;
                
                game_state = update_state(game_state, player, move);
                available_moves = get_available_moves(game_state, player);
                print_board(game_state, available_moves, N_ROW, N_COL);
                result = get_result(game_state);
                player = switch_player(player);
            }
            
            std::cout << LINE_BREAK << std::endl;

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

