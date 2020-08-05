#ifndef H_REVERSI
#define H_REVERSI

#include "../ai/GameBoard.h"

#include <vector>
#include <string>


class Reversi: public GameBoard {
    private:

        const std::string NAME = "Reversi (Othello)";
        const int N_ROW = 8;
        const int N_COL = 8;
        const int N_MOVES = N_ROW * N_COL;

        std::vector<int> check_link(std::vector<std::vector<int>> game_state, int row, int col);
        int move_available(std::vector<std::vector<int>> game_state, int player, int move);
        std::vector<int> update_local_available_moves(int player);

    public:
        
        Reversi* clone() const { return new Reversi(*this); }

        std::vector<std::vector<int>> initialize_game_state();
        std::vector<int> initialize_available_moves();
        int check_input(std::string user_input);
        int transform_input(std::string user_input);
        void ai_output(int move);
        void how_to_play();
        void print_board();
        void print_name();
        void initialize_board();

        std::vector<std::vector<int>> update_game_state(int move);
        int update_result(int move);
        int update_player(int move);
        std::vector<int> update_available_moves(int move);
        
};

#endif