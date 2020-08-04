#include "GameBoard.h"

double GameBoard::get_difficulty(int d_index) { return difficulty[d_index]; }
int GameBoard::get_player() { return player; }
int GameBoard::get_result() { return result; }
int GameBoard::get_game_state(int row, int col) { return game_state[row][col]; }
int GameBoard::get_available_moves(int move) { return available_moves[move]; }
int GameBoard::get_num_moves() { return available_moves.size(); }
int GameBoard::switch_player(int player) { return (player == 1) ? 2 : 1; }  

void GameBoard::update(int move) {
    last_move = move;
    game_state = update_state(game_state, player, move);
    result = update_result(game_state, player, move);
    player = next_player(game_state, player);
    available_moves = update_available_moves(game_state, available_moves, player);
}
