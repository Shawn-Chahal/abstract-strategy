#ifndef H_CONNECTFOUR
#define H_CONNECTFOUR

#include "../ai/GameBoard.h"

#include <vector>
#include <string>

class ConnectFour: public GameBoard {
    private:

        const int N_ROW = 6;
        const int N_COL = 7;
        const int N_MOVES = N_COL;

    public:
        
        ConnectFour* clone() const { return new ConnectFour(*this); }

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