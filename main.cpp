#include "ai/StrategyGame.h"
#include "ai/GameBoard.h"
#include "games/ConnectFour.h"
#include "games/Hex.h"
#include "games/Reversi.h"
#include "games/TicTacToe.h"

#include <iostream>
#include <vector>
#include <string>


int main() {
    
    int play_again = 1; 

    while (play_again == 1) {

        // Need to declare these globally
        const std::string INDENT = "   ";
        const std::string LINE_BREAK = "\n" + INDENT + "-----------------------------\n";

        StrategyGame app;

        std::vector<std::string> games_list = {"Connect Four", "Hex (7 x 7)", "Reversi (Othello)", "Tic-Tac-Toe"};
        std::cout << LINE_BREAK << std::endl;
        std::cout << INDENT << "Abstract Strategy Games" << std::endl;
        std::cout << INDENT << "by Shawn Chahal" << std::endl;
        std::cout << LINE_BREAK << std::endl;
        std::cout << INDENT << "Select a game:" << std::endl << std::endl;
        for (int i = 0; i < games_list.size(); i++) {
            std::cout << INDENT << i + 1 << ") " << games_list[i] << std::endl;
        }
        std::cout << INDENT << std::endl;
        std::cout << INDENT << "Enter a number: ";

        int g_index = -1;

        while (g_index == -1) {
            if (!(std::cin >> g_index)){
                std::cout << INDENT << "Invalid input. Please enter a number: ";
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                g_index = -1;
            } else if (g_index < 1 || g_index > games_list.size()) {
                std::cout << INDENT << "Game index unavailable. Please enter a number between 1 and " << games_list.size() << ": ";
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                g_index = -1;
            }
        }        
        
        std::cout << LINE_BREAK << std::endl;

        if (games_list[g_index - 1] == "Tic-Tac-Toe") {
            TicTacToe game;
            app.run(game);

        } else if (games_list[g_index - 1] == "Connect Four") {
            ConnectFour game;
            app.run(game);
            
        } else if (games_list[g_index - 1] == "Reversi (Othello)") {
            Reversi game;
            app.run(game);

        } else if (games_list[g_index - 1] == "Hex (7 x 7)") {
            Hex game;
            app.run(game);
        }

        std::vector<std::string> options = {"Return to main menu", "Exit"};
        std::cout << std::endl;
        for (int i = 0; i < options.size(); i++) {
            std::cout << INDENT << i + 1 << ") " << options[i] << std::endl;
        }
        std::cout << INDENT << std::endl;
        std::cout << INDENT << "Enter a number: ";

        int e_index = -1;

        while (e_index == -1) {
            if (!(std::cin >> e_index)){
                std::cout << INDENT << "Invalid input. Please enter a number: ";
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                e_index = -1;
            } else if (e_index < 1 || e_index > options.size()) {
                std::cout << INDENT << "Option unavailable. Please enter a number between 1 and " << options.size() << ": ";
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                e_index = -1;
            }
        }

        play_again = e_index;

    }
    return 0;
}
