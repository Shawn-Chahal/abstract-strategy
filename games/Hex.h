#ifndef H_HEX
#define H_HEX

#include "../ai/GameBoard.h"

#include <vector>
#include <string>

class Hex: public GameBoard {
    private:

        const int N_ROW = 7;
        const int N_COL = 7;
        const int N_MOVES = N_ROW * N_COL;

        void print_spaces(int n_spaces);
        std::string print_tile(int player);
        int check_link(std::vector<std::vector<int>> game_state, int player, std::vector<std::vector<int>> link_history, int tile_row, int tile_col);

    public:
                   
        Hex* clone() const { return new Hex(*this); }

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