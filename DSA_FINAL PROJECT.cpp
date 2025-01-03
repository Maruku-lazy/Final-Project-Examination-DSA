// Marc Jysk E. Herato / Jasmine Alexa Torente / Erika Alexi Magsino
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Node structure for both Binary Tree and BST
struct Node {
    int position;     // Board position (1-9)
    char symbol;      // 'X', 'O', or ' ' (empty)
    Node* left;       // Left child node (for binary tree structure)
    Node* right;      // Right child node (for binary tree structure)

    // Constructor to initialize a node with a position
    Node(int pos) : position(pos), symbol(' '), left(nullptr), right(nullptr) {}
};

// Class to represent the 3x3 game board using a binary tree
class TicTacToeTree {
    Node* root;  // Root node of the binary tree

public:
    TicTacToeTree() { root = nullptr; }

    // Builds a binary search tree to represent the Tic Tac Toe grid
    void buildTree() {
        root = new Node(5);  // The root represents the center of the grid (position 5)
        root->left = new Node(3);  // Left child (position 3)
        root->right = new Node(7); // Right child (position 7)

        // Building other positions of the Tic Tac Toe grid
        root->left->left = new Node(1);
        root->left->right = new Node(4);
        root->right->left = new Node(6);
        root->right->right = new Node(9);

        root->left->left->right = new Node(2);
        root->right->right->left = new Node(8);
    }

    // Displays the current board to the user
    void displayBoard() {
        vector<string> board(9, " ");  // Vector to represent the board
        queue<Node*> q;  // Queue to traverse the binary tree
        q.push(root);

        // Traverse the binary tree and populate the board with symbols
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current) {
                board[current->position - 1] = (current->symbol == ' ') ? to_string(current->position) : string(1, current->symbol);
                q.push(current->left);
                q.push(current->right);
            }
        }

        // Display the board in a human-readable format
        cout << "\n";
        for (int i = 0; i < 9; i++) {
            cout << " " << board[i] << " ";
            if (i % 3 != 2) cout << "|"; // Add vertical separators
            else if (i != 8) cout << "\n---+---+---\n"; // Add horizontal separators
        }
        cout << "\n";
    }

    // Make a move on the board (place 'X' or 'O' in the specified position)
    bool makeMove(Node* root, int pos, char player) {
        if (!root) return false;  // Base case for recursion (no node found)
        if (root->position == pos) {  // If the node matches the position
            if (root->symbol != ' ') {  // Check if the cell is already taken
                cout << "Cell already taken! Try again.\n";
                return false;
            }
            root->symbol = player;  // Mark the cell with the player's symbol
            return true;
        }
        if (pos < root->position)
            return makeMove(root->left, pos, player);  // Recurse to the left subtree
        return makeMove(root->right, pos, player);  // Recurse to the right subtree
    }

    // Reset the board by setting all positions to empty
    void resetBoard() {
        queue<Node*> q;
        q.push(root);

        // Traverse the tree and reset the symbols to ' ' (empty)
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            if (current) {
                current->symbol = ' ';
                q.push(current->left);
                q.push(current->right);
            }
        }
    }

    // Getter for the root node of the tree
    Node* getRoot() { return root; }
};

// Validator class to manage valid moves
class MoveValidator {
    Node* root;

public:
    MoveValidator() { root = nullptr; }

    // Insert a position into the binary tree to keep track of valid moves
    void insert(int pos) {
        Node** current = &root;
        while (*current) {
            if (pos < (*current)->position)
                current = &((*current)->left);
            else
                current = &((*current)->right);
        }
        *current = new Node(pos);
    }

    // Search for a position in the tree to check if it's a valid move
    bool search(int pos) {
        Node* current = root;
        while (current) {
            if (current->position == pos)
                return true;
            if (pos < current->position)
                current = current->left;
            else
                current = current->right;
        }
        return false;
    }
};

class MaxHeap {
    vector<pair<int, string>> heap;  // (score, player_name) pairs

public:
    // Push a player and their score into the heap
    void push(int score, string playerName) {
        heap.push_back(make_pair(score, playerName));  // Add player and score pair
        heapifyUp(heap.size() - 1);  // Maintain heap property
    }

    // Extract the root (highest score player)
    pair<int, string> pop() {
        if (heap.empty()) return {-1, ""};  // Return invalid pair if heap is empty

        swap(heap[0], heap[heap.size() - 1]);  // Swap the root with the last element
        pair<int, string> root = heap.back();
        heap.pop_back();

        heapifyDown(0);  // Reheapify from the root
        return root;
    }

    // Heapify-up operation to maintain the heap property
    void heapifyUp(int index) {
        while (index > 0 && heap[index].first > heap[(index - 1) / 2].first) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // Heapify-down operation to maintain the heap property
    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < heap.size() && heap[leftChild].first > heap[largest].first) {
            largest = leftChild;
        }

        if (rightChild < heap.size() && heap[rightChild].first > heap[largest].first) {
            largest = rightChild;
        }

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);  // Recursively heapify down
        }
    }

    // Return the top element (highest score) without removing it
    pair<int, string> top() {
        if (!heap.empty()) return heap[0];
        return {-1, ""};  // Return invalid pair if heap is empty
    }

    // Return the size of the heap
    int size() {
        return heap.size();
    }

    // Check if the heap is empty
    bool empty() {
        return heap.empty();
    }

    // Display the entire heap (all players with scores)
    void displayHeap() {
        for (auto& p : heap) {
            cout << p.second << ": " << p.first << "\n";
        }
    }
};


