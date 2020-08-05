#include "GameBoard.h"

std::string GameBoard::get_name() { return name; }
double GameBoard::get_difficulty(int d_index) { return difficulty[d_index]; }
int GameBoard::get_player() { return player; }
int GameBoard::get_result() { return result; }
int GameBoard::get_game_state(int row, int col) { return game_state[row][col]; }
int GameBoard::get_available_moves(int move) { return available_moves[move]; }
int GameBoard::get_num_moves() { return available_moves.size(); }
int GameBoard::switch_player(int player) { return (player == 1) ? 2 : 1; }  

void GameBoard::initialize() {
    result = -1;
    player = 1;
    name = initialize_name();
    difficulty = initialize_difficulty();
    game_state = initialize_game_state();
    available_moves = initialize_available_moves();
}

void GameBoard::update(int move) {
    last_move = move;
    game_state = update_game_state(move);
    result = update_result(move);
    player = update_player(move);
    available_moves = update_available_moves(move);
}
