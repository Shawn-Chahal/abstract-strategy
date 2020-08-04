#ifndef H_GAMEBOARD
#define H_GAMEBOARD

#include "asg.h"

#include <iostream>
#include <vector>


class GameBoard {
    private:

    public:
     
        const char P1_MARKER = 'O';
        const char P2_MARKER = 'X';
        
        int player, last_move, result;
        std::vector<std::vector<int>> game_state;
        std::vector<int> available_moves;
        std::vector<double> difficulty;

        virtual ~GameBoard() {}
        virtual GameBoard* clone() const = 0;

        // Template virtual methods
        virtual std::vector<std::vector<int>> initialize_state() = 0;
        
        virtual int check_input(std::string user_input) = 0;
        virtual int transform_input(std::string user_input) = 0;

        virtual void ai_output(int move) = 0;
        virtual void how_to_play() = 0;
        virtual void display() = 0;
        virtual void print_name() = 0;
        virtual void initialize_board() = 0;

        virtual std::vector<std::vector<int>> update_state(std::vector<std::vector<int>> game_state, int player, int move) = 0;
                
        virtual int update_result(std::vector<std::vector<int>> game_state, int last_player, int last_move) = 0;
        
        virtual int next_player(std::vector<std::vector<int>> game_state, int previous_player) = 0;
        
        virtual std::vector<int> update_available_moves(std::vector<std::vector<int>> game_state, std::vector<int> available_moves, int player) = 0;
        
        // Inherited methods
        double get_difficulty(int d_index) { return difficulty[d_index]; }
        int get_player() { return player; }
        int get_result() { return result; }
        int get_game_state(int row, int col) { return game_state[row][col]; }
        int get_available_moves(int move) { return available_moves[move]; }
        int get_num_moves() { return available_moves.size(); }
        int switch_player(int player) { return (player == 1) ? 2 : 1; }  


        void update(int move) {
            last_move = move;
            game_state = update_state(game_state, player, move);
            result = update_result(game_state, player, move);
            player = next_player(game_state, player);
            available_moves = update_available_moves(game_state, available_moves, player);

        }
        

};


#endif