#ifndef H_TICTACTOE
#define H_TICTACTOE

#include "../ai/StrategyGame.h"

#include <vector>
#include <string>

class TicTacToe: public GameBoard {
    private:
  
        const int N_ROW = 3;
        const int N_COL = 3;
        const int N_MOVES = N_ROW * N_COL;

    public:
        
        TicTacToe* clone() const { return new TicTacToe(*this); }

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