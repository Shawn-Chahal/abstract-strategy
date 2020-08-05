#ifndef H_TICTACTOE
#define H_TICTACTOE

#include "../ai/StrategyGame.h"

#include <vector>
#include <string>

class TicTacToe: public GameBoard {
    private:

        const std::string NAME = "Tic-Tac-Toe";    
        const int N_ROW = 3;
        const int N_COL = 3;
        const int N_MOVES = N_ROW * N_COL;

    public:
        
        TicTacToe* clone() const { return new TicTacToe(*this); }

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