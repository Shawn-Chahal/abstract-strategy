#include <iostream>
#include <vector>
#include <random>
#include "Node.h"
#include "OneStepGame.h"
#include "ConnectFour.h"
#include "Hex.h"
#include "Reversi.h"
#include "TicTacToe.h"


int main() {
    
    int play_again = 1; 

    while (play_again == 1) {

        OneStepGame menu;
        
        std::vector<std::string> games_list = {"Connect Four", "Hex", "Reversi (Othello)", "Tic-Tac-Toe"};

        std::cout << menu.LINE_BREAK << std::endl;

        std::cout << menu.INDENT << "Abstract Strategy Games" << std::endl;
        std::cout << menu.INDENT << "by Shawn Chahal" << std::endl;

        std::cout << menu.LINE_BREAK << std::endl;

        std::cout << menu.INDENT << "Select a game:" << std::endl << std::endl;
        for (int i = 0; i < games_list.size(); i++) {
            std::cout << menu.INDENT << i + 1 << ") " << games_list[i] << std::endl;
        }

        std::cout << menu.INDENT << std::endl;
        std::cout << menu.INDENT << "Enter a number: ";

        int g_index = -1;

        while (g_index == -1) {
            if (!(std::cin >> g_index)){
                std::cout << menu.INDENT << "Invalid input. Please enter a number: ";
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                g_index = -1;
            } else if (g_index < 1 || g_index > games_list.size()) {
                std::cout << menu.INDENT << "Game index unavailable. Please enter a number between 1 and " << games_list.size() << ": ";
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                g_index = -1;
            }
        }        
        
        std::cout << menu.LINE_BREAK << std::endl;

        if (games_list[g_index - 1] == "Tic-Tac-Toe") {
            TicTacToe game;
            game.run();

        } else if (games_list[g_index - 1] == "Connect Four") {
            ConnectFour game;
            game.run();
            
        } else if (games_list[g_index - 1] == "Reversi (Othello)") {
            Reversi game;
            game.run();

        } else if (games_list[g_index - 1] == "Hex") {
            Hex game;
            game.run();
        }

        std::vector<std::string> options = {"Return to main menu", "Exit"};
        std::cout << std::endl;
        for (int i = 0; i < options.size(); i++) {
            std::cout << menu.INDENT << i + 1 << ") " << options[i] << std::endl;
        }
        std::cout << menu.INDENT << std::endl;
        std::cout << menu.INDENT << "Enter a number: ";

        int e_index = -1;

        while (e_index == -1) {
            if (!(std::cin >> e_index)){
                std::cout << menu.INDENT << "Invalid input. Please enter a number: ";
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                e_index = -1;
            } else if (e_index < 1 || e_index > options.size()) {
                std::cout << menu.INDENT << "Option unavailable. Please enter a number between 1 and " << options.size() << ": ";
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                e_index = -1;
            }
        }

        play_again = e_index;

    }
    return 0;
}
