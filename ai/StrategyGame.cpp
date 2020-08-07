#include "asg.h"
#include "StrategyGame.h"

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <chrono>
#include <thread>
#include <future>
#include <functional>

int StrategyGame::get_terminal_result(GameBoard &board_ref) {
    
    GameBoard *board = board_ref.clone();
    std::uniform_int_distribution<int> distribution = std::uniform_int_distribution<int>(0, board->get_num_moves() - 1); 
    int move, terminal_result;

    while (1) {
        
        move = distribution(generator);

        if (board->get_available_moves(move)) {

            board->update(move);
            break;
        }
    } 
    
    if (board->get_result() > -1) {

        terminal_result = board->get_result();
        delete board;
        return terminal_result;
    }
    
    terminal_result = get_terminal_result(*board);
    delete board;
    return terminal_result;
}

std::vector<Node> StrategyGame::update_tree(GameBoard &board_ref, std::vector<Node> tree, int parent_node, int move) {
        
    if (tree[parent_node].child_node_id[move] == -1) {
        GameBoard *board = board_ref.clone();
        board->update(move);
        int new_child_node = tree.size();
        tree[parent_node].add_child(new_child_node, move);
        tree.push_back(Node(parent_node, *board));
        delete board;
    }
        
    int current_node = tree[parent_node].child_node_id[move];

    if (tree[current_node].board->get_result() > -1) {

        tree[current_node].update(tree[current_node].board->get_result());
        tree[parent_node].update(tree[current_node].board->get_result());
        
        return tree;
    }
        
    if (tree[current_node].total == 0) {
 
        tree[current_node].update(get_terminal_result(*tree[current_node].board));
        
    } else {
        
        double UCB1;
        double UCB1_max = -1;
        int child_node, m_try, new_child_node, player_child;

        for (int m = 0; m < tree[current_node].board->get_num_moves(); m++) {
            if (tree[current_node].board->get_available_moves(m)) {

                child_node = tree[current_node].child_node_id[m];

                if (child_node == -1) {
                    UCB1 = S_INITIAL;
                } else {
                    UCB1 = tree[child_node].get_UCB1(tree[current_node].board->get_player(), tree[current_node].total);
                }

                if (UCB1 > UCB1_max) {
                    UCB1_max = UCB1;
                    m_try = m;
                }
            }
        }

        tree = update_tree(*tree[current_node].board, tree, current_node, m_try);
    }        
        
    tree[parent_node].update(tree[current_node].last_result);
    
    return tree;
}

std::vector<double> StrategyGame::get_score_thread(GameBoard &board_ref, std::vector<std::vector<int>> available_moves_thread, int thread_index, double max_time) {
    
    GameBoard *board = board_ref.clone();
    
    std::vector<Node> tree;
    tree.push_back(Node(-1, *board));
    double UCB1,UCB1_max;
    int child_node,m_try, new_child_node, m;

    std::chrono::duration<double> time;
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    time = end - start;

    while (time.count() < max_time) {
               
        UCB1_max = -1;

        for (int i = 0; i < available_moves_thread[thread_index].size(); i++) {
            
            m = available_moves_thread[thread_index][i];    
            child_node = tree[0].child_node_id[m];

            if (child_node == -1) {
                UCB1 = S_INITIAL;
            } else {
                UCB1 = tree[child_node].get_UCB1(tree[0].board->get_player(), tree[0].total);
            }

            if (UCB1 > UCB1_max) {
                UCB1_max = UCB1;
                m_try = m;
            }
            
        }
        
        tree = update_tree(*board, tree, 0, m_try);
        
        end = std::chrono::steady_clock::now();
        time = end - start;
        
    }
    
    int move;
    double best_score = -S_INITIAL;
    

    std::vector<double> score = std::vector<double> (board->get_num_moves(), -1.0);
    
    for (int m = 0; m < score.size(); m++) {

        child_node = tree[0].child_node_id[m];

        if (child_node != -1) {
            
            score[m] = tree[child_node].get_score(board->get_player());

        } 
    }

    std::cout << "\tThread: " << thread_index << "\tTree size: " << tree.size() << "\tTotal games: " << tree[0].total << std::endl;

    delete board;
    return score;
}

