#include "ai/StrategyGame.h"
#include "ai/GameBoard.h"
#include "ai/asg.h"
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


        StrategyGame app;

        std::vector<std::string> games_list = {"Connect Four", "Hex (7 x 7)", "Reversi (Othello)", "Tic-Tac-Toe"};
        asg::line_break(30);
        std::cout << "\t" << "Abstract Strategy Games" << std::endl;
        std::cout << "\t" << "by Shawn Chahal" << std::endl;
        asg::line_break(30);
        std::cout << "\t" << "Select a game:" << std::endl << std::endl;
        for (int i = 0; i < games_list.size(); i++) {
            std::cout << "\t" << i + 1 << ") " << games_list[i] << std::endl;
        }
        std::cout << "\t" << std::endl;
        std::cout << "\t" << "Enter a number: ";

        int g_index = asg::menu_input(games_list.size());
       
        asg::line_break(30);

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
            std::cout << "\t" << i + 1 << ") " << options[i] << std::endl;
        }
        std::cout << "\t" << std::endl;
        std::cout << "\t" << "Enter a number: ";

        play_again = asg::menu_input(options.size());

    }

    return 0;
}
