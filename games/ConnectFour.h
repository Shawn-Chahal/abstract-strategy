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

        int update_result(std::vector<std::vector<int>> game_state, int last_player, int last_move);

    public:
        
        ConnectFour* clone() const { return new ConnectFour(*this); }
        
        int transform_input(std::string user_input);
        int check_input(std::string user_input);
        void initialize_board();
        void display();
        void how_to_play();
        void ai_output(int move);
        void print_name();
        void update(int move);

};

#endif