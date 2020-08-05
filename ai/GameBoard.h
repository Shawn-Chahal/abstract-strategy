#ifndef H_GAMEBOARD
#define H_GAMEBOARD

#include <vector>
#include <string>

class GameBoard {
    private:

    public:
     
        const char P1_MARKER = 'O';
        const char P2_MARKER = 'X';
        
        int player, last_move, result;
        std::vector<std::vector<int>> game_state;
        std::vector<int> available_moves;
        std::vector<double> difficulty;

        virtual ~GameBoard() {}
        virtual GameBoard* clone() const = 0;

        // Template virtual methods
        virtual std::vector<std::vector<int>> initialize_game_state() = 0;
        virtual std::vector<int> initialize_available_moves() = 0;

        virtual int check_input(std::string user_input) = 0;
        virtual int transform_input(std::string user_input) = 0;

        virtual void ai_output(int move) = 0;
        virtual void how_to_play() = 0;
        virtual void print_board() = 0;
        virtual void print_name() = 0;
        virtual void initialize_board() = 0;

        virtual std::vector<std::vector<int>> update_game_state(int move) = 0;
        virtual int update_result(int move) = 0;
        virtual int update_player(int move) = 0;
        virtual std::vector<int> update_available_moves(int move) = 0;
        
        // Inherited methods
        double get_difficulty(int d_index);

        int get_player();
        int get_result();
        int get_game_state(int row, int col);
        int get_available_moves(int move);
        int get_num_moves();
        int switch_player(int player);

        void update(int move);
};

#endif