#ifndef H_CONNECTFOUR
#define H_CONNECTFOUR

#include "../ai/GameBoard.h"

#include <iostream>
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

        int next_player(std::vector<std::vector<int>> game_state, int previous_player) { return switch_player(previous_player); }
        

        void initialize_board() {
            result = -1;
            player = 1;
            game_state = initialize_state();
            available_moves = update_available_moves(game_state, available_moves, player);
            difficulty = {3, 5, 10, 15, 30};
        }


        int transform_input(std::string user_input) {

            int move = user_input[0] - '1';

            return move;
        }


        int check_input(std::string user_input) {
            
            if (user_input.length() != 1) {
                return 0;
            }

            int move = user_input[0] - '1';

            if (move >= 0 && move < available_moves.size()) {
                return available_moves[move];
            } else {
                return 0;
            }
        }


        void display() {
            
            std::cout << "\t";
            
            for (int j = 0; j < N_COL; j++) {

                std::cout << "   " << j + 1 << "  ";
            }

            std::cout << " " << std::endl;
            
            std::cout << "\t";
            for (int j = 0; j < N_COL; j++) {

                std::cout << "|     ";
            }

            std::cout << "|" << std::endl;


            for (int i = 0; i < N_ROW; i++) {
                std::cout << "\t";
                for (int j = 0; j < N_COL; j++) {
                    switch (game_state[i][j]) {
                        case 0:
                            std::cout << "|     ";
                            break;
                        case 1:
                            std::cout << "|  " << P1_MARKER << "  ";
                            break;
                        case 2:
                            std::cout << "|  " << P2_MARKER << "  ";
                            break;
                    }
                }

                std::cout << "|" << std::endl;
                std::cout << "\t" << "|";

                for (int j = 0; j < N_COL; j++) {
                    std::cout << "-----|";
                }

                std::cout << std::endl;
            }

            std::cout << std::endl;
        }


        std::vector<std::vector<int>> update_state(std::vector<std::vector<int>> game_state, int player, int move) {

            for (int row = game_state.size() - 1; row >= 0; row--) {
                if (game_state[row][move] == 0) {
                    game_state[row][move] = player;
                    break;
                }
            }   
            return game_state;
        }


        std::vector<int> update_available_moves(std::vector<std::vector<int>> game_state, std::vector<int> available_moves, int player) {
            
            available_moves = std::vector<int>(N_MOVES, 1);

            for (int j=0; j < available_moves.size(); j++) {
                if (game_state[0][j] > 0) {
                    available_moves[j] = 0;
                }
            }
            return available_moves;
        }


        int update_result(std::vector<std::vector<int>> game_state, int last_player, int last_move) {

            const int CONNECT = 4;
            int count;

            for (int i = 0; i < N_ROW; i++) {
                for (int j = 0; j < N_COL; j++) {
                    if (game_state[i][j] == last_player) {
                        

                        /* Check right */
                        if (j <= N_COL - CONNECT) {
                            count = 1;

                            for (int k = 1; k < CONNECT; k++) {
                                if (game_state[i][j + k] == last_player) {
                                    count++;
                                } else {
                                    break;
                                }
                            }
                            
                            if (count == CONNECT) {
                                return last_player;
                            }
                        }

                        /* Check down */
                        if (i <= N_ROW - CONNECT) {
                            count = 1;

                            for (int k = 1; k < CONNECT; k++) {
                                if (game_state[i + k][j] == last_player) {
                                    count++;
                                } else {
                                    break;
                                }
                            }

                            if (count == CONNECT) {
                                return last_player;
                            }
                        }

                        /* Check right-down */
                        if (i <= N_ROW - CONNECT && j <= N_COL - CONNECT) {
                            count = 1;
                            
                            for (int k = 1; k < CONNECT; k++) {
                                if (game_state[i + k][j + k] == last_player) {
                                    count++;
                                } else {
                                    break;
                                }
                            }
                            
                            if (count == CONNECT) {
                                return last_player;
                            }
                        }

                        /* Check left-down */
                        if (i <= N_ROW - CONNECT && j >= CONNECT - 1) {
                            count = 1;
                            
                            for (int k = 1; k < CONNECT; k++) {
                                if (game_state[i + k][j - k] == last_player) {
                                    count++;
                                } else {
                                    break;
                                }
                            }

                            if (count == CONNECT) {
                                return last_player;
                            }
                        }
                    }
                }
            }

            for (int j = 0 ; j < N_COL; j++) {
                if (game_state[0][j] == 0) {
                    return -1;
                }
            }
            
            return 0;

        }


        std::vector<std::vector<int>> initialize_state() {

            return std::vector<std::vector<int>>(N_ROW, std::vector<int>(N_COL, 0));
        }


        void how_to_play() {

            std::cout << "\t" << "Connect four consecutive tiles in a straight line." << std::endl;
            std::cout << "\t" << "The tiles can be horizontal, vertical, or diagonal." << std::endl;
            std::cout << "\t" << "Token are inserted from the top of the column." << std::endl;
            std::cout << "\t" << "E.g., if you want to play on column = 1," << std::endl; 
            std::cout << "\t" << "then input 1 when prompted." << std::endl;

        }


        void ai_output(int move) {
            std::cout << move + 1;
        }

        void print_name() {
            std::cout << NAME;
        }
    
};

#endif