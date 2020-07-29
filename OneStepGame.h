#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <string>


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
        
       
        int get_score(std::vector<std::vector<int>> game_state, int player, int move) {

            game_state = update_state(game_state, player, move);
            int result = get_result(game_state, player);


            if (result >= 0) {
                return result;
            }

            player = switch_player(player);
            std::vector<int> available_moves = get_available_moves(game_state, player);

            int pass = 1;

            for (int m = 0; m < available_moves.size(); m++) {
                if (available_moves[m]) {
                    pass = 0;
                    break;
                }
            }

            if (pass) {
                player = switch_player(player);
                available_moves = get_available_moves(game_state, player);
            }


            std::uniform_int_distribution<int> distribution = std::uniform_int_distribution<int>(0, available_moves.size() - 1); 
  
            int m;
            int check = 0;
            while (result == -1) {

                m = distribution(generator);

                if (available_moves[m]) {
            
                    result = get_score(game_state, player, m);
                    
                }
                
                
                
            }

            return result;
        
        }


        int get_move(std::vector<std::vector<int>> game_state, int player, std::vector<int> available_moves, int max_games) {

            std::cout << INDENT << "Computer is thinking.";
            std::uniform_int_distribution<int> distribution = std::uniform_int_distribution<int>(0, available_moves.size() - 1); 
            std::vector<int> win = std::vector<int>(available_moves.size(), 0);
            std::vector<int> lose = std::vector<int>(available_moves.size(), 0);
            std::vector<int> draw = std::vector<int>(available_moves.size(), 0);
            std::vector<int> n_games = std::vector<int>(available_moves.size(), 0);

            
            int games_played = 0;
            int result;
            int m;

            while (games_played < max_games) {
                
                m = distribution(generator);

                

                if (available_moves[m]) {
                
                    result = get_score(game_state, player, m);
    
                    if (result == player) {
                        win[m]++;
                    } else if (result == switch_player(player)) {
                        lose[m]++;
                    } else {
                        draw[m]++;
                    }
                    
                    n_games[m]++;

                    games_played++;

                    if (games_played % (max_games / 10) == 0) {
                        std::cout << ".";
                    }
                }
            }

            int move;
            double best_score = 0;
            double score;

            for (int m = 0; m < available_moves.size(); m++) {
                if (n_games[m] > 0) {
                    
                    score = (win[m] + 0.0) / (n_games[m] + 0.0) + sqrt(2.0 * log(max_games + 0.0) / (n_games[m] + 0.0));

                    if (score > best_score) {

                        best_score = score;
                        move = m;
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
        virtual int get_result(std::vector<std::vector<int>> game_state, int last_player) { return -1; }
        virtual std::vector<std::vector<int>> initialize_state(const int N_ROW, const int N_COL) { return std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0)); }
        virtual int check_input(std::vector<int> available_moves, std::string user_input, const int N_ROW, const int N_COL) { return -1; }
        virtual int transform_input(std::string user_input, const int N_ROW, const int N_COL) { return -1; }

        // Shared methods
        int switch_player(int player) {
            
            if (player == 1) {
                return 2;
            } else {
                return 1;
            }
        }    

        void run_internal(const std::string NAME, std::vector<int> difficulty, const int N_ROW, const int N_COL, const int N_MOVES) {
            
            double score, max_score;
            int move, pass;
            int player = 1;
            int result = -1;
            int max_games = 1;
            std::vector<std::vector<int>> game_state = initialize_state(N_ROW, N_COL);
            std::vector<int> available_moves = get_available_moves(game_state, player);
            std::string user_input;

            std::cout << INDENT << NAME << std::endl << std::endl;
            std::cout << INDENT << "Select a difficulty." << std::endl << std::endl;
            std::cout << INDENT << "1) Easy" << std::endl;
            std::cout << INDENT << "2) Medium" << std::endl;
            std::cout << INDENT << "3) Hard" << std::endl;
            std::cout << std::endl;
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
            
            max_games = difficulty[d_index - 1];

            std::cout << LINE_BREAK << std::endl;

            std::cout << INDENT << "Player markers" << std::endl;
            std::cout << INDENT << "You:      " << P1_MARKER << std::endl;
            std::cout << INDENT << "Computer: " << P2_MARKER << std::endl << std::endl;

            print_board(game_state, available_moves, N_ROW, N_COL);

            while (result == -1) {

                if (player == 1) {
                    std::cout << INDENT << "Your turn. Enter an alphanumeric value: ";
                    std:: cin >> user_input;

                    while (!check_input(available_moves, user_input, N_ROW, N_COL)) {
                        
                        std::cout << INDENT << "Invalid input. Please enter an available alphanumeric value: ";
                        std::cin.clear();
                        std::cin.ignore(10000,'\n');
                        std::cin >> user_input;
                        
                    }              

                    move = transform_input(user_input, N_ROW, N_COL);

                } else {
                    move = get_move(game_state, player, available_moves, max_games);
                    
                }

                std::cout << LINE_BREAK << std::endl;
                
                game_state = update_state(game_state, player, move);
                result = get_result(game_state, player);
                player = switch_player(player);
                available_moves = get_available_moves(game_state, player);

                pass = 1;

                for (int m = 0; m < N_MOVES; m++) {
                    if (available_moves[m]) {
                        pass = 0;
                        break;
                    }
                }

                if (pass) {
                    player = switch_player(player);
                    available_moves = get_available_moves(game_state, player);
                }

                print_board(game_state, available_moves, N_ROW, N_COL);
                
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

