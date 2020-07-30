#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <string>


class OneStepGame {
    private:

        int next_player(std::vector<std::vector<int>> game_state, int previous_player) {

            int player = switch_player(previous_player);
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
            }

            return player;
        }

        
        int get_terminal_result(std::vector<std::vector<int>> game_state, int player) {

            std::vector<int> available_moves = get_available_moves(game_state, player);
            std::uniform_int_distribution<int> distribution = std::uniform_int_distribution<int>(0, available_moves.size() - 1); 
        
            int move, result;
        
            do {
                move = distribution(generator);

                if (available_moves[move]) {

                    game_state = update_state(game_state, player, move);
                    result = get_result(game_state, player);
                }
            } while (!available_moves[move]);

            if (result > -1) {
               return result;
            }

            player = next_player(game_state, player);

            return get_terminal_result(game_state, player);
        }


        int check_moves(std::vector<int> attempted_moves) {

            for (int i = 0; i < attempted_moves.size(); i++) {
                if (attempted_moves[i] == 0) {
                    return 0;
                }
            }

            return 1;
        }
        

        std::vector<Node> update_tree(std::vector<std::vector<int>> game_state, std::vector<Node> tree, int parent_node, int move) {

            game_state = update_state(game_state, tree[parent_node].player, move);
            int result = get_result(game_state, tree[parent_node].player);

            if (result > -1) {

                tree[parent_node].update(result);

                return tree;
            }

            int player = next_player(game_state, tree[parent_node].player);
            std::vector<int> available_moves = get_available_moves(game_state, player);
                        
            if (tree[parent_node].children[move] == -1) {

                int new_child_node = tree.size();
                tree[parent_node].add_child(new_child_node, move);
                tree.push_back(Node(parent_node, player, available_moves.size()));
            }

            int current_node = tree[parent_node].children[move];
            
            if (tree[current_node].total == 0) {

                result = get_terminal_result(game_state, tree[current_node].player); 
                tree[current_node].update(result);

            } else {

                double UCB1;
                double UCB1_max = -1;
                int child_node, m_try, new_child_node, player_child;

                for (int m = 0; m < available_moves.size(); m++) {
                    if (available_moves[m]) {

                        child_node = tree[current_node].children[m];

                        if (child_node == -1) {
                            UCB1 = S_INITIAL;
                        } else {
                            UCB1 = tree[child_node].get_UCB1(tree[current_node].player, tree[current_node].total);
                        }

                        if (UCB1 > UCB1_max) {
                            UCB1_max = UCB1;
                            m_try = m;
                        }
                    }
                }

                tree = update_tree(game_state, tree, current_node, m_try);
            }        

            tree[parent_node].update(tree[current_node].last_result);

            return tree;
        }


        int get_move(std::vector<std::vector<int>> game_state, int player, std::vector<int> available_moves, int max_games) {

            std::cout << INDENT << "Computer is thinking.";
            std::vector<Node> tree;
            tree.push_back(Node(-1, player, available_moves.size()));
            double UCB1,UCB1_max;
            int child_node,m_try, new_child_node;

            while (tree[0].total < max_games) {

                UCB1_max = -1;

                for (int m = 0; m < available_moves.size(); m++) {
                    if (available_moves[m]) {
                        
                        child_node = tree[0].children[m];

                        if (child_node == -1) {
                            UCB1 = S_INITIAL;
                        } else {
                            UCB1 = tree[child_node].get_UCB1(tree[0].player, tree[0].total);
                        }

                        if (UCB1 > UCB1_max) {
                            UCB1_max = UCB1;
                            m_try = m;
                        }
                    }
                }

                tree = update_tree(game_state, tree, 0, m_try);
                
                if (tree[0].total % (max_games / 10) == 0) {
                    std::cout << ".";
                }                
            }

            std::cout << std::endl;

            // LOGISTICS START
            int node_log;
            for (int m = 0; m < available_moves.size(); m++) {
                node_log = tree[0].children[m];
                if (node_log >- 1) {
                    std::cout << INDENT << m + 1 << ": " << tree[node_log].get_score(player) << " Wins: " << tree[node_log].loss << " Draw: " << tree[node_log].draw << " Loss: " << tree[node_log].win << " Total: " << tree[node_log].total << std::endl;
                }
            }
            std::cout << INDENT << "Tree size: " << tree.size() << " Wins: " << tree[0].win << " Draw: " << tree[0].draw << " Loss: " << tree[0].loss << " Total: " << tree[0].total << std::endl;
            // LOGISTICS END

            int move;
            double best_score = -S_INITIAL;
            double score;
            
            for (int m = 0; m < available_moves.size(); m++) {

                child_node = tree[0].children[m];

                if (child_node != -1) {
                    
                    score = tree[child_node].get_score(player);

                    if (score > best_score) {

                        best_score = score;
                        move = m;
                    }
                } 
            }

            std::cout << INDENT << "Computer's move: " << move << std::endl;

            return move;
        }


    public:

        const double S_INITIAL = 1000000.0;
        const char P1_MARKER = 'O';
        const char P2_MARKER = 'X';
        const std::string INDENT = "   ";
        const std::string LINE_BREAK = "\n" + INDENT + "-----------------------------\n";
        std::default_random_engine generator;

        // Template virtual methods
        virtual void print_board(std::vector<std::vector<int>> game_state, const int N_ROW, const int N_COL) {}
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
            
            std::vector<std::vector<int>> game_state = initialize_state(N_ROW, N_COL);
            std::vector<int> available_moves;
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
            
            int max_games = difficulty[d_index - 1];

            std::cout << LINE_BREAK << std::endl;

            std::cout << INDENT << "Player markers" << std::endl;
            std::cout << INDENT << "You:      " << P1_MARKER << std::endl;
            std::cout << INDENT << "Computer: " << P2_MARKER << std::endl << std::endl;

            print_board(game_state, N_ROW, N_COL);

            while (result == -1) {

                available_moves = get_available_moves(game_state, player);

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
                player = next_player(game_state, player);
                print_board(game_state, N_ROW, N_COL);
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

