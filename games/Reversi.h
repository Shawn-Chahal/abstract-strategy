#ifndef H_REVERSI
#define H_REVERSI

#include "../ai/GameBoard.h"

#include <vector>
#include <string>

class Reversi: public GameBoard {
    private:

        const int N_ROW = 8;
        const int N_COL = 8;
        const int N_MOVES = N_ROW * N_COL;

        std::vector<int> check_link(std::vector<std::vector<int>> game_state, int row, int col);
        int move_available(std::vector<std::vector<int>> game_state, int player, int move);
        std::vector<int> update_local_available_moves(int local_player);

    public:
        
        Reversi* clone() const { return new Reversi(*this); }

        std::string initialize_name();
        std::vector<double> initialize_difficulty();
        std::vector<std::vector<int>> initialize_game_state();
        std::vector<int> initialize_available_moves();
        int input_check(std::string user_input);
        int input_transform(std::string user_input);
        void print_ai_move(int move);
        void print_rules();
        void print_board();

        std::vector<std::vector<int>> update_game_state(int move);
        int update_result(int move);
        int update_player(int move);
        std::vector<int> update_available_moves(int move);
        
};

#endif