// Score heap class to track and display scores of players
class ScoreHeap {
    MaxHeap maxHeap; // Max heap to track the highest scores
    string playerXName;
    string playerOName;
    int playerXScore; // Score for Player X
    int playerOScore; // Score for Player O
    int playerXOtie; // Count of tied games

public:
    // Default constructor
    ScoreHeap() : playerXName("Player X"), playerOName("Player O"), playerXScore(0), playerOScore(0), playerXOtie(0) {}

    // Parameterized constructor
    ScoreHeap(string playerX, string playerO) : playerXName(playerX), playerOName(playerO), playerXScore(0), playerOScore(0), playerXOtie(0) {}

    // Update score for the winner ('X' or 'O')
    void updateScore(char player) {
        if (player == 'X') {
            playerXScore++; // Increase score for Player X
        } else if (player == 'O') {
            playerOScore++; // Increase score for Player O
        }
        updatePlayers();
    }

    // Increment tie count
    void updateTie() {
        playerXOtie++; // Increment tie count
        updatePlayers();
    }

    // Update players in the heap based on the current score
    void updatePlayers() {
        maxHeap = MaxHeap(); // Reset the heap
        maxHeap.push(playerXScore, playerXName); // Insert Player X with score
        maxHeap.push(playerOScore, playerOName); // Insert Player O with score
    }

    // Display the scores in order using the heap
    void displayScores() {
        cout << "\nScores: \n";
        maxHeap.displayHeap(); // Display the scores based on heap order
        cout << "Tie: " << playerXOtie << "\n"; // Display tie count
        cout << "\n";
    }
};

// Main game logic class
class TicTacToeGame {
    TicTacToeTree board;  // Game board
    MoveValidator validator;  // Validator for valid moves
    ScoreHeap heap;  // Score tracker
    int moves;  // Counter for number of moves made in the current game
    string playerXName;
    string playerOName;

public:
    TicTacToeGame() : moves(0) {
        cout << "Enter name for Player X: ";
        cin >> playerXName;  // Ask for Player X's name
        cout << "Enter name for Player O: ";
        cin >> playerOName;  // Ask for Player O's name

        heap = ScoreHeap(playerXName, playerOName);  // Initialize ScoreHeap with player names

        board.buildTree();  // Initialize the board structure
        for (int i = 1; i <= 9; ++i)
            validator.insert(i);  // Insert positions into validator
    }

    // Main game loop
    void playGame() {
    char currentPlayer = 'X';  // Start with Player X
    cout << "Welcome to Tic Tac Toe! \n";
    board.displayBoard();  // Display the initial board

    while (true) {
        resetGame();  // Reset the game at the beginning of each round
        while (moves < 9) {
            int pos;
            cout << "Player " << currentPlayer << " (" << (currentPlayer == 'X' ? playerXName : playerOName) << "), enter your move (1-9): ";
            cin >> pos;

            // Validate the move
            if (!validator.search(pos)) {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            // Make the move if valid
            if (board.makeMove(board.getRoot(), pos, currentPlayer)) {
                board.displayBoard();  // Display the board after the move
                moves++;  // Increment the move count

                // Check if the current player has won
                if (checkWin(currentPlayer)) {
                    cout << "Player " << currentPlayer << " wins this round!\n";
                    heap.updateScore(currentPlayer);  // Update the score for the winner
                    heap.displayScores();  // Display the updated scores
                    break;
                }

                // Switch to the other player
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        // Check for tie condition (no winner after 9 moves)
        if (moves == 9 && !checkWin('X') && !checkWin('O')) {
            cout << "\nIt's a tie!\n";
            heap.updateTie();  // Increment the tie count
            heap.displayScores();  // Display updated scores and tie count
        }

        // Ask if the user wants to play another round
        char playAgain;
        cout << "Do you want to play another round? (y/n): ";
        cin >> playAgain;
        if (playAgain != 'y') break;
    }
}


    // Check if the current player has won
    bool checkWin(char player) {
        int winCombos[8][3] = {
            {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
            {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
            {1, 5, 9}, {3, 5, 7}
        };

        // Check all win combinations
        for (auto& combo : winCombos) {
            int score = 0;
            for (int pos : combo) {
                if (checkPosition(board.getRoot(), pos, player))
                    score++;
            }
            if (score == 3) return true;
        }
        return false;
    }

    // Helper function to check if a specific position matches the player's symbol
    bool checkPosition(Node* root, int pos, char player) {
        if (!root) return false;
        if (root->position == pos) return root->symbol == player;
        if (pos < root->position)
            return checkPosition(root->left, pos, player);
        return checkPosition(root->right, pos, player);
    }

    // Reset the game (clear board and reset move count)
    void resetGame() {
        board.resetBoard();
        moves = 0;
    }
};

int main() {
    TicTacToeGame game;  // Create a game object
    game.playGame();  // Start the game
    return 0;
}