int StrategyGame::get_move(GameBoard &board_ref, double max_time) {

    GameBoard *board = board_ref.clone();
    std::cout << "\t" << "Computer is thinking..." << std::endl << std::endl;

    unsigned int n_threads = std::thread::hardware_concurrency();
    std::vector<std::vector<int>> available_moves_thread = std::vector<std::vector<int>>(n_threads, std::vector<int>());
    int thread_index = 0;

    for (int m = 0; m < board->get_num_moves(); m++) {
        if (board->get_available_moves(m)) {
            available_moves_thread[thread_index].push_back(m);
            thread_index++;

            if (thread_index >= n_threads) {
                thread_index = 0;
            }
        }
    }

    n_threads = 0;

    for (int i = 0; i < available_moves_thread.size(); i ++) {
        if (available_moves_thread[i].size() > 0) {
            n_threads++;
        }
    }

    std::vector<std::future<std::vector<double>>> available_moves_future;

    for (int i = 0; i < n_threads; i++) {
        available_moves_future.push_back(std::async(std::launch::async, &StrategyGame::get_score_thread, this, std::ref(*board), available_moves_thread, i, max_time));
    }

    std::vector<std::vector<double>> available_moves_all; // i = thread_index, j = move_index

    for (int i = 0; i < n_threads; i++) {
        available_moves_all.push_back(available_moves_future[i].get());
    }

    std::vector<double> score = std::vector<double>(board->get_num_moves(), -1);

    for (int j = 0; j < board->get_num_moves(); j++) {
        for (int i = 0; i < n_threads; i++) {
            if (available_moves_all[i][j] > score[j]) {
                score[j] = available_moves_all[i][j];
            }
        }
    }

    int move;
    double best_score = -1;

    for (int m = 0; m < score.size(); m++) {
        if (score[m] > best_score) {
            best_score = score[m];
            move = m;
        }
    }

    int confidence = 100 * best_score;

    std::cout << std::endl <<  "\t" << "Computer's confidence: " << confidence << "%" << std::endl << std::endl;
    std::cout << "\t" << "Computer's move: ";
    board->print_ai_move(move);
    std::cout << std::endl;
    
    delete board;
    return move;
}

void StrategyGame::run(GameBoard &board_ref) {
    
    GameBoard *board = board_ref.clone();
    board->initialize();

    double score, max_score;
    int move, pass;
    std::vector<std::string> difficulty_names = {"Beginner", "Easy", "Normal", "Hard", "Expert"};

    std::string user_input;

    std::cout << "\t" << board->get_name() << std::endl << std::endl;
    std::cout << "\t" << "How to play" << std::endl << std::endl;
    board->print_rules();
    std::cout << std::endl;
    std::cout << "\t" << "Player markers" << std::endl;
    std::cout << "\t" << "You:      " << board->get_player_marker(1) << std::endl;
    std::cout << "\t" << "Computer: " << board->get_player_marker(2) << std::endl << std::endl;

    std::cout << "\t" << "Select a difficulty [Time AI has to think]" << std::endl << std::endl;

    for (int i = 0; i < difficulty_names.size(); i++) {
        std::cout << "\t" << i + 1 << ") " << difficulty_names[i] << " \t[ " << board->get_difficulty(i) << " s ]" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "\t" << "Enter a number: ";

    int d_index = asg::menu_input(difficulty_names.size());
    
    double max_time = board->get_difficulty(d_index - 1);

    asg::line_break(30);

    board->print_board();

    while (board->get_result() == -1) {

        if (board->get_player() == 1) {

            std::cout << "\t" << "Your turn. Enter an alphanumeric value: ";
            std:: cin >> user_input;

            while (!(board->input_check(user_input))) {
                
                std::cout << "\t" << "Invalid input. Please enter an available alphanumeric value: ";
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                std::cin >> user_input;
                
            }              

            move = board->input_transform(user_input);

        } else {

            move = get_move(*board, max_time);
        }

        asg::line_break(30);
        
        board->update(move);
        board->print_board();
    }
    
    asg::line_break(30);

    switch (board->get_result()) {

        case 0:
            std::cout << "\t" << "Draw." << std::endl;
            break;

        case 1:
            std::cout << "\t" << "You win!" << std::endl;
            break;

        case 2:
            std::cout << "\t" << "You lose." << std::endl;
            break;
    }

    delete board;
}

