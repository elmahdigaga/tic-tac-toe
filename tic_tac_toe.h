#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <iostream>

#if _WIN32
#define CLEAR_SCREEN "cls"  // the keyword for Clearing the Command Prompt in WINDOWS is "cls"
#else
#define CLEAR_SCREEN "clear"  // the keyword for Clearing the Terminal in LINUX is "clear"
#endif

#define ROWS 3
#define COLS 3
#define BOARD_SIZE 9

// Player strcuture
struct Player {
    char name[8] = "Player ";  // Player1 or Player2
    char symbol;               // X or O
    int score;
};

// TicTacToe Board Class
class Board {
   private:
    char** grid;          // Board matrix
    __int8 number_moves;  // total number of moves
    Player player1;
    Player player2;
    Player* current_player;  // Pointer to the current player

    __int8 SlotToRow(const __int8 slot);                     // Translates the slot number to the corresponding row index
    __int8 SlotToCol(const __int8 slot);                     // Translates the slot number to the corresponding column index
    bool isValid(const __int8 row, const __int8 col) const;  // Checks if the slot is empty
    bool isSlotValid(const __int8 slot) const;               // Validates the slot number

   public:
    Board();                  // Constructor
    ~Board();                 // Destructor
    void Reset();             // Reset the board
    void Print() const;       // Print/Display the board
    void SetPlayers();        // Assign symbols and order of play
    void Play();              // Take input and update the board
    void SwitchPlayer();      // Change the current player
    bool isWin() const;       // Check for a win
    bool isDraw() const;      // Check for a draw
    void AnnounceResult();    // Print the result (Win or Draw)
    void PrintScore() const;  // Print the cumulative player scores
};

Board::Board() {
    // Allocate memory for the board matrix
    grid = new char*[ROWS];
    for (__int8 i = 0; i < ROWS; ++i) {
        grid[i] = new char[COLS];
    }

    // Set player scores to 0
    player1.score = 0;
    player2.score = 0;

    Reset();
}

Board::~Board() {
    // Delete allocated memory block by block
    for (__int8 i = 0; i < ROWS; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

void Board::Reset() {
    // Fill the grid cases with numbers from 1 to 9
    char c = '0';
    for (short int i = 0; i < ROWS; ++i) {
        for (short int j = 0; j < COLS; ++j) {
            grid[i][j] = ++c;
        }
    }

    // Set the number of moves done by the players to 0
    number_moves = 0;

    // Add the index(number) of the player to their name, and empty their symbols
    player1.name[6] = '1';
    player1.symbol = ' ';
    player2.name[6] = '2';
    player2.symbol = ' ';

    current_player = nullptr;
}

void Board::Print() const {
    // Print/Display the board
    for (__int8 i = 0; i < ROWS; ++i) {
        std::cout << "     |     |     \n";
        for (__int8 j = 0; j < COLS; ++j) {
            std::cout << "  " << grid[i][j] << "  ";
            if (j < COLS - 1) {
                std::cout << "|";
            }
        }
        if (i < ROWS - 1) {
            std::cout << "\n_____|_____|_____\n";
        }
    }
    std::cout << "\n     |     |     \n";
}

void Board::SetPlayers() {
    // Randomize the selection of the player who plays first (X always goes first)
    __int8 who_first = rand() % 2 + 1;

    if (who_first == 1) {  // if Player1 plays first
        // Assign X to P1
        player1.symbol = 'X';
        // Assign O to P2
        player2.symbol = 'O';
        // Point the current player to P1
        current_player = &player1;
    } else {  // if Player2 plays first
        // Assign O to P1
        player1.symbol = 'O';
        // Assign X to P2
        player2.symbol = 'X';
        // Point the current player to P2
        current_player = &player2;
    }
}

__int8 Board::SlotToRow(const __int8 slot) {
    // Translates the slot number to a row index
    return (slot - 1) / ROWS;
}
__int8 Board::SlotToCol(const __int8 slot) {
    // Translates the slot number to a column index
    return (slot - 1) % COLS;
}

bool Board::isValid(const __int8 row, const __int8 col) const {
    // Check if the chosen slot is empty
    return grid[row][col] != 'X' && grid[row][col] != 'O';
}

bool Board::isSlotValid(const __int8 slot) const {
    // Check if the number entered is in the range of 1 to 9
    return slot >= 1 && slot <= 9;
}

void Board::Play() {
    __int8 slot = 0, row = 0, col = 0;

    do {
        // Ask player for a slot number
        std::cout << current_player->name << " chooses an empty slot:\n> ";
        scanf("%hhd", &slot);
        // Check the chosen slot number
        if (!isSlotValid(slot)) {
            continue;
        }
        // Translate the slot number to the row and column indexes
        row = SlotToRow(slot);
        col = SlotToCol(slot);
        // If the indexes are invalid, Restart the process
    } while (!isValid(row, col));

    // If everything is good, assign the current player's symbol to the chosen slot
    grid[row][col] = current_player->symbol;
    // Increment the number of moves
    ++number_moves;
}

void Board::SwitchPlayer() {  // Swaps the current player
    if (current_player == &player1) {
        current_player = &player2;
    } else {
        current_player = &player1;
    }
}

bool Board::isWin() const {
    if (number_moves < 5) {  // the minimum number for a win to be possible is 5
        return false;
    }

    __int8 count_vert = 0, count_hori = 0, count_diag = 0, count_anti_diag = 0;

    for (__int8 i = 0; i < ROWS; ++i) {
        count_vert = 0, count_hori = 0;
        for (__int8 j = 0; j < COLS - 1; ++j) {
            // Check Horizontal win
            if (grid[i][j] == grid[i][j + 1]) {
                if (++count_hori == ROWS - 1) {
                    return true;
                }
            }
            // Check Vertical win
            if (grid[j][i] == grid[j + 1][i]) {
                if (++count_vert == ROWS - 1) {
                    return true;
                }
            }
        }

        if (i < ROWS - 1) {
            // Check Diagonal win
            if (grid[i][i] == grid[i + 1][i + 1]) {
                if (++count_diag == ROWS - 1) {
                    return true;
                }
            }
            // Check Anti Diagonal win
            if (grid[i][ROWS - i - 1] == grid[i + 1][ROWS - i - 2]) {
                if (++count_anti_diag == ROWS - 1) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::isDraw() const {  // Check for a draw
    if (number_moves < 9) {   // For a draw the number of moves must be 9
        return false;
    }

    return !isWin();
}

void Board::AnnounceResult() {
    if (isDraw()) {  // if there is a draw
        std::cout << "Draw!\n";
        return;
    }

    // if there is a win
    std::cout << current_player->name << " Won!\n";
    // Increment the winning player's score
    ++(current_player->score);
}

void Board::PrintScore() const {  // Prints the scores of the players
    std::cout << player1.name << ": " << player1.score << "\t";
    std::cout << player2.name << ": " << player2.score << "\n";
}

#endif