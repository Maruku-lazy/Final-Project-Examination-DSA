This project is a game of Tic Tac Toe in C++ language with enhanced functionalities. 
The game uses data structures such as Binary Trees, Binary Search Trees (BST), and Heaps to model and manage different aspects of the game. 
It allows two players to alternate turns placing their marks ('X' or 'O') on a 3x3 grid, with the goal of achieving three consecutive marks in a row, column, or diagonal.
Key features include:
•	A binary tree representing the game board.
•	A binary search tree validating valid player moves.
•	A max-heap to manage and display player scores efficiently.
•	Player turn alternation, win condition checking, tie tracking, and score management.
Binary Tree: Game Board Representation
•	The TicTacToeTree class represents the 3x3 board using a binary tree.
o	Each node corresponds to a cell (positions 1–9).
o	Example tree structure:
               5
          /       \
        3           7
      /   \       /   \
     1     4     6     9
      \                 /
       2              8
•	Key Methods:
o	buildTree(): Constructs the tree by linking nodes to represent positions.
o	displayBoard(): Performs a level-order traversal to populate a 3x3 grid and display it in a user-friendly format.
o	makeMove(): Recursively searches the tree to update the symbol ('X' or 'O') for a given position, ensuring no overwriting of existing moves.
o	resetBoard(): Resets all nodes’ symbols to ' ' for a new game.

Binary Search Tree: Move Validation
•	The MoveValidator class uses a BST to validate moves.
o	Purpose: Ensure moves are within bounds (1–9) and not repeated.
o	Positions 1–9 are preloaded into the BST during initialization.
o	Key Methods:
	insert(int pos): Adds a position to the BST.
	search(int pos): Verifies if the position exists in the BST and is valid.
Max-Heap: Score Management
•	The MaxHeap class manages player scores using a priority queue (a max-heap).
o	Tracks scores for Player X, Player O, and the count of ties.
o	Swap the players position depending on the highest score.
o	Key Methods:
	updateScore(char player): Updates the score for the winner of a round.
	updateTie(): Increments the tie count.
	displayScores(): Prints current scores and the highest score.
	heapifyUp(): Swap the players position upward.
	heapifyDown(): Swap the players position downward.
Game Logic: Main Gameplay
•	The TicTacToeGame class contains the main game logic:
o	Initializes the board, move validator, and score heap.
o	Implements the game loop, allowing players to alternate turns, input moves, and check for wins or ties.
o	Key Methods:
	playGame(): Runs the main game loop.
	checkWin(char player): Evaluates all possible winning combinations using predefined position arrays.
	resetGame(): Clears the board and resets the move count for a new round.
	checkPosition(): Recursively checks if a specific position matches the player’s symbol.
