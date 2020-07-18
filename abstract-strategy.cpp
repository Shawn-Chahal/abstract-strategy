#include <iostream>
#include <vector>
#include <random>
#include "connect-four.h"


int main() {
    
    int play_again = 1;
    
    

    while (play_again == 1) {

        ConnectFour game;

        double score, max_score;
        int col, d_index;
        int result = -1;
        int player = 1;
        char s_play_again;
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(0, game.N_MOVES - 1);        

        std::cout << std::endl << std::endl;
        std::cout << game.INDENT << game.NAME << std::endl << std::endl;
        std::cout << game.INDENT << "Select a difficulty." << std::endl << std::endl;
        std::cout << game.INDENT << "1) Easy" << std::endl;
        std::cout << game.INDENT << "2) Medium" << std::endl;
        std::cout << game.INDENT << "3) Hard" << std::endl << std::endl;
        std::cout << game.INDENT << "Enter a number: ";

        d_index = -1;

        while (d_index == -1) {
            if (!(std::cin >> d_index)){
                std::cout << game.INDENT << "Invalid input. Please enter a number: ";
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                d_index = -1;
            } else if (d_index < 1 || d_index > game.difficulty.size()) {
                std::cout << game.INDENT << "Difficulty unavailable. Please enter a number between 1 and " << game.difficulty.size() << ": ";
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                d_index = -1;
            }
        }        
       
        std::cout << std::endl << std::endl;
        std::cout << game.INDENT << "Player markers" << std::endl;
        std::cout << game.INDENT << "You:      " << game.P1_MARKER << std::endl;
        std::cout << game.INDENT << "Computer: " << game.P2_MARKER << std::endl << std::endl;

        game.print_board(game.game_state, game.available_moves);

        while (result == -1) {

            if (player == 1) {
                std::cout << game.INDENT << "Your turn. Enter a number: ";
                col = -1;

                while (col == -1) {
                    if (!(std::cin >> col)){
                        std::cout << game.INDENT << "Invalid input. Please enter a number: ";
                        std::cin.clear();
                        std::cin.ignore(10000,'\n');
                        col = -1;
                    } else if (!game.check_input(col)) {
                        std::cout << game.INDENT << "Move unavailable. Please enter an available number:  ";
                        std::cin.clear();
                        std::cin.ignore(10000,'\n');
                        col = -1;
                    }
                }              
            } else {
                std::cout << game.INDENT << "Computer is thinking.";
                std::vector<int> attempted_moves = std::vector<int>(game.N_MOVES, 0);
                max_score = -game.S_INITIAL;

                while (!game.check_moves(attempted_moves)) {
                    int j = distribution(generator);

                    if (j >=0 && j < game.N_MOVES){
                        if (!attempted_moves[j]) {

                            attempted_moves[j] = 1;
                            std::cout << ".";
                            
                            if (game.available_moves[j] == 1) {
                                score = game.get_score(game.game_state, game.available_moves, player, j, 1, game.difficulty[d_index - 1], max_score);
                
                                if (score > max_score) {
                                    max_score = score;
                                    col = j;
                                }
                            }
                        }
                    }
                }
                
                std::cout << std::endl;
                std::cout << game.INDENT << "Computer's move: " << col << std::endl;
            }

            std::cout << std::endl;
            

            game.end_turn(player, col);
            result = game.check_state(game.game_state);
            player = game.switch_player(player);
        }
        
        switch (result) {

            case 0:
                std::cout << game.INDENT << "Draw." << std::endl;
                break;

            case 1:
                std::cout << game.INDENT << "You win!" << std::endl;
                break;

            case 2:
                std::cout << game.INDENT << "You lose." << std::endl;
                break;
        }

        do {
            std::cout << game.INDENT << "Play again? Y/N: ";
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
