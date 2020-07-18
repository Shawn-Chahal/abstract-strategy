#include <iostream>
#include <vector>
#include <random>
#include "connect-four.h"


int main() {
    
    int play_again = 1; 

    while (play_again == 1) {

        ConnectFour game;

        double score, max_score;
        int move, d_index;
        int player = 1;
        char s_play_again;
             
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
       
        game.set_difficulty(d_index);

        std::cout << std::endl << std::endl;
        std::cout << game.INDENT << "Player markers" << std::endl;
        std::cout << game.INDENT << "You:      " << game.P1_MARKER << std::endl;
        std::cout << game.INDENT << "Computer: " << game.P2_MARKER << std::endl << std::endl;

        game.print_board();

        while (game.result == -1) {

            if (player == 1) {
                std::cout << game.INDENT << "Your turn. Enter a number: ";
                move = -1;

                while (move == -1) {
                    if (!(std::cin >> move)){
                        std::cout << game.INDENT << "Invalid input. Please enter a number: ";
                        std::cin.clear();
                        std::cin.ignore(10000,'\n');
                        move = -1;
                    } else if (!game.check_input(move)) {
                        std::cout << game.INDENT << "Move unavailable. Please enter an available number:  ";
                        std::cin.clear();
                        std::cin.ignore(10000,'\n');
                        move = -1;
                    }
                }              
            } else {
                move = game.get_move(player);
            }

            std::cout << std::endl;
            game.end_turn(player, move);
            player = game.switch_player(player);
        }
        
        switch (game.result) {

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
