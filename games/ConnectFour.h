#ifndef H_CONNECTFOUR
#define H_CONNECTFOUR

#include "../ai/GameBoard.h"

#include <vector>
#include <string>

class ConnectFour: public GameBoard {
    private:

        const std::string NAME = "Connect Four";
        const int N_ROW = 6;
        const int N_COL = 7;
        const int N_MOVES = N_COL;

    public:
        
        ConnectFour* clone() const { return new ConnectFour(*this); }

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