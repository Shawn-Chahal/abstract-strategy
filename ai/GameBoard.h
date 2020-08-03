#ifndef H_GAMEBOARD
#define H_GAMEBOARD

#include <iostream>
#include <vector>

class GameBoard {
    public:
     
        const char P1_MARKER = 'O';
        const char P2_MARKER = 'X';

        const std::string LINE_BREAK = "\n\t-----------------------------\n";

        int player, last_move, result;
        std::vector<std::vector<int>> game_state;
        std::vector<int> available_moves;
        std::vector<double> difficulty;

        // Copy constructor
        virtual ~GameBoard() {}
        virtual GameBoard* clone() const = 0;

        // Template virtual methods
        virtual int transform_input(std::string user_input) = 0;
        virtual void ai_output(int move) = 0;
        virtual void how_to_play() = 0;
        virtual int check_input(std::string user_input) = 0;
        virtual void display() = 0;
        virtual void print_name() = 0;
        virtual void initialize_board() = 0;
        virtual void update(int move) = 0; // Store last_move then update the game_state, result, player, and available_moves.

        // Inherited methods
        int switch_player(int player) {
            if (player == 1) {
                return 2;
            } else {
                return 1;
            }
        }    

        int get_player() { return player; }
        int get_result() { return result; }
        int get_game_state(int row, int col) { return game_state[row][col]; }
        int get_available_moves(int move) { return available_moves[move]; }
        int get_num_moves() { return available_moves.size(); }

        double get_difficulty(int d_index) { return difficulty[d_index]; }

};

#endif