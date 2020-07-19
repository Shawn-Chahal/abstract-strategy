# Abstract Strategy Games 
An API which allows for the easy creation of abstract startegy games with artificial intelligence in C++. The games can then be played in a command-line interface.

## Available games
1. Connect Four
2. Tic-Tac-Toe

## Creating a custom strategy game class
New strategy games can be created by writing a new class which inherits `class StrategyGame` (see documentation below).

Here is an example using Tic-Tac-Toe:

1. Create a file called **tic-tac-toe.h**.
2. Inherit the StrategyGame class.
```
class TicTacToe: public StrategyGame {...};
```
3. Set the constant variables:
```
const std::string NAME = "Tic-Tac-Toe";   
std::vector<int> difficulty = {2, 6, 10}; // These are the max_depth that the AI will search the game tree for the {Easy, Medium, Hard} difficulties.
const int N_ROW = 3;
const int N_COL = 3;
const int N_MOVES = N_ROW * N_COL;
```
4. Define `void print_board()` which will print the game board to the command-line interface.
5. Define `std::vector<std::vector<int>> update_state()` which returns the updated `game_state` based on a `player`'s `move`.
6. Define `std::vector<int> update_available_moves()` which returns the updated `available_moves` based on the current `game_state`.
7. Define `int get_result()` which determines if the game has ended. Returns the player that won (1 or 2), a draw (0), or that the game has not yet ended (-1).
8. Define `void run()` which is a simple wrapper function for the inherited `run_internal()` method from the parent `class StrategyGame`.

## class StrategyGame
The parent class to be inherited by individual strategy game classes.

### void run_internal()
Set's up the in-game user interface. Allows the user to choose a difficulty setting and input their move each turn.

### int check_input()
Validates the user input.

### int check_moves()
Determines if the AI has attempted to check every branch of the game tree at a given node.

### int switch_player()
Switches between player 1 and 2.

### double get_score()
Returns the AI's score for a given move using a recursive minimax algorithm with alpha-beta pruning. Allows the setting of a max_depth to control the AI difficulty.

### int get_move()
Returns the best available move for the AI.
