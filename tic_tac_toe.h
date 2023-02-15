#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <iostream>

#define ROWS 3
#define COLS 3

typedef struct {
    char name[8] = "Player ";
    char symbol;
} Player;

class Board {
   private:
    char** grid;
    int number_moves;
    Player player1;
    Player player2;
    Player* current_player;

   public:
    Board();

    ~Board();

    Board& Reset();

    Board& Print();

    Board& SetPlayers();

    int SlotToRow(int slot);

    int SlotToCol(int slot);

    bool isValid(int slot);

    Board& Play();

    Board& SwitchPlayer();

    bool isWin();

    Board& AnnounceWin();
};

Board::Board() {
    grid = new char*[ROWS];
    for (short int i = 0; i < ROWS; ++i) {
        grid[i] = new char[COLS];
    }
    Reset();
}

Board::~Board() {
    for (short int i = 0; i < ROWS; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

Board& Board::Reset() {
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

    return *this;
}

Board& Board::Print() {
    for (short int i = 0; i < ROWS; ++i) {
        std::cout << "     |     |     " << std::endl;
        for (short int j = 0; j < COLS; ++j) {
            std::cout << "  " << grid[i][j] << "  ";
            if (j < COLS - 1) {
                std::cout << "|";
            }
        }
        if (i < ROWS - 1) {
            std::cout << "\n_____|_____|_____" << std::endl;
        }
    }
    std::cout << "\n     |     |     " << std::endl;

    return *this;
}

Board& Board::SetPlayers() {
    srand(time(0));
    short int who_first = rand() % 2 + 1;
    if (who_first == 1) {
        player1.symbol = 'X';
        player2.symbol = 'O';
        current_player = &player1;
    } else {
        player1.symbol = 'O';
        player2.symbol = 'X';
        current_player = &player2;
    }

    return *this;
}

int Board::SlotToRow(int slot) {
    return (slot - 1) / ROWS;
}
int Board::SlotToCol(int slot) {
    return (slot - 1) % COLS;
}

bool Board::isValid(int slot) {
    if (slot < 1 || slot > 9) {
        return false;
    }

    int row = SlotToRow(slot);
    int col = SlotToCol(slot);
    if (grid[row][col] == 'X' || grid[row][col] == 'O') {
        return false;
    }

    grid[row][col] = current_player->symbol;
    return true;
}

Board& Board::Play() {
    int slot = 0;
    do {
        std::cout << current_player->name << " chooses an empty slot:\n> ";
        std::cin >> slot;
    } while (!isValid(slot));
    ++number_moves;

    return *this;
}

Board& Board::SwitchPlayer() {
    if (current_player == &player1) {
        current_player = &player2;
    } else {
        current_player = &player1;
    }
    return *this;
}

bool Board::isWin() {
    if (number_moves == 9) {
        return true;
    } else if (number_moves < 5) {
        return false;
    }
    int count_vert = 0, count_hori = 0, count_diag = 0, count_inv_diag = 0;
    for (int i = 0; i < ROWS; ++i) {
        count_vert = 0, count_hori = 0;
        for (int j = 0; j < COLS - 1; ++j) {
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
            if (grid[i][ROWS - i - 1] == grid[i + 1][ROWS - i - 1 - 1]) {
                if (++count_inv_diag == ROWS - 1) {
                    return true;
                }
            }
        }
    }

    return false;
}

Board& Board::AnnounceWin() {
    if (number_moves == 9) {
        std::cout << "Draw!" << std::endl;
        return *this;
    }
    std::cout << current_player->name << " Won!" << std::endl;

    return *this;
}

#endif