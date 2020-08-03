#include "ai/StrategyGame.h"
#include "ai/GameBoard.h"
#include "games/ConnectFour.h"
#include "games/Hex.h"
#include "games/Reversi.h"
#include "games/TicTacToe.h"

#include <iostream>
#include <vector>
#include <string>


// Need to declare these globally
const std::string INDENT = "   ";
const std::string LINE_BREAK = "\n" + INDENT + "-----------------------------\n";


int menu_input (int size) {

    int index = -1;

    while (index == -1) {
        if (!(std::cin >> index)){
            std::cout << INDENT << "Invalid input. Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            index = -1;
        } else if (index < 1 || index > size) {
            std::cout << INDENT << "Index unavailable. Please enter a number between 1 and " << size << ": ";
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            index = -1;
        }
    }        
 
    return index;
}


int main() {
    
    int play_again = 1; 

    while (play_again == 1) {


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

        int g_index = menu_input(games_list.size());
       
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

        play_again = menu_input(options.size());

    }

    return 0;
}
