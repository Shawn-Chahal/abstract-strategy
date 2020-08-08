# Abstract Strategy Games 
An API which allows for the easy creation of abstract strategy games in C++. The concept is that an **artificial intelligence (AI)** using **Monte Carlo tree search (MCTS)** with **multithreading** can be coded once and play multiple games including games that are created after the AI was written. This was done through the creation of several classes which can be found in the [ai](./ai) directory. Four fully functional games have already been created and can be found in the [games](./games) directory: 

1. Connect Four
2. Hex (7 x 7)
3. Reversi (Othello)
4. Tic-Tac-Toe

Before creating a new game, we must understand the abstract base class `GameBoard` which a newly created game class will need to inherit. This abstract class has been programmed to interact with the AI found in `class StrategyGame`. Therefore, all one needs to do to make a new game class is to inherit `GameBoard` and define its pure virtual methods.

## `class GameBoard`
The `GameBoard` is an abstract class which is to be inherited by new games that are created. The GameBoard is essentially a representation of the current state of the game. It sepcifies the required variables and methods that must be defined by the derived class and also provides a few of its own:

### Variables
* `const char P1_MARKER = 'O'` and `const char P2_MARKER = 'X'` are the symbols that will represent players 1 and 2, respectively.
* `int player`: The current player. Can have a value of `1` or `2`. 
* `std::string name`: A string containing the name of the game.
* `std::vector<double> difficulty`: A vector containing five `double`s where each double represents a the amount of time in seconds the AI has to make a decision. The values should be increasing in size, with `difficulty[2]` being the average turn length for the game being created.
* `std::vector<std::vector<int>> game_state`: A matrix which represents the current state of the pieces on the board. Typically, `game_state[i][j]` (representing a tile in row `i` and column `j`) contains three possible values: `0`: The tile is empty, `1`: Player 1 occupys the tile, `2` Player 2 occupys the tile.
* `std::vector<int> available_moves`: A vector that represents every possible move that can be played. For a given move `m`, `available_moves[m]`, can have two values: `0`: move `m` is unvailable, `1`: move `m` is available.
* `int last_move`: The last move that was played. It's value represnts the index of a move found in `std::vector<int> available_moves`.
* `int result`: The current result of the game. Can have values of: `-1`: The game has not ended yet, `0`: Draw, `1`: Player 1 wins, `2`: Player 2 wins.


### Pure Virtual Methods
Keep in mind that when defining these Virtual Methods, you will have access to all the variables just mentioned.

#### Cloning
* `virtual GameBoard* clone() const`: Allows for the creation of copies of the derived class. This is required by the AI.

#### Initialization
* `virtual std::string initialize_name()`: Should return `std::string name`.
* `virtual std::vector<double> initialize_difficulty()`: Should return `std::vector<double> difficulty`.
* `virtual std::vector<std::vector<int>> initialize_game_state()`: Should return the `std::vector<std::vector<int>> game_state` as it would appear at the start of the game.
* `virtual std::vector<int> initialize_available_moves()`: Should return the `std::vector<int> available_moves` for player 1 at the start of the game.

#### Input
* `virtual int input_check(std::string user_input)`: Should return: `0` if the user's move input is invalid or `1` if the input is valid.
* `virtual int input_transform(std::string user_input)`: Should return the user's move `m` as an `int`. Note that this function is only called if `input_check(std::string user_input)` returns `1`. Therefore, it is safe to assume that the user's input is valid before transforming it into an `int`.

#### Output
* `virtual void print_ai_move(int move)`: Should print the move that the AI decides on in the same format as the user's input.
* `virtual void print_rules()`: Should print the rules of the game.
* `virtual void print_board()`: Should print the board, given the current `game_state`, to the command line interface.

#### Updating the board
* `virtual std::vector<std::vector<int>> update_game_state(int move)`: Should return the updated `game_state` based on the last `move` that occured.
* `virtual int update_result(int move)`: Should return the updated `result` based on the updated `game_state`.
* `virtual int update_player(int move)`: Should return the next `player` based on the updated `game_state`.
* `virtual std::vector<int> update_available_moves(int move)`: Should return the `available_moves` for the next `player`.
        
## Creating a new game
New strategy games can be created by writing a new class which inherits `class GameBoard`. Several examples can be found in the [games](./games) directory.

Let's assume you are creating a game called `MyGame`. After writing your `MyGame.h` and `MyGame.cpp` files in the [games](./games) directory, the last step is to include it in [main.cpp](./main.cpp) as follows:

...
```
#include "games/TicTacToe.h"
#include "games/MyGame.h"

#include <iostream>
```
...
```
StrategyGame app;

std::vector<std::string> games_list = {"My Game", "Connect Four", "Hex (7 x 7)", "Reversi (Othello)", "Tic-Tac-Toe"};
asg::line_break(30);
```
...
```
} else if (games_list[g_index - 1] == "Hex (7 x 7)") {
    Hex game;
    app.run(game);
} else if (games_list[g_index - 1] == "My Game") {
    MyGame game;
    app.run(game);
}
std::vector<std::string> options = {"Return to main menu", "Exit"};
```
...


Thats it! The API takes care of the rest. Your game will appear in the main menu with a functioning AI.
