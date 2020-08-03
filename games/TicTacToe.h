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
        
        int update_result(std::vector<std::vector<int>> game_state, int last_player, int last_move);

    public:
        
        TicTacToe* clone() const { return new TicTacToe(*this); }

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