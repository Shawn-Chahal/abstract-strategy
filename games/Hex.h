#ifndef H_HEX
#define H_HEX

#include "../ai/GameBoard.h"

#include <vector>
#include <string>


class Hex: public GameBoard {
    private:

        const std::string NAME = "Hex (7 x 7)";
        const int N_ROW = 7;
        const int N_COL = 7;
        const int N_MOVES = N_ROW * N_COL;

        std::string print_tile(int player);
        void print_spaces(int n_spaces);
        int check_link(std::vector<std::vector<int>> game_state, int player, std::vector<std::vector<int>> link_history, int tile_row, int tile_col);
        int update_result(std::vector<std::vector<int>> game_state, int last_player, int last_move);

    public:
                   
        Hex* clone() const { return new Hex(*this); }

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