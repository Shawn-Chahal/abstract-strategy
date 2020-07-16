#include <iostream>
#include <vector>
#include <cstdio>
#include "connect-four.h"


int main() {
    
    int play_again = 1;
    
    while (play_again == 1) {

        std::vector<std::vector<int>> game_state (N_ROW, std::vector<int> (N_COL, 0));
        std::vector<int> avail_col (N_COL, 1);
        int col, score, max_score;
        int result = -1;
        int player = 1;
        char s_col, s_play_again;        

        std::cout << "\n\nConnect Four\n" << std::endl;
        std::cout << "Player markers\nYou:      " << P1_MARKER << "\nComputer: " << P2_MARKER << "\n" << std::endl;
        print_board(game_state, avail_col);

        while (result == -1) {

            if (player == 1) {
                std::cout << "Your turn. Enter a column number: ";
                std::cin >> s_col;
                fflush(stdin);          
                col = s_col - '0';

                while (check_input(col, avail_col) == 0) {
                    std::cout << "Please enter a valid column number: ";
                    std::cin >> s_col;
                    fflush(stdin);
                    col = s_col - '0';
                }

                std::cout << "Your move: " << col << std::endl;                
            } else {
                std::cout << "Computer is thinking.";
                max_score = -S_INITIAL;

                for (int j = 0; j < N_COL; j++) {
                    std::cout << ".";

                    if (avail_col[j] == 1) {
                        score = get_score(game_state, avail_col, player, j, 1, max_score);

                        if (score > max_score) {
                            max_score = score;
                            col = j;
                        }
                    }
                }
                
                std::cout << "\nComputer's move: " << col << std::endl;
            }

            std::cout << "\n" << std::endl;
            game_state = update_state(game_state, player, col);
            avail_col = update_avail_col(game_state, avail_col);
            print_board(game_state, avail_col);
            result = check_state(game_state);
            player = switch_player(player);
        }
        
        switch (result) {

            case 0:
                std::cout << "Draw.\n" << std::endl;
                break;

            case 1:
                std::cout << "You win!\n" << std::endl;
                break;

            case 2:
                std::cout << "You lose.\n" << std::endl;
                break;
        }

        do {
            std::cout << "Play again? Y/N: ";
            std::cin >> s_play_again;
            fflush(stdin);

            if (s_play_again == 'Y' || s_play_again == 'y' ) {
                play_again = 1;
            } else if (s_play_again == 'N' || s_play_again == 'n' ) {
                play_again = 0;
            }
        } while (s_play_again != 'Y' && s_play_again != 'y' && s_play_again != 'N' && s_play_again != 'n');
    }
    return 0;
}
