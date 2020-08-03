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
        int next_player(std::vector<std::vector<int>> game_state, int previous_player);
        std::vector<int> update_available_moves(std::vector<std::vector<int>> game_state, int player);
        std::vector<std::vector<int>> update_state(std::vector<std::vector<int>> game_state, int player, int move);
        int update_result(std::vector<std::vector<int>> game_state, int last_player, int last_move);
        std::vector<std::vector<int>> initialize_state();

    public:
        
        Reversi* clone() const { return new Reversi(*this); }

        void initialize_board();
        int transform_input(std::string user_input);
        int check_input(std::string user_input);
        void display();
        void how_to_play();
        void ai_output(int move);
        void print_name();
        void update(int move);

};

#endif