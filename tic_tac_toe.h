#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <iostream>

#if _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
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
    bool isWin() const;       // Check for a win or draw
    void AnnounceWin();       // Print the result (Win or Draw)
    void PrintScore() const;  // Print the cumulative player scores
};

Board::Board() {
    grid = new char*[ROWS];
    for (__int8 i = 0; i < ROWS; ++i) {
        grid[i] = new char[COLS];
    }
    player1.score = 0;
    player2.score = 0;
    Reset();
}

Board::~Board() {
    for (__int8 i = 0; i < ROWS; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

void Board::Reset() {
    char c = '0';
    for (short int i = 0; i < ROWS; ++i) {
        for (short int j = 0; j < COLS; ++j) {
            grid[i][j] = ++c;
        }
    }
    number_moves = 0;
    player1.name[6] = '1';
    player1.symbol = ' ';
    player2.name[6] = '2';
    player2.symbol = ' ';
    current_player = nullptr;
}

void Board::Print() const {
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
    __int8 who_first = rand() % 2 + 1;
    if (who_first == 1) {
        player1.symbol = 'X';
        player2.symbol = 'O';
        current_player = &player1;
    } else {
        player1.symbol = 'O';
        player2.symbol = 'X';
        current_player = &player2;
    }
}

__int8 Board::SlotToRow(const __int8 slot) {
    return (slot - 1) / ROWS;
}
__int8 Board::SlotToCol(const __int8 slot) {
    return (slot - 1) % COLS;
}

bool Board::isValid(const __int8 row, const __int8 col) const {
    return grid[row][col] != 'X' && grid[row][col] != 'O';
}

bool Board::isSlotValid(const __int8 slot) const {
    return slot >= 1 && slot <= 9;
}

void Board::Play() {
    __int8 slot = 0, row = 0, col = 0;
    do {
        std::cout << current_player->name << " chooses an empty slot:\n> ";
        scanf("%hhd", &slot);
        if (!isSlotValid(slot)) {
            std::cout << "Here\n";
            continue;
        }
        row = SlotToRow(slot);
        col = SlotToCol(slot);
    } while (!isValid(row, col));

    grid[row][col] = current_player->symbol;
    ++number_moves;
}

void Board::SwitchPlayer() {
    if (current_player == &player1) {
        current_player = &player2;
    } else {
        current_player = &player1;
    }
}

bool Board::isWin() const {
    if (number_moves == BOARD_SIZE) {
        return true;
    } else if (number_moves < 5) {
        return false;
    }

    __int8 count_vert = 0, count_hori = 0, count_diag = 0, count_inv_diag = 0;
    for (__int8 i = 0; i < ROWS; ++i) {
        count_vert = 0, count_hori = 0;
        for (__int8 j = 0; j < COLS - 1; ++j) {
            if (grid[i][j] == grid[i][j + 1]) {
                if (++count_vert == ROWS - 1) {
                    return true;
                }
            }
            if (grid[j][i] == grid[j + 1][i]) {
                if (++count_hori == ROWS - 1) {
                    return true;
                }
            }
        }
        if (i < ROWS - 1) {
            if (grid[i][i] == grid[i + 1][i + 1]) {
                if (++count_diag == ROWS - 1) {
                    return true;
                }
            }
            if (grid[i][ROWS - i - 1] == grid[i + 1][ROWS - i - 2]) {
                if (++count_inv_diag == ROWS - 1) {
                    return true;
                }
            }
        }
    }

    return false;
}

void Board::AnnounceWin() {
    if (number_moves == BOARD_SIZE) {
        std::cout << "Draw!\n";
        return;
    }
    std::cout << current_player->name << " Won!\n";
    ++(current_player->score);
}

void Board::PrintScore() const {
    std::cout << player1.name << ": " << player1.score << "\t";
    std::cout << player2.name << ": " << player2.score << "\n";
}

#endif