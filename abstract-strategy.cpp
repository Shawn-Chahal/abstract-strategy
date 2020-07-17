#include <iostream>
#include <vector>
#include "connect-four.h"


int main() {
    
    int play_again = 1;
    
    while (play_again == 1) {

        std::vector<std::vector<int>> game_state (N_ROW, std::vector<int> (N_COL, 0));
        std::vector<int> avail_col (N_COL, 1);
        double score, max_score;
        int col;
        int result = -1;
        int player = 1;
        char s_play_again;        

        std::cout << std::endl << std::endl;
        std::cout << INDENT << "Connect Four" << std::endl << std::endl;;
        std::cout << INDENT << "Player markers" << std::endl;
        std::cout << INDENT << "You:      " << P1_MARKER << std::endl;
        std::cout << INDENT << "Computer: " << P2_MARKER << std::endl << std::endl;

        print_board(game_state, avail_col);

        while (result == -1) {

            if (player == 1) {
                std::cout << INDENT << "Your turn. Enter a number: ";
                col = -1;

                while (col == -1) {
                    if (!(std::cin >> col)){
                        std::cout << INDENT << "Invalid input. Please enter a number: ";
                        std::cin.clear();
                        std::cin.ignore(10000,'\n');
                        col = -1;
                    } else if (!check_input(col, avail_col)) {
                        std::cout << INDENT << "Move unavailable. Please enter an available number:  ";
                        std::cin.clear();
                        std::cin.ignore(10000,'\n');
                        col = -1;
                    }
                }              
            } else {
                std::cout << INDENT << "Computer is thinking.";
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
                
                std::cout << std::endl;
                std::cout << INDENT << "Computer's move: " << col << std::endl;
            }

            std::cout << std::endl;
            
            game_state = update_state(game_state, player, col);
            avail_col = update_avail_col(game_state, avail_col);
            print_board(game_state, avail_col);
            result = check_state(game_state);
            player = switch_player(player);
        }
        
        switch (result) {

            case 0:
                std::cout << INDENT << "Draw." << std::endl;
                break;

            case 1:
                std::cout << INDENT << "You win!" << std::endl;
                break;

            case 2:
                std::cout << INDENT << "You lose." << std::endl;
                break;
        }

        do {
            std::cout << INDENT << "Play again? Y/N: ";
            std::cin >> s_play_again;
            std::cin.clear();
            std::cin.ignore(10000,'\n');

            if (s_play_again == 'Y' || s_play_again == 'y' ) {
                play_again = 1;
            } else if (s_play_again == 'N' || s_play_again == 'n' ) {
                play_again = 0;
            }
        } while (s_play_again != 'Y' && s_play_again != 'y' && s_play_again != 'N' && s_play_again != 'n');
    }
    return 0;
}
